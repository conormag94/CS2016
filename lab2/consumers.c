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

#define					BUFFER_CAPACITY 8
#define                 NUM_CONSUMERS   2
#define					NUM_PRODUCERS   1
pthread_mutex_t         dataMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t          dataPresentCondition = PTHREAD_COND_INITIALIZER;
int                     dataPresent=0;
int                     sharedData=0;

struct buffer{
	int current_items;
	boolean is_full;
}buffer;

void *theProducer(void *threadid){

	int rc;
	
	printf("Producer Thread %.8x: Entered\n", (int)threadid);
	printf("Producer Thread %.8x: All done\n",(int)threadid);
	return NULL;
}

void *theConsumer(void *threadid){
	
	int rc;
	
	printf("Consumer Thread %.8x: Entered\n", (int)threadid);
	printf("Consumer Thread %.8x: All done\n",(int)threadid);
	return NULL;
}

void print_buffer(int items){
	char str[11];
	
	if(items == 0){
		strcpy(str, "[        ]");
	}
	else{
		int n = 0;
		
		strcpy(str, "[--------]");
	}
	printf("Buffer State:   %s\n", str);
}

int main(int argc, char **argv){
		
	buffer.current_items = 0;
	buffer.is_full = FALSE;
	printf("BUFFER CREATED. \nItems in Buffer: %d\n", buffer.current_items);
	
	pthread_t 		consumers[NUM_CONSUMERS];
	pthread_t       producers[NUM_PRODUCERS];
	
	print_buffer(buffer.current_items);
	
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
