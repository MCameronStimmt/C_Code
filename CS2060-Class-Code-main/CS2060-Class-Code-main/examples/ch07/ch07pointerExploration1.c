/*******************
 Understanding pointers

 Add comments to explain the code
**************/

#include <stdio.h>


int main ()
{
	// Initalize houseNum
	int houseNum = 13;
	int calcHouseNum1 = 0;
	int calcHouseNum2 = 0;
	//declare pointer
	int *houseNumPtr = &houseNum;
	//prints actual value stored
	printf("houseNum %d\n", houseNum);
	//prints address
	printf("&houseNum %p\n\n", &houseNum);
	//prints value via *identifier 
	printf ("*houseNumPtr  %d\n", *houseNumPtr);
	//prints actual value of pointer which is the address of houseNum
	printf ("houseNumPtr %p\n\n", houseNumPtr);
	//prints address of pointer
	printf ("&houseNumPtr %p\n\n", &houseNumPtr);
	//use * to access value 
	calcHouseNum1 =  *houseNumPtr + *houseNumPtr;

	printf("*houseNumPtr + *houseNumPtr is %d\n\n", calcHouseNum1);
	//parenthesis to differenciate between multiplication and operator 
	calcHouseNum2 = 2 * (*houseNumPtr);

	printf("2 * (*houseNumPtr) is %d\n\n", calcHouseNum2);
	//using both address and dereferencing operator 
	printf("\n&*houseNumPtr = %p"
		"\n*&houseNumPtr = %p\n", &*houseNumPtr, *&houseNumPtr);
			
	return 0;
}
