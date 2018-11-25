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
    int numbers;
    scanf("%d",&numbers);
    while(numbers>MAX_SEQUENCE)
    {
        printf("Please enter a number smaller than MAX_SEQUENCE!\nPlease enter:");
        scanf("%d",&numbers);
    }
    // create share memory
    int segment_id;
    shared_data *shared_memory;

    int size= sizeof(shared_memory->sequence_size);
    segment_id = shmget(IPC_PRIVATE, size*MAX_SEQUENCE, S_IRUSR | S_IWUSR);
    // attach the shared memory segment
    shared_memory = (shared_data*) shmat(segment_id,NULL,0);
    memset(shared_memory,0,size);
        shared_memory->sequence_size=numbers;
    // create the first process
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Fork Failed"); exit(-1);
    }
    else if (pid == 0) {
        for(int i=0;i<MAX_SEQUENCE;i++)
        {
            if(i==0)
                shared_memory->fib_sequence[i]=0;
            else if(i==1)
                shared_memory->fib_sequence[i]=1;
            else
                shared_memory->fib_sequence[i]=shared_memory->fib_sequence[i-1]+shared_memory->fib_sequence[i-2];
        }
        shmdt(shared_memory);
        exit(0);
    }
    else {
        // create the second process
        pid = fork();
        if(pid < 0) {
            fprintf(stderr, "Fork another process failed");
            exit(-1);
        }
        else if (pid == 0) {
            for(int i=0;i<shared_memory->sequence_size;i++)
            {
                printf("%ld ",shared_memory->fib_sequence[i]);
            }
            // detach the segment then exit
            shmdt(shared_memory);
            exit(0);
        }
        else {
            int count = 2;
            while (count > 0) {
                wait(NULL);
                count--;
            }
            // read messages posted by child processes
     
            shmdt(shared_memory);
            // parent removes the shared memory segment
            shmctl(segment_id,IPC_RMID,NULL);
            exit(0);
        }
    }
}
