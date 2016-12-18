#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <main.h>
#include <sched.h>

void *thread_task(void *x_void_ptr);
int start_thread_test(void);
void task1(void);
void task2(void);

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
    int id[NUM_THREAD];

    for(int i=0; i<NUM_THREAD; i++){
        id[i]=i;
        if(pthread_create(&p[i], NULL, thread_task, &id[i])) {
            fprintf(stderr, "Error creating thread\n");
            return 1;
        }
    }
    for(int i=0; i<NUM_THREAD; i++){
        if(pthread_join(p[i], NULL)) {
            fprintf(stderr, "Error joining thread\n");
            return 2;
        }
    }
    
    return 0;
}

void *thread_task(void *x_void_ptr)
{
    int id = *(int *) x_void_ptr;
    clock_t start = clock(), diff;
    int running=1;
    int msec=0;
    int laps = 0;
    while(running){
        if(id <NUM_THREAD/2){
            task1();
        }else{
            task2();
        }
        
        diff = clock() - start;
        msec = diff * 1000 / CLOCKS_PER_SEC;
        
        if(msec >= 1000){
            running =0;
        }else{
            laps++;
        }
    }
    
    printf("laps completed by thread %d: %d  \n", id, laps);
    
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