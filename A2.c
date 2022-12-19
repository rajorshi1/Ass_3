#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>

sem_t forks[5];

void *philosopher1() {
    while (true) {
        printf("Philosopher 1 is thinking\n");
        sleep(1);
        sem_wait(&forks[0]);
        printf("Philosopher 1 picked left fork\n");
        sem_wait(&forks[1]);
        printf("Philosopher 1 picked right fork\n");
        printf("Philosopher 1 is eating\n");
        sleep(1);
        sem_post(&forks[0]);
        printf("Philosopher 1 placed left fork back\n");
        sem_post(&forks[1]);
        printf("Philosopher 1 placed right fork back\n");
    }
}

void *philosopher2() {
    while (true) {
        printf("Philosopher 2 is thinking\n");
        sleep(1);
        sem_wait(&forks[1]);
        printf("Philosopher 2 picked left fork\n");
        sem_wait(&forks[2]);
        printf("Philosopher 2 picked right fork\n");
        printf("Philosopher 2 is eating\n");
        sleep(1);
        sem_post(&forks[1]);
        printf("Philosopher 2 placed left fork back\n");
        sem_post(&forks[2]);
        printf("Philosopher 2 placed right fork back\n");
    }
}

void *philosopher3() {
    while (true) {
        printf("Philosopher 3 is thinking\n");
        sleep(1);
        sem_wait(&forks[2]);
        printf("Philosopher 3 picked left fork\n");
        sem_wait(&forks[3]);
        printf("Philosopher 3 picked right fork\n");
        printf("Philosopher 3 is eating\n");
        sleep(1);
        sem_post(&forks[2]);
        printf("Philosopher 3 placed left fork back\n");
        sem_post(&forks[3]);
        printf("Philosopher 3 placed right fork back\n");
    }
}

void *philosopher4() {
    while (true) {
        printf("Philosopher 4 is thinking\n");
        sleep(1);
        sem_wait(&forks[3]);
        printf("Philosopher 4 picked left fork\n");
        sem_wait(&forks[4]);
        printf("Philosopher 4 picked right fork\n");
        printf("Philosopher 4 is eating\n");
        sleep(1);
        sem_post(&forks[3]);
        printf("Philosopher 4 placed left fork back\n");
        sem_post(&forks[4]);
        printf("Philosopher 4 placed right fork back\n");
    }
}

void *philosopher5() {
    while (true) {
        printf("Philosopher 5 is thinking\n");
        sleep(1);
        sem_wait(&forks[4]);
        printf("Philosopher 5 picked left fork\n");
        sem_wait(&forks[0]);
        printf("Philosopher 5 picked right fork\n");
        printf("Philosopher 5 is eating\n");
        sleep(1);
        sem_post(&forks[4]);
        printf("Philosopher 5 placed left fork back\n");
        sem_post(&forks[0]);
        printf("Philosopher 5 placed right fork back\n");
    }
}

int main(int argc, char *argv[]) {
    for (int i = 0; i < 5; i++) {
        sem_init(&forks[i], 0, 1);
    }
    pthread_t p1, p2, p3, p4, p5;
    pthread_create(&p1, NULL, philosopher1, NULL);
    pthread_create(&p2, NULL, philosopher2, NULL);
    pthread_create(&p3, NULL, philosopher3, NULL);
    pthread_create(&p4, NULL, philosopher4, NULL);
    pthread_create(&p5, NULL, philosopher5, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    pthread_join(p4, NULL);
    pthread_join(p5, NULL);
    return 0;
}
