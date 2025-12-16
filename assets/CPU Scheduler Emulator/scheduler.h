#define DEBUG 1

/**
 * Job Linked List
 * @param id job id
 * @param length job length
 * @param next pointer to the next job
*/
struct job {
    int id;
    int length;
    struct job* next;
};

/**
 * First In First Out (FIFO) scheduling policy
 * @param job head of the job linked list
 * @param count number of jobs
*/
void fifo(struct job* job, int count);

/**
 * Shortest Job First (SJF) scheduling policy
 * @param job head of the job linked list
 * @param count the number of jobs
*/
void sjf(struct job* job, int count);

/**
 * Round Robin (RR) scheduling policy
 * @param job head of the job linked list
 * @param time_slice time slice
 * @param count the number of jobs
*/
void rr(struct job* job, int time_slice, int count);