#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

typedef enum { FALSE, TRUE } boolean;

#define checkResults(string, val) {             \
if (val) {                                     \
printf("Failed with %d at %s", val, string); \
exit(1);                                     \
}                                              \
}

#define					BUFFER_CAPACITY 5
#define                 NUM_CONSUMERS   2
#define					NUM_PRODUCERS   1
pthread_mutex_t         dataMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t          bufferFullCondition = PTHREAD_COND_INITIALIZER;
int                     bufferFull=0;


struct buffer{
	int current_items;
	boolean is_full;
}buffer;

void print_buffer(int items){
	char str[BUFFER_CAPACITY + 3];
	int i = 0;

	strcpy(str, "[");
	while(i < BUFFER_CAPACITY){
		if(i < buffer.current_items){
			strcat(str, "|");
		}
		else{
			strcat(str, " ");
		}
		i++;
	}
	strcat(str, "]");
	printf("Items in Buffer:   %s (%d)\n", str, items);
}

void *theProducer(void *threadid){

	int rc;
	
	printf("Producer Thread %.4x: Entered\n", (int)threadid);

	while(TRUE){
		printf("Producing Data...\n");
		sleep(1);

		rc = pthread_mutex_lock(&dataMutex);
		checkResults("pthread_mutex_lock\n", rc);

		while(bufferFull){
			printf("Producer %.4x: Buffer full - waiting...\n", (int)threadid);
			rc = pthread_cond_wait(&bufferFullCondition, &dataMutex);

			if(rc){
				printf("Producer %.4x: condwait failed, rc=%d\n", (int)threadid,rc);
				pthread_mutex_unlock(&dataMutex);
				exit(1);
			}
		}
		printf("Producer %.4x: Producing Data\n", (int)threadid);

		++buffer.current_items;

		if(buffer.current_items == BUFFER_CAPACITY){
			bufferFull = 1;
		}

		print_buffer(buffer.current_items);
		rc = pthread_mutex_unlock(&dataMutex);
		checkResults("pthread_mutex_unlock\n", rc);
	}


	printf("Producer Thread %.4x: All done\n",(int)threadid);
	return NULL;
}

void *theConsumer(void *threadid){
	
	int rc;
	
	printf("Consumer Thread %.4x: Entered\n", (int)threadid);

	while(TRUE){
		printf("Waiting to consume\n");

		rc = pthread_mutex_lock(&dataMutex);
		checkResults("pthread_mutex_lock\n", rc);

		while(!bufferFull){
			printf("Consumer %.4x: waiting for data to be produced\n", (int)threadid);
			rc = pthread_cond_wait(&bufferFullCondition, &dataMutex);

			if(rc){
				printf("Consumer %.4x: condwait failed, rc=%d\n", (int)threadid,rc);
				pthread_mutex_unlock(&dataMutex);
				exit(1);
			}
		}

		printf("Consumer %.4x: Consuming Data\n", (int)threadid);
		--buffer.current_items;

		if(buffer.current_items == 0){
			bufferFull = 0;
		}

		print_buffer(buffer.current_items);
		rc = pthread_mutex_unlock(&dataMutex);
		checkResults("pthread_mutex_unlock\n", rc);
	}


	printf("Consumer Thread %.4x: All done\n",(int)threadid);
	return NULL;
}

int main(int argc, char **argv){
			
	pthread_t 		consumers[NUM_CONSUMERS];
	pthread_t       producers[NUM_PRODUCERS];
	
	buffer.current_items = 0;
	buffer.is_full = FALSE;
	printf("BUFFER CREATED\n");
	
	int				rc =0;
	int 			amountOfData=4;
	int 			i;
	
	printf("Create Consumer Threads\n");
	for(i = 0; i < NUM_CONSUMERS; ++i){
		rc = pthread_create(&consumers[i], NULL, theConsumer, (void *)i);
		checkResults("pthread_create()\n", rc);		
	}

	printf("Create Producer Thread(s)\n");
	for(i = 0; i < NUM_PRODUCERS; ++i){
		rc = pthread_create(&producers[i], NULL, theProducer, (void *)i);
		checkResults("pthread_create()\n", rc);
	}
	
	printf("Joining Consumers\n");
	for (i=0; i <NUM_CONSUMERS; ++i) {
		rc = pthread_join(consumers[i], NULL);
		checkResults("pthread_join()\n", rc);
	}
	
	printf("Joining Producers\n");
	for (i=0; i <NUM_PRODUCERS; ++i) {
		rc = pthread_join(producers[i], NULL);
		checkResults("pthread_join()\n", rc);
	}
	
	sleep(1);
    return 0;
}
