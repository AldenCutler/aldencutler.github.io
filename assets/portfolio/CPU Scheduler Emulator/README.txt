Project 4: Scheduling Policies
===================================
This is the work of Alden Cutler and Nia Junod.

To compile and run the program, use the following commands:
make
./scheduler <scheduling_policy> <workload_file> <timeslice_duration>


Part 1:
===================================
For part 1, we implemented and simulated a workload scheduler with three
scheduling policies, first-in-first-out, shortest-job-first, and round-robin.
The scheduler accepts command-line arguments for the scheduling policy, workload
file, and timeslice duration for round-robin. Workloads are defined in files
where each line represents a job with its total runtime. The scheduler then
initializes a job list as a linked list of structs. 

- FIFO (First-In-First-Out) the jobs are scheduled in order of arrival, and each
job runs to completion without preemption. 

- SJF (Shortest Job First) the shortest job is scheduled next, and tie breaking
favors jos that arrived earlier. 

- RR (Round Robin) jobs are scheduled in arrival order, and each job runs for a
fixed timeslice before preemption (timeslice provided as argument). 


Part 2: 
=================================== 
For part 2, we implemented the analysis of the scheduling policies. To store
each job's analytics, we used three arrays: response_times[],
turnaround_times[], and wait_times[]. In each policy's implementation, we added
code to update these arrays. Then, once the scheduler has finished running the
workload, we print each job's analytics to the console, as well as the average
response time, turnaround time, and wait time for all jobs.

We also created 5 custom workloads as described in the project description. We
These workloads are stored in the novel-workloads/ directory. We ran the
scheduler on each of these inputs to test the policies and analyze the results.
