//
//  main.cpp
//  OS1
//
//  Created by 林軒逸 on 4/12/16.
//  Copyright © 2016 林軒逸. All rights reserved.
//

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
    
    int*fib; //pointer of dynamic array of fibonacci sequence
    int numbers;// the number user inputted
    scanf("%d",&numbers); //read the number
    while (numbers<0) { //error detecting of negative number
        printf("Please input a positive number:");
        scanf("%d",&numbers);
    }
    fib= (int*)malloc(numbers*sizeof(int)); //declaration of the dynamic array
    pid_t pid;
    pid = fork(); /* fork another process */
    if (pid < 0) { /* error occurred */
        printf("Fork Failed\n");
        exit(-1);
    }
    else if (pid == 0) { /* child process */
        for(int i=0;i<numbers;i++) //fibnocci sequence
        {
            if(i==0)
            {
                fib[i]=0;
                printf("%d ",fib[i]); //output
            }
            else if(i==1)
            {
                fib[i]=1;
                printf("%d ",fib[i]); //output
            }
            else
            {
                fib[i]=fib[i-1]+fib[i-2];
                printf("%d ",fib[i]); //output
            }
        }
    }
    else { /* parent process */
        /* parent will wait for the child to complete */
        wait(NULL);
        printf ("Child Complete\n");
        exit(0);
    }
}
