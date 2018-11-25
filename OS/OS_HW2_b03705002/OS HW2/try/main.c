//
//  main.c
//  thread-1
//
//  Created by 周祐鈞 on 5/15/16.
//  Copyright © 2016 周祐鈞. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>

int aver,min,max,n,arr[];

void* maxCount(int arr[],int n);
void* minCount(int arr[],int n);
void* averCount(void arr[]);
int main(int argc, const char * argv[]) {
    // insert code here...
    n=argc-1;
    int arr[n];
    for(int i=0;i<n;i++) {
        arr[i]=atoi(argv[i]);
    }
    
    pthread_t averThread,minThread,maxThread;
    pthread_attr_t attr;
    
    pthread_attr_init(&attr);
    pthread_create(&averThread,&attr,averCount(arr,n),(void*)argv);
    pthread_create(&minThread,&attr,minCount(arr,n),(void*)argv);
    pthread_create(&maxThread,&attr,maxCount(arr,n),(void*)argv);
    
    pthread_join(maxThread,NULL);
    printf("The average value is %d\n",aver);
    printf("The minimum value is %d\n",min);
    printf("The maximum value is %d\n",max);
    return 0;
}

void* averCount(void* arr[]) {
    int*array=(int*)arr;
    int sum=0;
    for(int i=0;i<n;i++) {
        sum+=array[i];
    }
    aver=sum/n;
    pthread_exit(0);
}

void* minCount(void* arr[]) {
    int*array=(int*)arr;
    min=array[1];
    for(int i=1;i<n;i++) {
        if(array[i]<min)
            min=array[i];
    }
    pthread_exit(0);
}

void* maxCount(void* arr[]) {
    max=arr[0];
    for(int i=1;i<n;i++) {
        if(arr[i]>max)
            max=arr[i];
    }
    pthread_exit(0);
}