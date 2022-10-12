#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

pthread_mutex_t mutex;
sem_t sem;
pthread_cond_t cond;
bool flag = true;
void *printing_num1(void *);
void *printing_num2(void *);
int num = 10;

int main(int argc, char *argv[]) {
    printf("printing start...\n");

    // create double thread.
    pthread_t tid1, tid2;
    // create semaphore
    sem_init(&sem, 0, 1);

    pthread_create(&tid1, NULL, printing_num1, NULL);
    pthread_create(&tid2, NULL, printing_num2, NULL);
    // sem_post(&sem);     // +1
    // one thread printing one number and 

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("printing end.\n");

    return 0;
}

// true 运行
void *printing_num1(void *) {
    while(num > 0) {
        // pthread_mutex_lock(&mutex);
        while (!flag) {
            printf("thread1 wait...\n");
            pthread_cond_wait(&cond, &mutex);
            printf("thread1 start...\n");
        }
        printf("thread1: %d\n", num);
        num--;
        // pthread_mutex_unlock(&mutex);
        flag = false;
        pthread_cond_signal(&cond);
        printf("thread1 num = %d\n", num);
        printf("thread1 one end.\n");
    }
    printf("thread1 exit.\n");
}

// false 运行
void *printing_num2(void *) {
    while(num > 0) {
        // pthread_mutex_lock(&mutex);
        while(flag) {
            printf("thread2 wait...\n");
            pthread_cond_wait(&cond, &mutex);
            printf("thread2 start...\n");
        }
        printf("thread2: %d\n", num);
        num--;
        // pthread_mutex_unlock(&mutex);
        flag = true;
        pthread_cond_signal(&cond);
        printf("thread2 num = %d\n", num);
        printf("thread2 one end.\n");
    }
    printf("thread2 eixt.\n");
}
