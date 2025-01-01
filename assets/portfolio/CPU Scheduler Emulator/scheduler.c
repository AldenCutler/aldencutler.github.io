#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "scheduler.h"

// Private helper functions
/**
 * Calculate the average of an array of integers
 * @param count the number of elements in the array
 * @param arr the array of integers
*/
float calculate_average(int count, int arr[count]) {
    float average = 0;
    for (int i = 0; i < count; i++) {
        average += arr[i];
    }
    if (average == 0) return 0;
    return average / count;
}

/**
 * Remove a job from the linked list
 * @param head the head of the linked list
 * @param to_remove the id of the job to remove
*/
void remove_job(struct job* head, int to_remove) {
    if (head->id == to_remove) {
        head = head->next;
        return;
    }

    while (head->next->id != to_remove) {
        if (head == NULL) {
            printf("Error: id to remove not found in job list.\n");
            return;
        }
        head = head->next;
    }

    // remove job from list
    if (head->next->next != NULL) head->next = head->next->next;
    else head->next = NULL;
}

/**
 * Check if all jobs are done
 * @param job the head of the job linked list
*/
int check_done(struct job* head) {
    while (head != NULL) {
        if (head->length > 0) {
            return 0;
        }
        head = head->next;
    }
    return 1;
}
//----------------------------------------------------------------

// Public functions
void fifo(struct job* job, int num_jobs) {
    if (job == NULL) {
        printf("No jobs to run.\n");
        return;
    }
    struct job* current = job;
    int response_times[num_jobs];
    int turnaround_times[num_jobs];
    int wait_times[num_jobs];
    int response_time = 0;

    printf("Execution trace with FIFO:\n");
    while (current != NULL) {
        if (!DEBUG) {       // change DEBUG in scheduler.h to run sleep
            sleep(current->length);
        }

        printf("Job %d ran for: %d\n", current->id, current->length);
        response_times[current->id] = response_time;
        response_time += current->length;
        turnaround_times[current->id] = response_time;
        wait_times[current->id] = response_times[current->id];

        current = current->next;
    }
    printf("End of execution with FIFO.\n");

    // calculate response, turnaround, and wait times
    printf("Begin analyzing FIFO:\n");

    // print response, turnaround, and wait times
    for (int i = 0; i < num_jobs; i++) {
        printf("Job %d -- Response time: %d  Turnaround time: %d  Wait time: %d\n", i, response_times[i], turnaround_times[i], wait_times[i]);
    }

    // calculate and print averages
    float average_response = calculate_average(num_jobs, response_times);
    float average_turnaround = calculate_average(num_jobs, turnaround_times);
    float average_wait = calculate_average(num_jobs, wait_times);
    printf("Average -- Response time: %.2f  Turnaround time: %.2f  Wait time: %.2f\n", average_response, average_turnaround, average_wait);
    printf("End analyzing FIFO.\n");
    free(current);
}

void sjf(struct job* job, int num_jobs) {
    if (job == NULL) {
        printf("No jobs to run.\n");
        return;
    }

    struct job* head = job;
    int response_times[num_jobs];
    int turnaround_times[num_jobs];
    int wait_times[num_jobs];
    int response_time = 0;

    printf("Execution trace with SJF:\n");
    struct job* shortest;
    struct job* current;
    while (job != NULL) {

        shortest = job;
        current = job->next;

        // Find the shortest job in the linked list
        while (current != NULL) {
            if (current->length < shortest->length) {
                shortest = current;
            }
            current = current->next;
        }

        // Sleep for the length of the shortest job
        if (!DEBUG) {       // change DEBUG in scheduler.h to run sleep
            sleep(current->length);
        }
        printf("Job %d ran for: %d\n", shortest->id, shortest->length);

        // update response, turnaround, and wait times
        response_times[shortest->id] = response_time;
        response_time += shortest->length;
        turnaround_times[shortest->id] = response_time;
        wait_times[shortest->id] = response_times[shortest->id];

        // Remove the shortest job from the linked list
        if (shortest == head) {
            head = shortest->next;
        } else {
            remove_job(head, shortest->id);
        }

        // Move to the next job
        job = head;
    }
    printf("End of execution with SJF.\n");

    printf("Begin analyzing SJF:\n");
    // print response, turnaround, and wait times in order of shortest response time
    float average_response = calculate_average(num_jobs, response_times);
    float average_turnaround = calculate_average(num_jobs, turnaround_times);
    float average_wait = calculate_average(num_jobs, wait_times);

    for (int i = 0; i < num_jobs; i++) {
        // printf("Job %d -- Response time: %d  Turnaround time: %d  Wait time: %d\n", i, response_times[i], turnaround_times[i], wait_times[i]);
        int shortest_job = 0;
        for (int j = 0; j < num_jobs; j++) {
            if (response_times[j] < response_times[shortest_job]) {
                shortest_job = j;
            }
        }
        printf("Job %d -- Response time: %d  Turnaround time: %d  Wait time: %d\n", shortest_job, response_times[shortest_job], turnaround_times[shortest_job], wait_times[shortest_job]);
        response_times[shortest_job] = __INT_MAX__;
    }

    // calculate and print averages
    printf("Average -- Response time: %.2f  Turnaround time: %.2f  Wait time: %.2f\n", average_response, average_turnaround, average_wait);
    printf("End analyzing SJF.\n");
    free(head);
}

void rr(struct job* head, int time_slice, int num_jobs) {
    if (head == NULL) {
        printf("No jobs to run.\n");
        return;
    }
    if (time_slice <= 0) {
        printf("Error: time slice must be greater than 0.\n");
        return;
    }

    int response_times[num_jobs];       // response time = Time_start - Time_arrival (assume Time_arrival is always 0)
    int wait_times[num_jobs];           // wait time = time spent waiting in the ready queue
    int turnaround_times[num_jobs];     // turnaround time = Time_end - Time_arrival (assume Time_arrival is always 0)
    int response_time = 0;

    // initialize arrays
    for (int i = 0; i < num_jobs; i++) {
        response_times[i] = -1;         // -1 means response time has not been set (a.k.a. job has not started yet)
        wait_times[i] = 0;
        turnaround_times[i] = 0;
    }

    struct job* current = head;
    printf("Execution trace with RR:\n");

    while (!check_done(head)) {
        while (current != NULL) {
            if (current->length > 0) {
                if (current->length > time_slice) {
                    // change DEBUG in scheduler.h to run sleep
                    if (!DEBUG) sleep(time_slice);
                    printf("Job %d ran for: %d\n", current->id, time_slice);

                    // only set response time once
                    if (response_times[current->id] == -1) {
                        response_times[current->id] = response_time;
                    }
                    response_time += time_slice;

                    // update wait times for all other jobs
                    struct job* temp = head;
                    while (temp != NULL) {
                        if (current->id != temp->id && temp->length > 0) {
                            wait_times[temp->id] += time_slice;
                        }
                        temp = temp->next;
                    }

                    // update job length
                    current->length -= time_slice;
                } else {
                    // change DEBUG in scheduler.h to run sleep
                    if (!DEBUG) sleep(current->length);
                    printf("Job %d ran for: %d\n", current->id, current->length);

                    // only set response time once
                    if (response_times[current->id] == -1) {
                        response_times[current->id] = response_time;
                    }
                    response_time += current->length;
                    turnaround_times[current->id] = response_time;        // only set turnaround time when job is finished

                    // update wait times for all other jobs
                    struct job* temp = head;
                    while (temp != NULL) {
                        if (current->id != temp->id && temp->length > 0) {
                            wait_times[temp->id] += current->length;
                        }
                        temp = temp->next;
                    }

                    // update job length
                    current->length = 0;
                }
            }
            current = current->next;
        }
        current = head;
    }

    printf("End of execution with RR.\n");

    printf("Begin analyzing RR:\n");
    // print response, turnaround, and wait times
    for (int i = 0; i < num_jobs; i++) {
        printf("Job %d -- Response time: %d  Turnaround time: %d  Wait time: %d\n", i, response_times[i], turnaround_times[i], wait_times[i]);
    }

    // calculate and print averages
    float average_response = calculate_average(num_jobs, response_times);
    float average_turnaround = calculate_average(num_jobs, turnaround_times);
    float average_wait = calculate_average(num_jobs, wait_times);
    printf("Average -- Response time: %.2f  Turnaround time: %.2f  Wait time: %.2f\n", average_response, average_turnaround, average_wait);
}
//----------------------------------------------------------------
