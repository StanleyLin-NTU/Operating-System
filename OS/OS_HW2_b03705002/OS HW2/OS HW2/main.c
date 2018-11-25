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
void *average(void *param) {
    int*num= (int*)param;
    for(int i=0;i<length;i++)
    {
        sum+=num[i];
    }
    printf("%d",sum/length);
    pthread_exit(0);
    //Thread termination
}
void *minium(void* param){
    int* num=(int*)param;
    int minium=num[0];
    for(int i=0;i<length;i++)
    {
        if(num[i]<=minium)
        {
            minium=num[i];
        }
    }
    printf("%d",minium);
    pthread_exit(0);
    //Thread termination
}

void *maxium(void* param){
    int*num=(int*)param;
    int maxium=num[0];
    for(int i=0;i<length;i++)
    {
        if(num[i]>=maxium)
        {
            maxium=num[i];
        }
    }
    printf("%d",maxium);
    pthread_exit(0);
    //Thread termination
}
int main(int argc, char *argv[])
{
    length=argc-1;
    int numbers[length];
    for(int i=1;i<length;i++)
    {
        numbers[i]=atoi(argv[i]);
        printf("%d",numbers[i]);
    }
    pthread_t tid; /* the thread identifier */
    pthread_attr_t attr; /* set of attributes for the thread */
    if (argc != 2) {
        fprintf(stderr,"usage: a.out <integer value>\n");
        return -1;
    }
    if (atoi(argv[1]) < 0) {
        fprintf(stderr,"Argument %d must be non-negative\n",atoi(argv[1]));
        return -1;
    }
    /* get the default attributes */
    pthread_attr_init(&attr);
    /* create the thread */
    //Use default thread attributes.
    
    pthread_create(&tid,&attr,average,numbers);
    pthread_create(&tid,&attr,minium,numbers);
    pthread_create(&tid,&attr,maxium,numbers);
    //Create a separate thread The parent thread waits for child to complete.
    /* now wait for the thread to exit */
        pthread_join(tid,NULL);
}