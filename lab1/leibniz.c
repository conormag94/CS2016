#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define  NUM_THREADS 200

void * computePi(void * threadid){
	printf("I'm a thread\n");
	pthread_exit(NULL);
}

int main(int argc, const char * argv[]){
	clock_t start = clock();
	clock_t end = 0;
	
	pthread_t threads[NUM_THREADS];
	int rc, t;
	
	for(t = 0; t < NUM_THREADS; t++){
		printf("Creating thread %d\n", t);
		rc = pthread_create(&threads[t], NULL, computePi, (void *)t);
		
		if(rc){
			printf("ERROR return code from pthread_create(): %d\n", rc);
			exit(-1);
		}
	}
	
	for(t = 0; t < NUM_THREADS; t++){
		pthread_join(threads[t], NULL);
	}
	
	end  = clock();
	printf("Elapsed time: %f s\n", (double)(end - start) / CLOCKS_PER_SEC);
	return(0);
	
	/*
	
	
	int limit = 10000000;
	int i;
	double result = 1;
	
	double total = 0;

	clock_t end = 0;
	for(i = 0; i < limit; i++){
		total += pow(-1, i) / (2 * i + 1);
	}
	total *= 4;
	
	end = clock();
	
	printf("Pi: %.7f\n", total);
	printf("Elapsed time: %f s\n", (double)(end - start) / CLOCKS_PER_SEC);
	*/
	return 0;
}
