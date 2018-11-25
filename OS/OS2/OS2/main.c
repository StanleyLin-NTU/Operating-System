//
//  main.c
//  OS2
//
//  Created by 林軒逸 on 3/31/16.
//  Copyright © 2016 林軒逸. All rights reserved.
//

#include <sys/types.h> 
#include <stdio.h> 
#include <sys/shm.h> 
#include <sys/ipc.h> 
#include <sys/stat.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h>

#define MAX_SEQUENCE 10
typedef struct{
    long fib_sequence[MAX_SEQUENCE];
    int sequence_size;
}shared_data;

int main() {
    int numbers; //the output numbers
    scanf("%d",&numbers);
    //Ensuring number>0
    while (numbers<0) {
        printf("Please enter a positive number.\nPlease enter:");
        scanf("%d",&numbers);
    }
    //Ensuring number<= MAX_SEQUENCE
    while(numbers>MAX_SEQUENCE)
    {
        printf("Please enter a number smaller than MAX_SEQUENCE!\nPlease enter:");
        scanf("%d",&numbers);
        while (numbers<=0) //Ensuring number>0
        {
            printf("Please enter a positive number.\nPlease enter:");
            scanf("%d",&numbers);
        }
    }
    // create share memory
    int segment_id;
    shared_data *shared_memory_fib; //The share memory pointer
    int size= sizeof(shared_memory_fib->sequence_size);
    segment_id = shmget(IPC_PRIVATE, size*MAX_SEQUENCE, S_IRUSR | S_IWUSR);
    // attach the shared memory segment
    shared_memory_fib = (shared_data*) shmat(segment_id,NULL,0);
    memset(shared_memory_fib,0,size);
        shared_memory_fib->sequence_size=numbers;
    // create process
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Fork Failed"); exit(-1);
    }
    //child process, creating fibonacci sequence
    else if (pid == 0) {
        //Creating fibonacci sequence
        for(int i=0;i<shared_memory_fib->sequence_size;i++)
        {
            if(i==0)
                shared_memory_fib->fib_sequence[i]=0;
            else if(i==1)
                shared_memory_fib->fib_sequence[i]=1;
            else
                shared_memory_fib->fib_sequence[i]=shared_memory_fib->fib_sequence[i-1]+shared_memory_fib->fib_sequence[i-2];
        }
        exit(0);
    }
    //parent process, outputting fibonaaci sequence
    else {
        int count = 1;
        while (count > 0) {
            wait(NULL);
            count--;
            if(shared_memory_fib->sequence_size>MAX_SEQUENCE)
                //error checking, although we had do it at the very first
            {
                exit(0);
            }
            //outputing fibonacci sequence
            for(int i=0;i<shared_memory_fib->sequence_size;i++)
            {
                printf("%ld ",shared_memory_fib->fib_sequence[i]);
            }
            // detach the segment then exit
            shmdt(shared_memory_fib);
            printf("\nProgram executed.");
            exit(0);
        }
    }
}
