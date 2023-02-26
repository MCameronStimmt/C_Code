// Passing Primitive Data Types and pointers
//Add comments to explain the code

#include <stdio.h>	
#include <stdlib.h>

int cubePass1(int number);
void cubePass2(int * numberPtr);

int main(void) {

	int numberMain = 5;
	int result = 0;
	
	printf ("In main before cubePass1  numberMain = %d\n", numberMain);
	printf("&numberMain = %p\n", &numberMain);
	result = cubePass1(numberMain);
	printf ("In main after cubePass1  numberMain = %d\n", numberMain);
	printf ("Result = %d\n", result);
	printf("\nIn main before cubePass2  numberMain = %d\n", numberMain);
//	result = cubePass2(&numberMain);
	printf("\nIn main after cubePass2  numberMain = %d\n", numberMain);
	printf("result = %d\n", result);

} // main


int cubePass1 (int number) 
{
	int cube = 0;
	puts("\nIn cubePass1");
	printf("number = %d\n", number);
	printf("&number = %p\n", &number);
	cube = number * number * number;
	printf("cube  = %d\n", cube);
	number = cube;
	printf("number = %d\n", number);
	return cube;
} 
//point to constant makes value unmodifiable 
void cubePass2(const int* numberPtr) {
	printf("   *numberPtr = %d\n", *numberPtr);
	printf("   numberPtr = %p\n", numberPtr);
	int cube = (*numberPtr) * (*numberPtr) * (*numberPtr);
	*numberPtr = cube;
	numberPtr = &cube;
	printf("   *numberPtr = %d\n\n", *numberPtr);
}



