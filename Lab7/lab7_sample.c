#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

#define NUM_THREADS 3

sem_t semaphore;

typedef struct {
    int threadID;
    int count;
} ThreadArgs;

void* threadFunc(void* args) {
    ThreadArgs* threadArgs = (ThreadArgs*)args;
    int tid = threadArgs->threadID;
    int count = threadArgs->count;

    printf("%d\n", count);
    printf("Thread %c is 等待共享記憶體可以使用\n", tid + 'A');
    sem_wait(&semaphore); // 等待semaphore可以使用
    printf("Thread %c has 可以使用共享變數.\n", tid + 'A');
    int state =  12;
    for(int i=0;i<count*2;i++){
        if(tid==0)
            if(state==12)
                state=3;
            else
                state=12;
        else if(tid==1)
            if(state==10)
                state=0;
            else
                state=10;
        else if(tid==2)
            if(state==6)
                state=15;
            else
                state=6;
        printf("change to %d%d%d%d\n",(state>>3)&1,(state>>2)&1,(state>>1)&1,(state>>0)&1);
    }
    printf("Thread %d is releasing the semaphore.\n", tid);
    sem_post(&semaphore);
    free(threadArgs);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadArgs* args[NUM_THREADS];

    // Initialize semaphore
    sem_init(&semaphore, 0, 1); // 只能一個執行序存取

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        args[i] = (ThreadArgs*)malloc(sizeof(ThreadArgs));
        args[i]->threadID = i;
        args[i]->count = 3;
        pthread_create(&threads[i], NULL, threadFunc, (void*)args[i]);
    }

    // Wait for threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy semaphore
    sem_destroy(&semaphore);

    return 0;
}
