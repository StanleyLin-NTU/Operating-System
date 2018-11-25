//
//  main.c
//  OS HW2
//
//  Created by 林軒逸 on 5/11/16.
//  Copyright © 2016 林軒逸. All rights reserved.
//
#include <stdio.h>
#include <pthread.h>

int length;
int sum;
int minimum;
int maximum;
void *average(void *param) //find average(integer value)
{
    int*num= (int*)param;
    for(int i=1;i<=length;i++)
    {
        sum+=num[i];
    }
    pthread_exit(0);
    //Thread termination
}
void *find_minimum(void* param) //find minium
{
    int* num=(int*)param;
    minimum=num[1];
    for(int i=1;i<=length;i++)
    {
        if(num[i]<=minimum)
        {
            minimum=num[i];
        }
    }
    pthread_exit(0);
    //Thread termination
}

void *find_maximum(void* param) //find max function
{
    int*num=(int*)param;
    maximum=num[1];
    for(int i=1;i<=length;i++)
    {
        if(num[i]>=maximum)
        {
            maximum=num[i];
        }
    }
    pthread_exit(0);
    //Thread termination
}
int main(int argc, char *argv[])
{
    if (argc < 2) //error handling
    {
        fprintf(stderr,"Please enter at least one number!\n");
        return -1;
    }
    length=argc-1;
    int numbers[argc];
    for(int i=1;i<=length;i++)
    {
        numbers[i]=atoi(argv[i]); //get the command line numbers
    }
    
    pthread_t tid; /* the thread identifier */
    pthread_attr_t attr; /* set of attributes for the thread */
    
    /* get the default attributes */
    pthread_attr_init(&attr);
    /* create three thread */
    //Use default thread attributes.
    pthread_create(&tid,&attr,average,numbers);
    pthread_create(&tid,&attr,find_minimum,numbers);
    pthread_create(&tid,&attr,find_maximum,numbers);
    //Create 3 separate threads, The parent thread waits for child to complete.
    /* now wait for the thread to exit */
    pthread_join(tid,NULL);
    printf("The average value is %d\n",sum/length);
    printf("The minimum value is %d\n",minimum);
    printf("The maximum value is %d\n",maximum);
}