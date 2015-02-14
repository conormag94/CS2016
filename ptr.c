//#include <stdlib.h>
#include <stdio.h>

struct word{
	int length;
	char  letters;
	int something;
};

int main(){

	printf("\n   Pointer Sizes   \n");
	printf("====================\n");
	printf("On a 32 bit system, pointers are 4 bytes\n");
	printf("On a 64 bit system, pointers are 8 bytes\n");
	printf("Sizes may change from machine to machine\n");
	printf("====================\n");

	printf("Size of void     : %lu Bytes\n", sizeof(void));
	printf("Size of void *   : %lu Bytes\n", sizeof(void*));

	printf("Size of char     : %lu Bytes\n", sizeof(char));
	printf("Size of char *   : %lu Bytes\n", sizeof(char*));

	printf("Size of short    : %lu Bytes\n", sizeof(short));
	printf("Size of short *  : %lu Bytes\n", sizeof(short*));

	printf("Size of int      : %lu Bytes\n", sizeof(int));
	printf("Size of int *    : %lu Bytes\n", sizeof(int*));

	printf("Size of long     : %lu Bytes\n", sizeof(long));
	printf("Size of long *   : %lu Bytes\n", sizeof(long*));

	printf("Size of float    : %lu Bytes\n", sizeof(float));
	printf("Size of float *  : %lu Bytes\n", sizeof(float*));

	printf("Size of double   : %lu Bytes\n", sizeof(double));
	printf("Size of double * : %lu Bytes\n", sizeof(double*));

	printf("====================\n");

	printf("Size of unsigned char     : %lu Bytes\n", sizeof(unsigned char));
	printf("Size of unsigned char *   : %lu Bytes\n", sizeof(unsigned char*));

	printf("Size of unsigned short    : %lu Bytes\n", sizeof(unsigned short));
	printf("Size of unsigned short *  : %lu Bytes\n", sizeof(unsigned short*));

	printf("Size of unsigned int      : %lu Bytes\n", sizeof(unsigned int));
	printf("Size of unsigned int *    : %lu Bytes\n", sizeof(unsigned int*));

	printf("Size of unsigned long     : %lu Bytes\n", sizeof(unsigned long));
	printf("Size of unsigned long *   : %lu Bytes\n", sizeof(unsigned long*));

	printf("====================\n");

	printf("Size of signed char     : %lu Bytes\n", sizeof(signed char));
	printf("Size of signed char *   : %lu Bytes\n", sizeof(signed char*));

	printf("Size of signed short    : %lu Bytes\n", sizeof(signed short));
	printf("Size of signed short *  : %lu Bytes\n", sizeof(signed short*));

	printf("Size of signed int      : %lu Bytes\n", sizeof(signed int));
	printf("Size of signed int *    : %lu Bytes\n", sizeof(signed int*));

	printf("Size of signed long     : %lu Bytes\n", sizeof(signed long));
	printf("Size of signed long *   : %lu Bytes\n", sizeof(signed long*));

	return 0;
}