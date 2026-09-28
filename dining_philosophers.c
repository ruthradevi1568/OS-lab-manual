#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#define N 5
#define MEALS 3
sem_t forks[N];
sem_t room;
void think(int id)
{
printf("Philosopher %d is thinking.\n", id);
usleep(100000);
}
void eat(int id)
{
printf("Philosopher %d is eating.\n", id);
usleep(100000);
}
void *philosopher(void *arg)
{
int id = *(int *)arg;
int left = id;
int right = (id + 1) % N;
for (int m = 0; m < MEALS; m++) {
think(id);
sem_wait(&room);
sem_wait(&forks[left]);
printf("Philosopher %d picked up left fork %d\n", id, left);
sem_wait(&forks[right]);
printf("Philosopher %d picked up right fork %d\n", id, right);
eat(id);
sem_post(&forks[right]);
sem_post(&forks[left]);
printf("Philosopher %d put down both forks.\n", id);
sem_post(&room);
}
return NULL;
}
int main()
{
pthread_t phil[N];
int ids[N];
for (int i = 0; i < N; i++)
sem_init(&forks[i], 0, 1);
sem_init(&room, 0, N - 1);
for (int i = 0; i < N; i++) {
ids[i] = i;
pthread_create(&phil[i], NULL, philosopher, &ids[i]);
}
for (int i = 0; i < N; i++)
pthread_join(phil[i], NULL);
for (int i = 0; i < N; i++)
sem_destroy(&forks[i]);
sem_destroy(&room);
printf("\nAll philosophers have finished eating. No deadlock occurred.\n");
return 0;
}
