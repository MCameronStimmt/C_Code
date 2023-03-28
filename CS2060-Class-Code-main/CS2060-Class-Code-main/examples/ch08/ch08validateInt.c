
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define LENGTH 80

void  exploreValidateInt(const char* buff);
bool validateInt(const char* buff);
void printLimits();

int main(void)
{
	char inputStr[LENGTH]; // create char arintray
	size_t inputLength = 0;
	bool isValid = 0;

	printLimits();

	for (unsigned int counter = 1; counter < 6; counter++)
	{
		puts("\nEnter an integer");
		fgets(inputStr, LENGTH, stdin);

		inputLength = strnlen(inputStr, LENGTH);

		if (inputLength > 0 && inputStr[inputLength - 1] == '\n')
		{
			inputStr[inputLength - 1] = '\0';
			inputLength--;
		}
		isValid = validateInt(inputStr);
		//exploreValidateInt(inputStr);
		
	}
	printf("int: %d", isValid);

}



void printLimits()
{
	printf("The number of bits in a byte %d\n", CHAR_BIT);

	printf("The minimum value of SIGNED CHAR = %d\n", SCHAR_MIN);
	printf("The maximum value of SIGNED CHAR = %d\n", SCHAR_MAX);
	printf("The maximum value of UNSIGNED CHAR = %d\n", UCHAR_MAX);

	printf("The minimum value of SHORT INT = %d\n", SHRT_MIN);
	printf("The maximum value of SHORT INT = %d\n", SHRT_MAX);

	printf("The minimum value of INT = %d\n", INT_MIN);
	printf("The maximum value of INT = %d\n", INT_MAX);

	printf("The minimum value of CHAR = %d\n", CHAR_MIN);
	printf("The maximum value of CHAR = %d\n", CHAR_MAX);

	printf("The minimum value of LONG = %ld\n", LONG_MIN);
	printf("The maximum value of LONG = %ld\n", LONG_MAX);
}


void  exploreValidateInt(const char* buff)
{

	//indicates which character the conversion should end at
	char* end;
	//errno set to 0
	errno = 0;
	//where the converted integer will be stored if valid
	int validInt = 0;
	//convert string into long and store in intTest 
	long intTest = strtol(buff, &end, 10);
	//if the string matches the ending character
	if (end == buff) {
		fprintf(stderr, "%s: not a decimal number\n", buff);
	}
	//if it is not the null character at the end of the converted string, there are extra characters 
	else if ('\0' != *end) {
		fprintf(stderr, "%s: extra characters at end of input: %s\n", buff, end);
	}
	//when it is unsuccessful and stores ERANGE in errno, check if it was caused by being out of range 
	else if ((LONG_MIN == intTest || LONG_MAX == intTest) && ERANGE == errno) {
		fprintf(stderr, "%s out of range of type long\n", buff);
	}
	//if the integer is greater then the acceptable max
	else if (intTest > INT_MAX) {
		fprintf(stderr, "%ld greater than INT_MAX\n", intTest);
	}
	//if the integer is less then the acceptable min 
	else if (intTest < INT_MIN) {
		fprintf(stderr, "%ld less than INT_MIN\n", intTest);
	}
	//if there were no errors, cast intTest into an int and store in validInt 
	else {
		validInt = (int)intTest;
		printf("%d is integer value ", validInt);
	}
}

bool  validateInt(const char* buff)
{
	bool isValid = false;
	char* end;
	errno = 0;
	int validInt = 0;
	long intTest = strtol(buff, &end, 10);

	if (end == buff) {
		fprintf(stderr, "%s: not an integer\n", buff);
	}
	else if ('\0' != *end) {
		fprintf(stderr, "%s: extra characters at end of input: %s\n", buff, end);
	}
	else if ((LONG_MIN == intTest || LONG_MAX == intTest) && ERANGE == errno) {
		fprintf(stderr, "%s Error out of range of long int\n", buff);
	}
	else if (intTest > INT_MAX) {
		fprintf(stderr, "%ld greater than INT_MAX\n", intTest);
	}
	else if (intTest < INT_MIN) {
		fprintf(stderr, "%ld less than INT_MIN\n", intTest);
	}
	else {
		validInt = (int)intTest;
		printf("%d Valid int", validInt);
		isValid = true;
	}
	return isValid; 
}
