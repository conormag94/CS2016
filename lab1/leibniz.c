#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#define  NUM_THREADS 	  10000
#define  CALCS_PER_THREAD 10000
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

double total = 0;
double answers[NUM_THREADS];
void * computePi(void * threadid){
	int rc;

	//rc = pthread_mutex_lock(&mutex);

	int i = ((int)threadid * CALCS_PER_THREAD);
	int calcs = 0;
	for(i; calcs < CALCS_PER_THREAD; i++){
		//total += pow(-1, i) / (2 * i + 1);
		answers[(int)threadid] += pow(-1, i) / (2 * i + 1);
		calcs += 1;
	}
	//sleep((random()%500000)/1000000.0);
	//rc = pthread_mutex_unlock(&mutex);
	return NULL;
}

int main(int argc, const char * argv[]){
	long cores = sysconf(_SC_NPROCESSORS_ONLN);
	printf("%ld Cores   | %ld Clocks per second\n", cores, CLOCKS_PER_SEC);
	printf("====================================\n");
	printf("%d Threads | %d Calculations per thread\n", NUM_THREADS, CALCS_PER_THREAD);
	// Current time
	clock_t start = clock();
	clock_t end = 0;
	
	pthread_t threads[NUM_THREADS];
	int rc = 0;
	int t;
	
	//rc = pthread_mutex_lock(&mutex);
	for(t = 0; t < NUM_THREADS; t++){

		rc = pthread_create(&threads[t], NULL, computePi, (void *)t);		
		if(rc){
			printf("ERROR return code from pthread_create(): %d\n", rc);
			exit(-1);
		}
	}

	//sleep(5);
	//rc = pthread_mutex_unlock(&mutex);
	for(t = 0; t < NUM_THREADS; t++){
		pthread_join(threads[t], NULL);
	}
	
	int x;
	for(x = 0; x < NUM_THREADS; x++){
		total += answers[x];
	}
	printf("Total %.15f\n", total * 4);
	//rc = pthread_mutex_destroy(&mutex);

	// Get end time after all computations
	end  = clock();
	printf("Elapsed time: %f s\n",(double)(end - start) / (CLOCKS_PER_SEC));// + 5);
	return 0;
	
}
