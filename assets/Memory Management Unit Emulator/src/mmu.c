#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include "../include/helpers.h"
#include "../include/mmu.h"

// global variables
char* input;                                                    // input string
char** args;                                                    // input arguments
unsigned char* memory;                                          // physical memory
FILE* disk_file;                                                // file pointer for the disk file
int arg_count = 0;                                              // to keep track of the number of arguments
int hard_reg[4] = { -1, -1, -1, -1 };                           // hardware register for page table
int hard_reg_disk[4] = { -1, -1, -1, -1 };                      // hardware register for page table on disk
int mem_pids[4] = { -1, -1, -1, -1 };                           // process id of the page in the memory
int mem_pages[MAX_PAGES] = { EMPTY, EMPTY, EMPTY, EMPTY };      // status of the page in the memory
int disk_pages[64];                                             // status of the page in the disk
int page_to_evict = 0;                                          // round-robin page to evict

/* Old Array Implementation: this works but the assignment description mentions using a swap file */
// unsigned char* disk;                                         // could also be a file but for simplicity, we used an array

/**
 * Free the memory and exit the program
 */
void exit_memsim() {
    free(input);
    free(args);
    free(memory);
    printf("End of file.\n");
    exit(EXIT_SUCCESS);
}

/**
 * Get the next free page in the memory.
 * If all pages are full, evict one page and return the index of the free page.
 * @param pid the process id to allocate the page
 * @return the index of the free page
 */
int get_next_free_page(int pid) {
    for (int i = 0; i < 4; i++) {
        if (mem_pages[i] == EMPTY)
            return i;
    }
    // if all pages are full, evict one page
    return evict(pid);
}

/**
 * Get the next free page in the disk.
 * @return the index of the free page
 */
int get_next_free_page_disk() {
    for (int i = 0; i < 64; i++) {
        if (disk_pages[i] == EMPTY)
            return i;
    }

    // all pages should never be full with test cases provided
    printf("Error: Disk is full\n");
    return -1;
}

/**
 * Swap a page from the memory to the disk or vice versa.
 * @param mem_page the index of the page in the memory
 * @param disk_page the index of the page in the disk
 * @return 0 if swap is successful
 */
int swap(int mem_page, int disk_page) {
    int mem_start_idx = mem_page * PAGE_SIZE;
    int disk_start_idx = disk_page * PAGE_SIZE;
    unsigned char temp;
    unsigned char disk_byte;
    disk_file = fopen("disk", "rb+");


    // swap the pages
    for (int i = 0; i < PAGE_SIZE; i++) {
        temp = memory[mem_start_idx + i];

        // seek to correct position in disk file
        fseek(disk_file, disk_start_idx + i, SEEK_SET);

        // read a byte from the disk
        fread(&disk_byte, sizeof(unsigned char), 1, disk_file);

        // write the memory byte to the disk file
        fseek(disk_file, disk_start_idx + i, SEEK_SET);
        fwrite(&temp, sizeof(unsigned char), 1, disk_file);

        // swap the memory byte with the disk byte
        memory[mem_start_idx + i] = disk_byte;
    }

    fclose(disk_file);

    /* Old Array Implementation: this works but the assignment description mentions using a swap file */
    // swap the pages
    // for (int i = 0; i < PAGE_SIZE; i++) {
    //     temp = memory[mem_start_idx + i];
    //     memory[mem_start_idx + i] = disk[disk_start_idx + i];
    //     disk[disk_start_idx + i] = temp;
    // }

    return 0;
}

/**
 * Convert a virtual address to a physical address.
 * @param pid the process id
 * @param v_addr the virtual address
 * @return the physical address
 */
int convert(unsigned char pid, unsigned char v_addr) {
    int offset = v_addr % PAGE_SIZE;
    int entry_idx = find_ptable_entry(pid, v_addr);

    // invalid mapping
    if (entry_idx == -1 || memory[entry_idx + VALID] == 0 || memory[entry_idx + PRESENT] == 0)
        return -1;

    // PhysAddr = (PFN << PFN.SHIFT) | Offset (from textbook)
    int p_addr = memory[entry_idx + PFN] * PAGE_SIZE + offset;

    return p_addr;
}

/**
 * Find the page table for a process.
 * If the page table is not in the memory, swap it from the disk.
 * @param pid the process id
 * @return the index of the page table
 */
int find_ptable(int pid) {
    // if PT not in memory
    if (hard_reg[pid] == -1) {
        // if PT doesn't exist, return -1
        if (hard_reg_disk[pid] == -1) {
            return -1;
        }

        // else on disk, swap it to the memory and return idx
        int mem_page = get_next_free_page(pid);
        int disk_page = hard_reg_disk[pid];
        swap(mem_page, disk_page);
        hard_reg[pid] = mem_page;
        mem_pages[mem_page] = OCCUPY_PTABLE;
        mem_pids[mem_page] = pid;
        disk_pages[disk_page] = EMPTY;

        printf("Swapped disk page %d to memory page %d\n", disk_page, mem_page);
    }

    // return the page table index
    return hard_reg[pid];
}

/**
 * Update the page table entry when a page is evicted.
 * @param pid the process id
 * @param frame the index of the page in the memory
 * @param disk_page the index of the page in the disk
 * @return 0 if update is successful
 */
int update_ptable_entry(int pid, int frame, int disk_page) {
    // if the page table is in the memory
    if (hard_reg[pid] > -1) {
        // find the pte to be updated
        int entry_idx = hard_reg[pid] * PAGE_SIZE;

        // update the pte
        for (int i = 0; i < 4; i++) {
            if (memory[entry_idx + PFN] == frame) {
                // printf("updating evicted entry_idx: %d\n", entry_idx);
                memory[entry_idx + PRESENT] = 0;
                memory[entry_idx + PFN] = disk_page;
                break;
            }
            entry_idx += PTE_SIZE;
        }
    } else {
        // if the page table is on the disk, update the pte on the disk
        int entry_idx = hard_reg_disk[pid] * PAGE_SIZE;
        unsigned char disk_byte;
        disk_file = fopen("disk", "rb+");

        for (int i = 0; i < 4; i++) {
            // seek to the correct position in the disk file
            fseek(disk_file, entry_idx + PFN, SEEK_SET);

            // read a byte from the disk
            fread(&disk_byte, sizeof(unsigned char), 1, disk_file);

            if (disk_byte == frame) {
                disk_byte = 0;

                // write the updated byte to the disk file
                fseek(disk_file, entry_idx + PRESENT, SEEK_SET);
                fwrite(&disk_byte, sizeof(unsigned char), 1, disk_file);

                disk_byte = disk_page;

                // write the updated byte to the disk file
                fseek(disk_file, entry_idx + PFN, SEEK_SET);
                fwrite(&disk_byte, sizeof(unsigned char), 1, disk_file);

                break;
            }
            entry_idx += PTE_SIZE;
        }

        fclose(disk_file);

        /* Old Array Implementation: this works but the assignment description mentions using a swap file */
        // for (int i = 0; i < 4; i++) {
        //     if (disk[entry_idx + PFN] == frame) {
        //         disk[entry_idx + PRESENT] = 0;
        //         disk[entry_idx + PFN] = disk_page;
        //         break;
        //     }
        //     entry_idx += PTE_SIZE;
        // }
    }
    return 0;
}

/**
 * Find the page table entry for a process and a virtual address.
 * @param pid the process id
 * @param v_addr the virtual address
 * @return the index of the page table entry
 */
int find_ptable_entry(int pid, int v_addr) {
    int ptable = find_ptable(pid);

    // if PT doesn't exist, return -1
    if (ptable == -1) {
        return -1;
    }

    // otherwise, return the pte index
    int v_page = v_addr / PAGE_SIZE;
    return (ptable * PAGE_SIZE) + (v_page * PTE_SIZE);
}

/**
 * Evict a page from the memory to the disk using round-robin.
 * @param pid the process id
 * @return the index of the evicted page
 */
int evict(int pid) {
    // find the page to be evicted
    page_to_evict = (page_to_evict + 1) % 4;
    int type = mem_pages[page_to_evict];        // -1 = empty, 0 = page, 1 = page table
    int evictee = mem_pids[page_to_evict];      // the process id of the page to be evicted
    int disk_page = get_next_free_page_disk();

    // if the page is to be evicted, update the page table entry
    if (type == OCCUPIED) {     // OCCUPIED = 0
        // find the pte to be updated
        update_ptable_entry(evictee, page_to_evict, disk_page);

        // evict the page
        swap(page_to_evict, disk_page);
        disk_pages[disk_page] = OCCUPIED;
    } else if (type == OCCUPY_PTABLE) {
        // a page table to be evicted
        if (evictee == pid) {
            page_to_evict++;
            evict(pid);
            return page_to_evict - 1;
        }

        hard_reg[evictee] = -1;
        hard_reg_disk[evictee] = disk_page;
        swap(page_to_evict, disk_page);
        disk_pages[disk_page] = OCCUPY_PTABLE;
    } else {
        // this shouldn't ever happen with the test cases provided, but just in case
        printf("Trying to evict an empty page\n");
        return -1;
    }

    printf("Evicted memory page %d out to disk page %d\n", page_to_evict, disk_page);
    return page_to_evict;
}

/**
 * Maps a page of a process's virtual memory to a page of the physical memory.
 * @param pid the process id
 * @param v_addr the virtual address to start mapping from
 * @param value the protection value (0 = read-only, 1 = read/write)
 * @return 0 if mapping is successful
*/
int map(unsigned char pid, unsigned char v_addr, unsigned char value) {
    // find the page table for the process
    int ptable = find_ptable(pid);
    int v_page = v_addr / PAGE_SIZE;

    // the page table doesn't exist, try to allocate one page for PT
    if (ptable == -1) {
        // get a free page (evict one if full)
        ptable = get_next_free_page(pid);
        // printf("next free page: %d\n", ptable);

        // set the hardware register and page status
        mem_pages[ptable] = OCCUPY_PTABLE;
        mem_pids[ptable] = pid;
        hard_reg[pid] = ptable;

        // clear the page table
        int fstart = ptable * PAGE_SIZE;
        int fend = fstart + PAGE_SIZE;
        for (int i = fstart; i < fend; i++) {
            memory[i] = 0;
        }
        printf("Put page table for PID %u into physical frame %d\n", pid, ptable);
    }

    int entry_idx = (ptable * PAGE_SIZE) + (v_page * PTE_SIZE);

    // if already being mapped, update permission or return error
    if (memory[entry_idx + VALID] == 1) {
        if (value == memory[entry_idx + PROTECTION]) {
            printf("ERROR: virtual page %d already mapped with rw_bit = %u\n", v_page, value);
            return -1;
        } else {
            memory[entry_idx + PROTECTION] = value;
            printf("Updating permissions for virtual page %d", v_page);
            return 0;
        }
    }

    // otherwise, map a virtual page to physical frame
    int frame = get_next_free_page(pid);
    mem_pages[frame] = OCCUPIED;
    mem_pids[frame] = pid;
    memory[entry_idx + PFN] = frame;
    memory[entry_idx + VALID] = 1;
    memory[entry_idx + PROTECTION] = value;
    memory[entry_idx + PRESENT] = 1;
    printf("Mapped virtual address %d (page %d) into physical frame %d\n", v_addr, v_page, frame);
    return 0;
}

/**
 * Stores a value at a virtual address of a process.
 * @param pid the process id
 * @param v_addr the virtual address
 * @param value the value to store
 * @return 0 if store is successful
 */
int store(unsigned char pid, unsigned char v_addr, unsigned char value) {
    int entry_idx = find_ptable_entry(pid, v_addr);

    // if page on disk, swap it to the memory
    if (memory[entry_idx + PRESENT] == 0) {
        int frame = get_next_free_page(pid);
        int disk_frame = memory[entry_idx + PFN];
        swap(frame, disk_frame);
        mem_pages[frame] = OCCUPIED;
        mem_pids[frame] = pid;
        disk_pages[disk_frame] = EMPTY;
        memory[entry_idx + PRESENT] = 1;
        memory[entry_idx + PFN] = frame;
    }

    // if no mapping, return error
    int p_addr = convert(pid, v_addr);
    if (p_addr == -1) {
        printf("No mapping for process %u virtual address %u\n", pid, v_addr);
        return -1;
    }

    // if we don't have write permission, return error
    if (memory[entry_idx + PROTECTION] != WRITE) {
        printf("The physical frame %u is not writable\n", memory[entry_idx + PFN]);
        return -1;
    }

    // otherwise, store the value
    memory[p_addr] = value;
    printf("Stored value %u at virtual address %u (physical address %d)\n", value, v_addr, p_addr);
    return 0;
}

/**
 * Loads a value from a virtual address of a process.
 * @param pid the process id
 * @param v_addr the virtual address
 * @param value the value to load
 * @return 0 if load is successful
 */
int load(unsigned char pid, unsigned char v_addr) {
    int entry_idx = find_ptable_entry(pid, v_addr);

    // if page on disk, swap it to the memory
    if (memory[entry_idx + PRESENT] == 0) {
        int frame = get_next_free_page(pid);
        int disk_frame = memory[entry_idx + PFN];
        swap(frame, disk_frame);
        mem_pages[frame] = OCCUPIED;
        mem_pids[frame] = pid;
        disk_pages[disk_frame] = EMPTY;
        memory[entry_idx + PRESENT] = 1;
        memory[entry_idx + PFN] = frame;
    }

    // if no mapping, return error
    int p_addr = convert(pid, v_addr);
    if (p_addr == -1) {
        printf("No mapping for process %u virtual address %u\n", pid, v_addr);
        return -1;
    }
    // (don't need to check for read permission, since we can always read)

    // otherwise, print the value
    printf("The value %u is virtual address %u (physical address %d)\n", memory[p_addr], v_addr, p_addr);
    return 0;
}

/**
 * Main function to run the virtual memory manager.
 */
int main() {

    printf("Welcome to the Virtual Memory Manager\n");
    printf("-------------------------------------\n");

    // allocate memory for input, args, memory, and disk
    input = (char*)malloc(sizeof(char*) * (MAX_INPUT_LENGTH + 3));
    args = (char**)malloc(sizeof(char**) * (MAX_ARGS + 2));
    memory = (unsigned char*)malloc(sizeof(unsigned char*) * (PHYS_MEM_SIZE));
    
    /* Old Array Implementation: this works but the assignment description mentions using a swap file */
    // disk = (unsigned char*)malloc(sizeof(unsigned char*) * (DISK_SIZE));

    // initialize disk
    for (int i = 0; i < DISK_SIZE / PAGE_SIZE; i++) {
        disk_pages[i] = EMPTY;
    }

    while (1) {
        arg_count = 0;

        // prompt
        printf("\nInstruction? ");

        // check input
        if (read_input(input)) continue;
        if (read_args(args, input)) continue;
        if (arg_count != 4) {
            printf("Wrong number of arguments.\n");
            continue;
        }

        // parse input
        unsigned char pid = atoi(args[0]);
        char* instruction = args[1];
        unsigned char v_addr = atoi(args[2]);
        unsigned char value = atoi(args[3]);

        // process instruction
        printf("\n\n");
        if (strcmp(instruction, "map") == 0) {
            map(pid, v_addr, value);
        } else if (strcmp(instruction, "store") == 0) {

            // value must be between 0 and 255 for store
            int val = atoi(args[3]);
            if (val < 0 || val > 255) {
                printf("Invalid instruction, value must be between 0 and 255.\n");
                continue;
            }

            store(pid, v_addr, value);
        } else if (strcmp(instruction, "load") == 0) {

            // value must be "NA" for load
            if (strcmp(args[3], "NA") != 0) {
                printf("Invalid instruction, value can only be NA for load.\n");
                continue;
            }

            load(pid, v_addr);
        } else {
            printf("Invalid instruction, instruction can only be map/store/load.\n");
            continue;
        }
    }

    return 0;
}