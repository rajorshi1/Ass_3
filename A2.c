#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>

sem_t fork1;
sem_t fork2;
sem_t fork3;
sem_t fork4;
sem_t fork5;

void *philosopher1() {
    while (true) {
        printf("Philosopher 1 is thinking\n");
        sleep(1);
        sem_wait(&fork1);
        printf("Philosopher 1 picked left fork\n");
        sem_wait(&fork2);
        printf("Philosopher 1 picked right fork\n");
        printf("Philosopher 1 is eating\n");
        sleep(1);
        sem_post(&fork1);
        printf("Philosopher 1 placed left fork back\n");
        sem_post(&fork2);
        printf("Philosopher 1 placed right fork back\n");
    }
}

void *philosopher2() {
    while (true) {
        printf("Philosopher 2 is thinking\n");
        sleep(1);
        sem_wait(&fork2);
        printf("Philosopher 2 picked left fork\n");
        sem_wait(&fork3);
        printf("Philosopher 2 picked right fork\n");
        printf("Philosopher 2 is eating\n");
        sleep(1);
        sem_post(&fork2);
        printf("Philosopher 2 placed left fork back\n");
        sem_post(&forks3);
        printf("Philosopher 2 placed right fork back\n");
    }
}

void *philosopher3() {
    while (true) {
        printf("Philosopher 3 is thinking\n");
        sleep(1);
        sem_wait(&fork3);
        printf("Philosopher 3 picked left fork\n");
        sem_wait(&fork4);
        printf("Philosopher 3 picked right fork\n");
        printf("Philosopher 3 is eating\n");
        sleep(1);
        sem_post(&fork3);
        printf("Philosopher 3 placed left fork back\n");
        sem_post(&fork4);
        printf("Philosopher 3 placed right fork back\n");
    }
}

void *philosopher4() {
    while (true) {
        printf("Philosopher 4 is thinking\n");
        sleep(1);
        sem_wait(&fork4);
        printf("Philosopher 4 picked left fork\n");
        sem_wait(&fork5);
        printf("Philosopher 4 picked right fork\n");
        printf("Philosopher 4 is eating\n");
        sleep(1);
        sem_post(&fork4);
        printf("Philosopher 4 placed left fork back\n");
        sem_post(&fork5);
        printf("Philosopher 4 placed right fork back\n");
    }
}

void *philosopher5() {
    while (true) {
        printf("Philosopher 5 is thinking\n");
        sleep(1);
        sem_wait(&fork5);
        printf("Philosopher 5 picked left fork\n");
        sem_wait(&fork1);
        printf("Philosopher 5 picked right fork\n");
        printf("Philosopher 5 is eating\n");
        sleep(1);
        sem_post(&fork5);
        printf("Philosopher 5 placed left fork back\n");
        sem_post(&fork1);
        printf("Philosopher 5 placed right fork back\n");
    }
}

int main(int argc, char *argv[]) {
    sem_init(&fork1, 0, 1);
    sem_init(&fork2, 0, 1);
    sem_init(&fork3, 0, 1);
    sem_init(&fork4, 0, 1);
    sem_init(&fork5, 0, 1);
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
    sem_destroy(&fork1);
    sem_destroy(&fork2);
    sem_destroy(&fork3);
    sem_destroy(&fork4);
    sem_destroy(&fork5);
    return 0;
}
