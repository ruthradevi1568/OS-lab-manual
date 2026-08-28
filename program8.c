
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
#define ITEMS_TO_PRODUCE 10
 
int buffer[BUFFER_SIZE];
int in = 0, out = 0;
 
sem_t empty;   
sem_t full;    
pthread_mutex_t mutex; 
 
void *producer(void *arg)
{
    int item;
    for (item = 1; item <= ITEMS_TO_PRODUCE; item++) {
        sem_wait(&empty);              
        pthread_mutex_lock(&mutex);    
 
        buffer[in] = item;
        printf("Producer produced item %d at slot %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;
 
        pthread_mutex_unlock(&mutex);  
        sem_post(&full);               
 
        usleep(100000); 
    }
    return NULL;
}
 
void *consumer(void *arg)
{
    int item;
    for (int count = 1; count <= ITEMS_TO_PRODUCE; count++) {
        sem_wait(&full);               
        pthread_mutex_lock(&mutex);    
 
        item = buffer[out];
        printf("\tConsumer consumed item %d from slot %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;
 
        pthread_mutex_unlock(&mutex);  
        sem_post(&empty);             
 
        usleep(150000); 
    }
    return NULL;
}
 
int main()
{
    pthread_t prod_thread, cons_thread;
 
    sem_init(&empty, 0, BUFFER_SIZE); 
    sem_init(&full, 0, 0);            
    pthread_mutex_init(&mutex, NULL);
 
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);
 
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);
 
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
 
    printf("\nAll items produced and consumed successfully.\n");
    return 0;
}
 

 
