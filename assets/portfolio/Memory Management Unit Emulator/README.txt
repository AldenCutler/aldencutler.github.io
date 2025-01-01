Project 3: Virtual Memory Management
===================================
This is the work of Alden Cutler and Nia Junod.

Our task for this project was to create a virtual memory manager that takes intructions 
from simulated processes and modifies physical memory accordingly. In part 1, we implemented
the basics of paging, including a per-process page table, address translation, and support 
for multiple processes residing in memory concurrently. In part 2, we added support for 
swapping pages to and from disk. The core of the project is in the mmu.c file, with some 
helper functions in the helper.c file. 

To build and run the, cd into the src directory and run the following commands:
make
./project3

You can also supply an input file as an argument to the program:
./project3 test/sampleInput.txt

===================================
The main issue we ran into was with the swapping. We originally implemented the disk with a
text file, then when we couldn't get that to work, we switched to using an array of unsigned
chars. We then noticed in the project description that we were supposed to use a file, so we
eventually settled on a binary file, which I think is the correct way to do it.
-To clarify why our checkpoint submission code is different is because we originally had part 1 working fully which satisfied the requirements for the checkpoint.
But then we realized that the load function for part 2 did not work, so we had to change the code to use a binary file instead of an array of unsigned chars.
