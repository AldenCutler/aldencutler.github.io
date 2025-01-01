# Portfolio

Handshake doesn't let me upload .zip archives to display my portfolio, so the easiest workaround I thought of was to upload the archive to GitHub and then provide a link to this page in my application on Handshake. To download my portfolio and look at some of the work I've done in the past, just download any of the .zip archives in this folder.

## Binary Exploitation and Reverse Engineering
This contains coursework from my Software Security Design and Analysis class. It covers many different kinds of exploits like stack or heap-based buffer overflows, Ret2LibC, Return-Oriented Programming (ROP), format string vulnerabilities, and other general memory corruption attacks.

## Concurrency (threads and locks)
This is a project written for my Operating Systems class. See its [README](https://github.com/AldenCutler/aldencutler.github.io/blob/main/assets/portfolio/Concurrency%20(threads%20and%20locks)/README.txt) for more information on the details of the project.

## CPU Scheduler Emulator
I implemented and simulated a workload scheduler with three scheduling policies, first-in-first-out, shortest-job-first, and round-robin. The scheduler accepts command-line arguments for the scheduling policy, workload file, and timeslice duration for round-robin. Workloads are defined in files where each line represents a job with its total runtime. The scheduler then initializes a job list as a linked list of structs. 

- FIFO (First-In-First-Out) the jobs are scheduled in order of arrival, and each
job runs to completion without preemption. 

- SJF (Shortest Job First) the shortest job is scheduled next, and tie breaking
favors jos that arrived earlier. 

- RR (Round Robin) jobs are scheduled in arrival order, and each job runs for a
fixed timeslice before preemption (timeslice provided as argument). 

I also implemented the analysis of the scheduling policies. To store each job's analytics, we used three arrays: response_times[], turnaround_times[], and wait_times[]. In each policy's implementation, we added code to update these arrays. Then, once the scheduler has finished running the workload, we print each job's analytics to the console, as well as the average response time, turnaround time, and wait time for all jobs.

We also created 5 custom workloads as described in the project description. We These workloads are stored in the novel-workloads/ directory. We ran the scheduler on each of these inputs to test the policies and analyze the results.

## Full-Stack Web App
This is a project written for a web development class. The app is a tournament manager for a group member's high school badminton team. School coaches can upload player rosters. Tournament officials then submit game results on the Submission page. The brackets page then automatically updates with each school's score. We used a MERN stack for this app, meaning MongoDB for storing user data, Express.js for the back-end, React.js for the front-end, and Node.js for the server.

## Gauss Jordan Elimination and Dynamic Programming
This is a project written for my Algorithms and Data Structures class, showing my understanding of dynamic programming principles.

## Hashing and Dijkstra Implementation
This is a project written for my Algorithms and Data Structures class that shows my understanding of hashing, both open and closed. I also implemented Dijkstra's algorithm in C.

## Memory Management Unit Emulator
My task for this project was to create a virtual [memory manager](https://en.wikipedia.org/wiki/Memory_management_unit) that takes intructions from simulated processes and modifies physical memory accordingly. I implemented paging, including a per-process page table, address translation, and support for multiple processes residing in memory concurrently. I also added support for swapping pages to and from disk. The core of the project is in the mmu.c file, with some helper functions in the helper.c file. 

## N-Queens Problem
This was my final project for my Algorithms and Data Structures class. The [N-Queens Problem](https://en.wikipedia.org/wiki/Eight_queens_puzzle) is a problem where
the goal is to place N chess queens on an N×N chessboard so that no two queens threaten each other. I implemented a backtracking algorithm to solve this problem for any given N. The solution involves placing a queen on the board, then recursively attempting to place the next queen in a valid position. If a conflict is detected, the algorithm backtracks and tries the next possible position. 

With the code in the N-Queens problem folder, you can check if a position is a legal position, find the next legal position from any given position, find the first solution for any given n, or find all solutions for any given n.
