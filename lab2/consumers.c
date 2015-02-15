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
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

#define					BUFFER_CAPACITY 20
#define                 NUM_CONSUMERS   8
#define					NUM_PRODUCERS   1

pthread_mutex_t         dataMutex = PTHREAD_MUTEX_INITIALIZER;

// Producer condition variable - Producer waits on it
pthread_cond_t          bufferFullCondition = PTHREAD_COND_INITIALIZER;
// Consumer condition variable - Consumer waits on it
pthread_cond_t          bufferEmptyCondition = PTHREAD_COND_INITIALIZER;

// The representation of the items in the buffer
// This is the shared data all threads will access
int 					current_items=0;

/*
 *	Prints a visual representation of the number of items currently in buffer
 *	Output will look like this:		[||||||||||          ] (10/20)
 */
void print_buffer_state(int items){
	char str[BUFFER_CAPACITY + 3];
	int i = 0;

	strcpy(str, "[");
	while(i < BUFFER_CAPACITY){
		if(i < current_items){
			strcat(str, "|");
		}
		else{
			strcat(str, " ");
		}
		i++;
	}
	strcat(str, "]");
	printf("%s (%d/%d)\n", str, items, BUFFER_CAPACITY);
}

void *theProducer(void *threadid){

	int rc;

	// This will generate a warning (on 64 bit systems anyway)
	// due to pointers being 8 bytes long on 64 bit systems,
	// whereas ints are only 4 bytes long
	int id = (int)threadid;

	printf(BLUE"Producer Thread %.4x: Entered" RESET "\n", id);
	
	while(TRUE){
		// small pseudo random delay between 0s and 0.1s to simluate production 
		usleep(100000ULL * rand() / RAND_MAX);

		rc = pthread_mutex_lock(&dataMutex);
		checkResults("pthread_mutex_lock\n", rc);

		// No space in the buffer - producer waits until there is space
		while(current_items >= BUFFER_CAPACITY){
			printf(YELLOW "Producer #%.4x: waiting..." RESET "\n", id);
			
			// The condition variable the producer is waiting on 
			rc = pthread_cond_wait(&bufferFullCondition, &dataMutex);

			if(rc){
				printf("Producer condwait failed");
				pthread_mutex_unlock(&dataMutex);
				exit(1);
			}
		}
		printf(GREEN "Producer #%.4x: PRODUCED 	" RESET, id);

		// Item "produced"
		++current_items;

		print_buffer_state(current_items);

		// Notify threads there is something in buffer to be consumed
		pthread_cond_signal(&bufferEmptyCondition);
		rc = pthread_mutex_unlock(&dataMutex);
		checkResults("pthread_mutex_unlock\n", rc);
	}


	printf(CYAN "Producer Thread %.4x: All done" RESET "\n",id);
	return NULL;
}

void *theConsumer(void *threadid){
	
	int rc;
	int id = (int)threadid;
	printf(BLUE"Consumer Thread %.4x: Entered" RESET "\n", id);

	while(TRUE){
		// Note: consumer delays are longer so they don't outpace the producer
		// small pseudo random delay between 0s and 1s to simluate consumption
		usleep(1000000ULL * rand() / RAND_MAX);

		rc = pthread_mutex_lock(&dataMutex);
		checkResults("pthread_mutex_lock\n", rc);

		while(current_items == 0){
			printf(YELLOW"Consumer #%.4x: waiting..." RESET "\n", id);
			rc = pthread_cond_wait(&bufferEmptyCondition, &dataMutex);

			// extra delay to help stop the consumer outpacing the producer
			usleep(1000000ULL * rand() / RAND_MAX);
			if(rc){
				printf("Consumer condwait failed");
				pthread_mutex_unlock(&dataMutex);
				exit(1);
			}
		}
		printf(RED"Consumer #%.4x: CONSUMED 	" RESET, id);

		// Item "consumed"
		--current_items;

		print_buffer_state(current_items);

		// Notify producer there is definitely now space in buffer
		pthread_cond_signal(&bufferFullCondition);
		rc = pthread_mutex_unlock(&dataMutex);
		checkResults("pthread_mutex_unlock\n", rc);
	}


	printf(CYAN"Consumer Thread %.4x: All done" RESET "\n",id);
	return NULL;
}

int main(int argc, char **argv){
			
	pthread_t 		consumers[NUM_CONSUMERS];
	pthread_t       producers[NUM_PRODUCERS];
		
	int				rc =0;
	int 			i;
	
	printf("Create Producer Thread(s)\n");
	for(i = 0; i < NUM_PRODUCERS; ++i){
		rc = pthread_create(&producers[i], NULL, theProducer, (void *)i);
		checkResults("pthread_create()\n", rc);
	}

	printf("Create Consumer Threads\n");
	for(i = 0; i < NUM_CONSUMERS; ++i){
		rc = pthread_create(&consumers[i], NULL, theConsumer, (void *)i);
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
	
    return 0;
}
