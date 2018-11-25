#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double pi;
int points_sum;
int in_circle_sum;
pthread_mutex_t mutex;//create mutex

void*calculate_pi(void* param);

void*calculate_pi(void* param) //the function of calculating pi
{
    int in_circle=0;
    srand(time(NULL));
    int points=(double)rand()/RAND_MAX*6000; //6000 points each thread
    for(int i=0;i<points;i++)
    {
        double x= (double)rand()/RAND_MAX; //radius
        double y=(double)rand()/RAND_MAX; //radius
        if(x*x+y*y<=1)
        {
            in_circle++; //the points fall in 1/4 circle
        }
    }
    pthread_mutex_lock(&mutex); //lock
    in_circle_sum+=in_circle;
    points_sum+=points;
    pthread_mutex_unlock(&mutex); //unlock
    pthread_exit(0); //thread terminate
}
int main(int argc, char *argv[])
{
    pthread_mutex_init(&mutex, NULL); //initiate mutex
    pthread_attr_t attr; //create parent thread
    pthread_attr_init(&attr); //initiate parent thread
    srand(time(NULL)); //ranadom seed
    int thread_count= (double)rand()/RAND_MAX*6000; //number of threads= 6000
    pthread_t tid=NULL;//parent thread id
    for (int i = 0; i < thread_count; i++)
    {
        pthread_create(&tid,&attr,calculate_pi,(void*)NULL); //creating threads
    }
    pthread_join(tid,NULL);
    pthread_mutex_destroy(&mutex); //destroy the mutex
    pi=(double)(4*in_circle_sum)/points_sum; //calculate pi
    printf("%f\n",pi); //print it
    return 0;
}