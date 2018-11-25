//
//  main.c
//  OSHW3
//
//  Created by 林軒逸 on 6/6/16.
//  Copyright © 2016 林軒逸. All rights reserved.
//

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
double pi;
int point,sum;
void *computepi(void *param);
pthread_mutex_t mutex ;

int main(int argc, char *argv[])
{
    pthread_mutex_init(&mutex,NULL);
    pthread_attr_t attr;
    srand(time(0));
    int threadsum=(double)rand()/RAND_MAX*5000;
    pthread_t* tid=malloc((threadsum+100) * sizeof(pthread_t));
    int i;
    /* get the default attributes */
    pthread_attr_init(&attr);
    /* create the thread */
    for (i = 0; i < threadsum; ++i)
    {
        pthread_create(&tid[i],&attr,computepi,(void*)NULL);
    }
    for (i = 0; i < threadsum; ++i)
    {
        pthread_join(tid[i],NULL);
    }
    /* now wait for the thread to exit */
    pthread_mutex_destroy(&mutex);
    pi= (double)(4*point)/sum;
    printf("%f\n",pi);
    return 0;
}
void *computepi(void *param)
{
    long incirclesum=0;
    srand(time(NULL));
    long pointsum=(double)rand()/RAND_MAX*5000;
    long i;
    for (i = 0; i < pointsum; ++i)
    {
        double x = ((double)rand()/RAND_MAX) * 2.0 -1.0;
        double y = ((double)rand()/RAND_MAX) * 2.0 -1.0;
        if (x*x+y*y<=1){
            incirclesum++;
        }
    }
    pthread_mutex_lock(&mutex);
    point += incirclesum;
    sum += pointsum;
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}
