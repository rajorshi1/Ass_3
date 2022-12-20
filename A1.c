#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

int forks[5];

void free_fork(int *frok, int x) {
    frok[x] = 0;
}

void take_fork(int *frok, int x) {
    frok[x] = 1;
}

void take_right_fork(int *frok, int right) {
    while (frok[right] == 1) {
        sleep(1);
    }
    take_fork(forks, right);
}

void take_left_fork(int *frok, int left) {
    while (frok[left] == 1) {
        sleep(1);
    }
    take_fork(forks, left);
}

void *philosopher1() {
    while (true) {
        printf("Philosopher 1 is thinking\n");
        sleep(1);
        int left = 0;
        int right = 1;
        take_right_fork(forks, right);
        printf("Philosopher 1 picked right fork\n");
        take_left_fork(forks, left);
        printf("Philosopher 1 picked left fork\n");
        printf("Philosopher 1 is eating\n");
        sleep(1);
        free_fork(forks, left);
        printf("Philosopher 1 placed left fork back\n");
        free_fork(forks, right);
        printf("Philosopher 1 placed right fork back\n");
    }
}
void *philosopher2() {
    while (true) {
        printf("Philosopher 2 is thinking\n");
        sleep(1);
        int left = 1;
        int right = 2;
        take_left_fork(forks, left);
        printf("Philosopher 2 picked left fork\n");
        take_right_fork(forks, right);
        printf("Philosopher 2 picked right fork\n");
        printf("Philosopher 2 is eating\n");
        sleep(1);
        free_fork(forks, left);
        printf("Philosopher 2 placed left fork back\n");
        free_fork(forks, right);
        printf("Philosopher 2 placed right fork back\n");
    }
}
void *philosopher3() {
    while (true) {
        printf("Philosopher 3 is thinking\n");
        sleep(1);
        int left = 2;
        int right = 3;
        take_right_fork(forks, right);
        printf("Philosopher 3 picked right fork\n");
        take_left_fork(forks, left);
        printf("Philosopher 3 picked left fork\n");
        printf("Philosopher 3 is eating\n");
        sleep(1);
        free_fork(forks, left);
        printf("Philosopher 3 placed left fork back\n");
        free_fork(forks, right);
        printf("Philosopher 3 placed right fork back\n");
    }
}
void *philosopher4() {
    while (true) {
        printf("Philosopher 4 is thinking\n");
        sleep(1);
        int left = 3;
        int right = 4;
        take_left_fork(forks, left);
        printf("Philosopher 4 picked left fork\n");
        take_right_fork(forks, right);
        printf("Philosopher 4 picked right fork\n");
        printf("Philosopher 4 is eating\n");
        sleep(1);
        free_fork(forks, left);
        printf("Philosopher 4 placed left fork back\n");
        free_fork(forks, right);
        printf("Philosopher 4 placed right fork back\n");
    }
}
void *philosopher5() {
    while (true) {
        printf("Philosopher 5 is thinking\n");
        sleep(1);
        int left = 4;
        int right = 0;
        take_right_fork(forks, right);
        printf("Philosopher 5 picked right fork\n");
        take_left_fork(forks, left);
        printf("Philosopher 5 picked left fork\n");
        printf("Philosopher 5 is eating\n");
        sleep(1);
        free_fork(forks, left);
        printf("Philosopher 5 placed left fork back\n");
        free_fork(forks, right);
        printf("Philosopher 5 placed right fork back\n");
    }
}

int main(int argc, char *argv[]) {
    for (int i = 0; i < 5; i++) {
        forks[i] = 0;
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
