
#include <pthread.h>
#include <stdlib.h>
#define NUM_THREADS 2
void* print_hello(void *thread_id)
{
	pthread_exit(NULL);
}
int main(int argc, char *argv[])
{
	pthread_t threads[NUM_THREADS];
	int rc, t;
	for(t=0;t<NUM_THREADS;t++)
	{
		rc = pthread_create(&threads[t], NULL, print_hello, (void *)t);
		if (rc) exit(-1);
	}
	pthread_exit(NULL);
}
