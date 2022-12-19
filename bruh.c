#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define NUM_FORKS 5

pthread_mutex_t forks[NUM_FORKS];

void *philosopher(void *id)
{
    int i = *((int*)id);
    int left_fork = i;
    int right_fork = (i + 1) % NUM_FORKS;

    while (1) {
        printf("Philosopher %d is thinking\n", i);
        sleep(1);

        printf("Philosopher %d is hungry\n", i);

        if (i % 2 == 0) {
            pthread_mutex_lock(&forks[right_fork]);
            pthread_mutex_lock(&forks[left_fork]);
        } else {
            pthread_mutex_lock(&forks[left_fork]);
            pthread_mutex_lock(&forks[right_fork]);
        }

        printf("Philosopher %d is eating\n", i);
        sleep(1);

        pthread_mutex_unlock(&forks[left_fork]);
        pthread_mutex_unlock(&forks[right_fork]);
    }

    return NULL;
}

int main(void)
{
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_FORKS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}
