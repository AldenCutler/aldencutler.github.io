#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "scheduler.h"

int main(int argc, char* argv[]) {
    
    // input should follow format: ./scheduler <policy name> <job trace file> <time slice>
    if (argc != 4) {
        printf("Usage: ./scheduler <policy name> <job trace file> <time slice>\n");
        return 1;
    }

    // get the policy name and convert to lowercase
    char* policy = argv[1];
    int len = strlen(policy);       // makes compiler happy
    for (int i = 0; i < len; i++) {
        policy[i] = tolower(policy[i]);
    }
    
    // get the time slice (only used for round robin policy)
    int time_slice = atoi(argv[3]);

    // get the job trace file 
    FILE* job_trace = fopen(argv[2], "r");
    if (job_trace == NULL) {
        printf("Error: file %s does not exist\n", argv[2]);
        return 1;
    }

    // read the file and store the jobs in job linked list struct
    struct job* head = NULL;
    int count = 0;
    int length;
    while (fscanf(job_trace, "%d", &length) != EOF) {
        struct job* new_job = (struct job*)malloc(sizeof(struct job));

        // set the id, length, and next pointer of the new job
        new_job->id = count;
        new_job->length = length;
        new_job->next = NULL;

        // if this is the first job, set it as the head of the linked list
        if (head == NULL) {
            head = new_job;
        } else {
            // otherwise, add the new job to the end of the linked list
            struct job* current = head;
            while (current->next != NULL) current = current->next;
            current->next = new_job;
        }

        count++;
    }

    // based on the policy name, call the corresponding function
    if (strcmp(policy, "fifo") == 0) {
        fifo(head, count);
    } else if (strcmp(policy, "sjf") == 0) {
        sjf(head, count);
    } else if (strcmp(policy, "rr") == 0) {
        rr(head, time_slice, count);
    } else {
        printf("Error: invalid policy name\n");
        return 1;
    }

    // free the memory allocated for the job linked list
    struct job* current = head;
    while (current != NULL) {
        struct job* temp = current;
        current = current->next;
        free(temp);
    }

    // close the file
    fclose(job_trace);

    return 0;
}