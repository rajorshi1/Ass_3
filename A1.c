#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

int fork1 = 0;
int fork2 = 1;
int fork3 = 2;
int fork4 = 3;
int fork5 = 4;

int free_fork(int spoon) {
    return = 0;
}

int take_fork(int spoon) {
    return 1;
}

int taking_fork(int spoon) {
    while (spoon == 1) {
        sleep(1);
    }
    return take_fork(spoon);
}

void *philosopher1() {
    while (true) {
        printf("Philosopher 1 is thinking\n");
        sleep(1);
        fork2 = taking_fork(fork2);
        printf("Philosopher 1 picked right fork\n");
        fork1 = taking_fork(fork1);
        printf("Philosopher 1 picked left fork\n");
        printf("Philosopher 1 is eating\n");
        sleep(1);
        fork1 = free_fork(fork1);
        printf("Philosopher 1 placed left fork back\n");
        fork2 = free_fork(fork2);
        printf("Philosopher 1 placed right fork back\n");
    }
}
void *philosopher2() {
    while (true) {
        printf("Philosopher 2 is thinking\n");
        sleep(1);
        fork2 = taking_fork(fork2);
        printf("Philosopher 2 picked left fork\n");
        fork3 = taking_fork(fork3);
        printf("Philosopher 2 picked right fork\n");
        printf("Philosopher 2 is eating\n");
        sleep(1);
        fork2 = free_fork(fork2);
        printf("Philosopher 2 placed left fork back\n");
        fork3 = free_fork(fork3);
        printf("Philosopher 2 placed right fork back\n");
    }
}
void *philosopher3() {
    while (true) {
        printf("Philosopher 3 is thinking\n");
        sleep(1);
        fork4 = taking_fork(fork4);
        printf("Philosopher 3 picked right fork\n");
        fork3 = taking_fork(fork3);
        printf("Philosopher 3 picked left fork\n");
        printf("Philosopher 3 is eating\n");
        sleep(1);
        fork3 = free_fork(fork3);
        printf("Philosopher 3 placed left fork back\n");
        fork4 = free_fork(fork4);
        printf("Philosopher 3 placed right fork back\n");
    }
}
void *philosopher4() {
    while (true) {
        printf("Philosopher 4 is thinking\n");
        sleep(1);
        fork4 = taking_fork(fork4);
        printf("Philosopher 4 picked left fork\n");
        fork5 = taking_fork(fork5);
        printf("Philosopher 4 picked right fork\n");
        printf("Philosopher 4 is eating\n");
        sleep(1);
        fork4 = free_fork(fork5);
        printf("Philosopher 4 placed left fork back\n");
        fork5 = free_fork(fork5);
        printf("Philosopher 4 placed right fork back\n");
    }
}
void *philosopher5() {
    while (true) {
        printf("Philosopher 5 is thinking\n");
        sleep(1);
        fork1 = taking_fork(fork1);
        printf("Philosopher 5 picked right fork\n");
        fork5 = taking_fork(fork5);
        printf("Philosopher 5 picked left fork\n");
        printf("Philosopher 5 is eating\n");
        sleep(1);
        fork1 = free_fork(fork1);
        printf("Philosopher 5 placed left fork back\n");
        fork5 = free_fork(fork5);
        printf("Philosopher 5 placed right fork back\n");
    }
}

int main(int argc, char *argv[]) {
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
