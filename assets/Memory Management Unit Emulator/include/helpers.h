
#define MAX_INPUT_LENGTH 128
#define MAX_ARGS 32
#define MAX_CMDS 128
#define NUM_PROCESSES 4
#define MAX_PAGES 4

// I believe DISK_SIZE could be as small as 320, but 1024 is just a nicer number
//  - NUM_PROCESSES * (MAX_PAGES + 1) * PAGE_SIZE
//  - 4 * ((64 / 16) + 1) * 16 = 4 * 5 * 16 = 320
#define DISK_SIZE 1024  
#define PHYS_MEM_SIZE 64
#define VMEM_SIZE 64
#define PAGE_SIZE 16
#define PTE_SIZE 4

// PTE values
#define PFN 0
#define VALID 1
#define PROTECTION 2
#define PRESENT 3
#define WRITE 1
#define READ 0

#define EMPTY -1
#define OCCUPIED 0
#define OCCUPY_PTABLE 1

int read_input(char* str);
int read_args(char** pstr, char* str);
