#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int a = 0;
pthread_mutex_t mutex;
int hasCalc = 0;
int hasIo = 0;

void *calc_thread() {
    printf("calc create!\n");
    for (int i = 1; i <= 100; i++) {
        while (hasCalc);
        pthread_mutex_lock(&mutex);
        printf("%d\n", i);
        a += i;
        hasIo = 0;
        hasCalc = 1;
        pthread_mutex_unlock(&mutex);
    }
}

void *io_thread() {
    printf("io created!;");
    while (a <= 5050) {
        while (hasIo);
        pthread_mutex_lock(&mutex);
        printf("%d\n", a);
        hasIo = 1;
        hasCalc = 0;
        pthread_mutex_unlock(&mutex);
    }
}


int main() {
    pthread_t io_t, calc_t;
    pthread_mutex_init(&mutex, NULL);
    if (pthread_create(&io_t, NULL, io_thread, NULL) == -1) {
        printf("io thread create failed\n");
    }
    if (pthread_create(&calc_t, NULL, calc_thread, NULL) == -1) {
        printf("calc thread create failed\n");
    }
    
    pthread_join(io_t, NULL);
    pthread_join(calc_t, NULL);
}
