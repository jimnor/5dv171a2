#ifndef MAIN_H_   
#define MAIN_H_

#define NUM_THREAD 20
#define TEST_TIME 1
void *thread_task(void *x_void_ptr);
int start_thread_test(void);
void task1(void);
void task2(void);
int main(int argc, char **argv);

#endif 