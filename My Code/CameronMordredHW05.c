//HW05 Read company information
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//constants
#define CHOICE_SIZE 2
#define BUFF_LENGTH 80
#define FEE 0.029

//Structures
typedef struct organization {
	char organizationName[BUFF_LENGTH];
	char name[BUFF_LENGTH];
	char emailAddress[BUFF_LENGTH];
	char purpose[BUFF_LENGTH];
	char goalAmount[BUFF_LENGTH];
	char password[BUFF_LENGTH];
	char url[BUFF_LENGTH];
	double donations;
	int numDonations;
	double creditCard;
}Organization;

typedef struct donation {
	char amount[BUFF_LENGTH];
	char name[BUFF_LENGTH];
	char zip[BUFF_LENGTH];
	double totalDonation;
}Donation;

//functions
void setUpOrganization(Organization* orgPtr);
void displayOrganization(Organization* orgPtr);
char* validInt(Organization* orgPtr);
bool correctEmail();
void setUpDonation(Donation* donPtr, Organization* orgPtr);
double validDonation(Donation* donPtr, Organization* orgPtr);
void validZip(Donation* donPtr);
void reciept(Organization* orgPtr, Donation* donPtr); 
void cardFee(Donation* donPtr, Organization* orgPtr);
void login(Donation* donPtr, Organization* orgPtr);


int main(void) {
	//variables
	//const char* yesOrNoPtr[CHOICE_SIZE] = { "yes", "no" }; 
	//int help = 0;
	Organization org1;
	Organization* org1Ptr = &org1;
	//initialize variables to zero
	org1Ptr->donations = 0;
	org1Ptr->creditCard = 0;
	org1Ptr->numDonations = 0;
	Donation don1;
	Donation* don1Ptr = &don1; 
	setUpOrganization(org1Ptr);
	//printf("Thank you %s. The url to raise funds for %s is", org1.name, org1.organizationName);

	setUpDonation(don1Ptr, org1Ptr); 

	//displayOrganization(org1);

	return 0; 
}

void setUpOrganization(Organization* orgPtr) {
	bool cont = false;
	//fill in organization info
	puts("\nEnter organization name");
	fgets(orgPtr->organizationName, BUFF_LENGTH, stdin);
	puts("Enter your name");
	fgets(orgPtr->name, BUFF_LENGTH, stdin);
	puts("Enter purpose");
	fgets(orgPtr->purpose, BUFF_LENGTH, stdin);
	puts("Enter goal amount");
	validInt(orgPtr);
	//continue loop while email is incorrect
	while (!cont) {
		puts("Enter email");
		fgets(orgPtr->emailAddress, BUFF_LENGTH, stdin);
		bool correct = correctEmail();
		if (correct == true) {
			puts("Create Password");
			fgets(orgPtr->password, BUFF_LENGTH, stdin);
			cont = true;
		}
		else {
			cont = false;
		}
	}
}

char* validInt(Organization* orgPtr) {
	bool cont = false;
	//continue while incorrect input
	while (!cont) {

		fgets(orgPtr->goalAmount, BUFF_LENGTH, stdin);
		//remove ending
		size_t inputLength = strnlen(orgPtr->goalAmount, BUFF_LENGTH);
		if (inputLength > 0 && orgPtr->goalAmount[inputLength - 1] == '\n')
		{
			orgPtr->goalAmount[inputLength - 1] = '\0';
			inputLength--;
		}
		//test for valid integer
		char* end;
		errno = 0;
		//int validInt = 0;
		double intTest = strtod(orgPtr->goalAmount, &end);
		//if the string matches the ending character
		if (end == orgPtr->goalAmount) {
			fprintf(stderr, "%s: not an integer\n", orgPtr->goalAmount);
		}
		//if it is not the null character at the end of the converted string, there are extra characters 
		else if ('\0' != *end) {
			fprintf(stderr, "%s: extra characters at end of input: %s\n", orgPtr->goalAmount, end);
		}
		//when it is unsuccessful and stores ERANGE in errno, check if it was caused by being out of range 
		else if ((LONG_MIN == intTest || LONG_MAX == intTest) && ERANGE == errno) {
			fprintf(stderr, "%s Error out of range of long int\n", orgPtr->goalAmount);
		}
		//if the integer is greater then the acceptable max
		else if (intTest > INT_MAX) {
			fprintf(stderr, "%f greater than INT_MAX\n", intTest);
		}
		//if the integer is less then the acceptable min 
		else if (intTest < 0) {
			fprintf(stderr, "%f less than zero\n", intTest);
		}
		//if there were no errors, cast intTest into an int and store in validInt
		else {
			//validInt = (int)intTest;
			cont = true;
		}
	}
	
	return orgPtr->goalAmount;
}

bool correctEmail() {
	char yesNo[BUFF_LENGTH];
	bool correct = false; 
	bool cont = false;
	puts("\nIs this email correct? (y)es y/Y or (n)o n/N");
	while (!cont) {
		fgets(yesNo, BUFF_LENGTH, stdin);
		//remove extra elements
		size_t inputLength = strnlen(yesNo, BUFF_LENGTH);
		if (inputLength > 0 && yesNo[inputLength - 1] == '\n')
		{
			yesNo[inputLength - 1] = '\0';
			inputLength--;
		}
		
		if (strcmp(yesNo, "y") == 0 || strcmp(yesNo, "Y") == 0) {
			correct = true;
			cont = true;
		}
		else if (strcmp(yesNo, "n") == 0 || strcmp(yesNo, "N") == 0) {
			correct = false; 
			cont = true;
		}
		else {
			puts("Please enter (y)es y/Y or (n)o n/N");
		}
	}
	return correct; 
}

/**void createURL(Organization* orgPtr) {
	char front[BUFF_LENGTH] = "https:donate.com/";
	char back[BUFF_LENGTH] = "?form=popup#";
	char string[BUFF_LENGTH];
	strncpy(string, orgPtr->organizationName, BUFF_LENGTH);
	char replace = '-';
	for (int i = 0; i = strlen(string); i++) {
		if (string[i] == ' ') {
			string[i] = replace;
		}
	}
	strncat(front, string, BUFF_LENGTH);
	strncat(front, back, BUFF_LENGTH);
	fgets(orgPtr->url, BUFF_LENGTH, front);

}*/


void setUpDonation(Donation* donPtr, Organization* orgPtr) {
	while (strcmp(donPtr->amount, "q") != 0 || strcmp(donPtr->amount, "Q") != 0) {
		puts("\nEnter donation amount");
		validDonation(donPtr, orgPtr);
		puts("Enter your name");
		fgets(donPtr->name, BUFF_LENGTH, stdin);
		puts("Enter your 5 digit zip code");
		validZip(donPtr);
		orgPtr->numDonations++;
		cardFee(donPtr, orgPtr);
		reciept(orgPtr, donPtr);
	}
	
}

void cardFee(Donation* donPtr, Organization* orgPtr) {
	char* end;
	double donationAmount = strtod(donPtr->amount, &end);
	double cardFee = donationAmount * FEE; 
	double total = donationAmount + cardFee;
	orgPtr->creditCard += cardFee;
	donPtr->totalDonation = total; 
	printf("\nThank you for your donation. There is a 2.9 percent credit card processing fee of %f. %f will be donated.", 
		donationAmount, total);
	orgPtr->donations += total; 
}

void reciept(Organization* orgPtr, Donation* donPtr) {
	char yesNo[BUFF_LENGTH];
	bool cont = false;
	puts("Do you want a reciept? (y)es y/Y or (n)o n/N");
	//continue to ask until user inputs acceptable answer 
	while (!cont) {
		fgets(yesNo, BUFF_LENGTH, stdin);
		//remove extra elements
		size_t inputLength = strnlen(yesNo, BUFF_LENGTH);
		if (inputLength > 0 && yesNo[inputLength - 1] == '\n')
		{
			yesNo[inputLength - 1] = '\0';
			inputLength--;
		}
		//print out reciept info while user inputs y/Y
		if (strcmp(yesNo, "y") == 0 || strcmp(yesNo, "Y") == 0) {
			cont = true;
			printf("\nOrganization: %s", orgPtr->organizationName);
			printf("Donation Amount: %f", donPtr->totalDonation);
			//find local time and date
			time_t now;
			time(&now);
			//convert time to local time
			struct tm* local = localtime(&now);
			int hours = local->tm_hour;         
			int minutes = local->tm_min;        
			int seconds = local->tm_sec; 
			int day = local->tm_mday;            
			int month = local->tm_mon + 1;      
			int year = local->tm_year + 1900;
			//if its am
			if (hours < 12) {    
				printf("\nDonation Date:  %02d/%02d/%d - %02d:%02d:%02d am\n", day, month, year, hours, minutes, seconds);
			}
			//if pm
			else {    
				printf("\nDonation Date:  %02d/%02d/%d - %02d:%02d:%02d pm\n", day, month, year, hours - 12, minutes, seconds);
			}

		}
		else if (strcmp(yesNo, "n") == 0 || strcmp(yesNo, "N") == 0) {
			cont = true;
		}
		else {
			puts("Please enter (y)es y/Y or (n)o n/N");
		}
	}
}
double validDonation(Donation* donPtr, Organization* orgPtr) {
	bool cont = false;
	double intTest = 0;
	//continue while incorrect input
	while (!cont) {

		fgets(donPtr->amount, BUFF_LENGTH, stdin);
		//remove ending
		size_t inputLength = strnlen(donPtr->amount, BUFF_LENGTH);
		if (inputLength > 0 && donPtr->amount[inputLength - 1] == '\n')
		{
			donPtr->amount[inputLength - 1] = '\0';
			inputLength--;
		}
		if (strcmp(donPtr->amount, "q") == 0 || strcmp(donPtr->amount, "Q") == 0) {
			login(donPtr, orgPtr);
			cont = true; 
		}
		//test for valid integer
		char* end;
		errno = 0;
		//int validInt = 0;
		intTest = strtod(donPtr->amount, &end);
		//if the string matches the ending character
		if (end == donPtr->amount) {
			fprintf(stderr, "%s: not an integer\n", donPtr->amount);
		}
		//if it is not the null character at the end of the converted string, there are extra characters 
		else if ('\0' != *end) {
			fprintf(stderr, "%s: extra characters at end of input: %s\n", donPtr->amount, end);
		}
		//when it is unsuccessful and stores ERANGE in errno, check if it was caused by being out of range 
		else if ((LONG_MIN == intTest || LONG_MAX == intTest) && ERANGE == errno) {
			fprintf(stderr, "%s Error out of range of long int\n", donPtr->amount);
		}
		//if the integer is greater then the acceptable max
		else if (intTest > INT_MAX) {
			fprintf(stderr, "%f greater than INT_MAX\n", intTest);
		}
		//if the integer is less then the acceptable min 
		else if (intTest < 0) {
			fprintf(stderr, "%f less than zero\n", intTest);
		}
		//if there were no errors, cast intTest into an int and store in validInt
		else {
			//validInt = (int)intTest;
			cont = true;
		}
	}
	return intTest;
	//return donPtr->amount;
}

void validZip(Donation* donPtr) {
	bool cont = false;
	//continue while incorrect input
	while (!cont) {

		fgets(donPtr->zip, BUFF_LENGTH, stdin);

		//remove ending
		size_t inputLength = strnlen(donPtr->zip, BUFF_LENGTH);
		if (inputLength > 0 && donPtr->zip[inputLength - 1] == '\n')
		{
			donPtr->zip[inputLength - 1] = '\0';
			inputLength--;
		}
		//test for valid integer
		char* end;
		errno = 0;
		long intTest = strtol(donPtr->zip, &end, 10);
		//if the string matches the ending character
		if (end == donPtr->zip) {
			fprintf(stderr, "%s: not an integer\n", donPtr->zip);
		}
		//if it is not the null character at the end of the converted string, there are extra characters 
		else if ('\0' != *end) {
			fprintf(stderr, "%s: extra characters at end of input: %s\n", donPtr->zip, end);
		}
		//when it is unsuccessful and stores ERANGE in errno, check if it was caused by being out of range 
		else if ((LONG_MIN == intTest || LONG_MAX == intTest) && ERANGE == errno) {
			fprintf(stderr, "%s Error out of range of long int\n", donPtr->zip);
		}
		//if the integer is greater then the acceptable max
		else if (intTest > INT_MAX) {
			fprintf(stderr, "%ld greater than INT_MAX\n", intTest);
		}
		//if the integer is less then the acceptable min 
		else if (intTest < 0) {
			fprintf(stderr, "%ld less than zero\n", intTest);
		}
		//if zip is not 5 numbers
		else if (inputLength > 5 || inputLength < 5) {
			puts("Invalid zip length");
		}
		else if (donPtr->zip[0] == 0) {
			puts("Cannot start with zero");
		}
		//if there were no errors, cast intTest into an int and store in validInt
		else {
			cont = true;
		}
	}

}

void login(Donation* donPtr, Organization* orgPtr) {
	char email[BUFF_LENGTH];
	char password[BUFF_LENGTH];
	bool correct = false;
	bool correctP = false;
	int counter = 0;
	int counterP = 0;
	puts("Enter email");
	while (!correct && counter != 2) {
		fgets(email, BUFF_LENGTH, stdin);
		if (strcmp(email, orgPtr->emailAddress) != 0) {
			puts("Incorrect email");
			counter++;
		}
		else {
			puts("Enter password");
			while (!correctP && counterP != 2) {
				fgets(password, BUFF_LENGTH, stdin);
				if (strcmp(password, orgPtr->password) != 0) {
					puts("Incorrect password");
					counterP++;
				}
				else {
					correctP = true;
					displayOrganization(orgPtr);
				}
			}
			correct = true;
		}
	}
	puts("Going back to donations mode");
	setUpDonation(donPtr, orgPtr);
}

void displayOrganization(Organization* orgPtr) {
	//puts("\nMAKE A DIFFERENCE BY YOUR DONATION");
	printf("Organization name: %s\n", orgPtr->organizationName);
	printf("Total Number of Donations: %d\n", orgPtr->numDonations);
	printf("Total Amount Raised: %f\n", orgPtr->donations);
	printf("Total amount paid for credit card processing: %f\n", orgPtr->creditCard);
}
