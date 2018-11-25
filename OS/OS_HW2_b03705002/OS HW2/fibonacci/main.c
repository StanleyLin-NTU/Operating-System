//
//  main.c
//  OS HW2
//
//  Created by 林軒逸 on 5/11/16.
//  Copyright © 2016 林軒逸. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>

int number;
int*fib_seq;
void *fib(void *param) {
    number=atoi(param);
    fib_seq= (int*)malloc(number*sizeof(int));
    fib_seq[0]=0;
    fib_seq[1]=1;
    for(int i=2;i<number;i++) //Generate fibonacci sequence
    {
        fib_seq[i]=fib_seq[i-1]+fib_seq[i-2];
    }
    pthread_exit(0);
    //Thread termination
}
int main(int argc, char *argv[])
{
    if (argc != 2) //error handling
    {
        fprintf(stderr,"Please enter only one number!\n");
        return -1;
    }
    
    pthread_t tid; /* the thread identifier */
    pthread_attr_t attr; /* set of attributes for the thread */
    
    /* get the default attributes */
    pthread_attr_init(&attr);
    /* create the thread */
    //Use default thread attributes.
    
    pthread_create(&tid,&attr,fib,argv[1]);
    //Create a separate thread The parent thread waits for child to complete.
    /* now wait for the thread to exit */
    
    pthread_join(tid,NULL);
    for(int i=0;i<number;i++)
    {
        printf("%d ",fib_seq[i]); //print the fibonacci sequence
    }
}