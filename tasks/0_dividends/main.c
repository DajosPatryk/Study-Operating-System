#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#pragma GCC diagnostic ignored "-Wformat-zero-length"


extern int getDivisorCount_variant1(unsigned int value);
extern void getDivisorCount_variant2(int value, int *result);


unsigned long readInput(){
	unsigned long value;
	
	char inputPtr[64];
    char *errorPtr;
    do
    {
		printf("Input number: ");
        fgets(inputPtr, sizeof inputPtr, stdin);
        value = strtoul(inputPtr, &errorPtr, 10);
    } while (*errorPtr != '\n' && *errorPtr != '\0');

	return value;
}

int main() {
	unsigned long input = readInput();
	long tmp1;
	scanf("", &tmp1); // clear buffers

	if(input > INT_MAX){
		printf("Error: Number is not an integer.");
		return 1;
	}

	unsigned int value = (unsigned int)input;
	

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
