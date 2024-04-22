#include <stdio.h>
#include <stdlib.h>
#pragma GCC diagnostic ignored "-Wformat-zero-length"


extern int getDivisorCount_variant1(unsigned int value);
extern void getDivisorCount_variant2(int value, int *result);


unsigned int readInput(){
	unsigned int value;
	
	char inputPtr[32];
    char *errorPtr;
    do
    {
		printf("Input number: ");
        fgets(inputPtr, sizeof inputPtr, stdin);
        value = strtoll(inputPtr, &errorPtr, 10);
    } while (*errorPtr != '\n' && *errorPtr != '\0');

	return value;
}

int main() {
	unsigned int value = readInput();
	int tmp1;
	scanf("", &tmp1); // clear buffers

	// variant 1
	int divisorCount = getDivisorCount_variant1(value);

	printf("Divisor Count (variant 1): %d\n", divisorCount);

	// variant 2
	
	int *result;

	int signedValue = (signed int) value;

	getDivisorCount_variant2(signedValue, result);

	printf("Divisor Count (variant 2): %d\n", *result);

	return 0;
}