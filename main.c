#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <main.h>
#include <sched.h>

void *thread_task(void *x_void_ptr);
int start_thread_test(void);
void task1(void);
void task2(void);
void task3(int id);
void print_result(void);

int res[NUM_THREAD];
pthread_mutex_t lock;

int main(int argc, char **argv)
{
    printf("Test will run with %d threads during %d seconds\n", NUM_THREAD, TEST_TIME);
    printf("Initiating test... wait a bit\n");
    printf("Running on Standard schedular\n");
    start_thread_test();
    
    
	return 0;
}

int start_thread_test(void){
    pthread_t p[NUM_THREAD];
    pthread_mutex_init(&lock, NULL);
    int id[NUM_THREAD];
    
    pthread_mutex_lock(&lock);
    printf("Making threads\n");
    for(int i=0; i<NUM_THREAD; i++){
        id[i]=i;
        if(pthread_create(&p[i], NULL, thread_task, &id[i])) {
            fprintf(stderr, "Error creating thread\n");
            return 1;
        }
    }
    printf("running test...\n");
    pthread_mutex_unlock(&lock);
    for(int i=0; i<NUM_THREAD; i++){
        if(pthread_join(p[i], NULL)) {
            fprintf(stderr, "Error joining thread\n");
            return 2;
        }
    }
    printf("Test complete, displaying result\n\n");
    
    print_result();
    
    return 0;
}

void print_result(void){
    int total=0;
    int max=0;
    int min=0;
    pthread_mutex_lock(&lock);
    for(int i=0; i<NUM_THREAD; i++){
        if(min == 0 ){
            min = res[i];
        }else if(min > res[i]){
            min = res[i];
        }else if(max < res[i]){
            max = res[i];
        }
        total = total +res[i];
        printf("Thread %d completed %d work laps\n", i+1, res[i]);
    }
    pthread_mutex_unlock(&lock);
    total=total/NUM_THREAD;
    printf("\nAverage runtime is: %d\n", total);
    printf("Lowest amount of completed laps: %d\n", min);
    printf("Highest amount of completed laps: %d\n", max);
    printf("Gap between highest and lowest completions: %d\n", max-min);
}

void *thread_task(void *x_void_ptr)
{
    int id = *(int *) x_void_ptr;
    clock_t start = clock(), diff;
    int running=1;
    int msec=0;
    int laps = 0;
    pthread_mutex_lock(&lock);
    pthread_mutex_unlock(&lock);
    while(running){
        task1();
        task2();
        task3(id);
        
        diff = clock() - start;
        msec = diff * 1000 / CLOCKS_PER_SEC;
        
        if(msec >= 1000*TEST_TIME){
            running =0;
        }else{
            laps++;
        }
    }
    pthread_mutex_lock(&lock);
    res[id]=laps;
    pthread_mutex_unlock(&lock);
    
    return NULL;
}

void task1(void)
{
    for(int i=0; i<1000; i++){
        int temp = 5+5;
    }
}

void task2(void)
{
    for(int i=0; i<1000; i++){
        double temp = 70000*8121/(10012+102121) * 0.10212121;
    }
}

void task3(int id)
{
    char buf[256];
    sprintf(buf, "%d", id);
    
    FILE *fp = fopen(buf, "ab+");
    if(!fp){
        perror("failed to open file");
        exit(1);
    }
    fputs(buf, fp);
    fgets(buf, 255, (FILE*)fp);
    
    fclose(fp);
}