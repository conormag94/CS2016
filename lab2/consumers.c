#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define MAX_ITEMS 8

struct buffer{
	int current_items;
	int is_full;
};

struct producer{

};

struct consumer{

};
int main(){

	struct buffer buf;
	buf.current_items = 5;

	
	printf("%d\n", buf.current_items);
    return 0;
}