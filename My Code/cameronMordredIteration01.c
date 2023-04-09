//Iteration one - Set up organization, prompt for donations, and display results after logging in 
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
void fGets(char* input);
bool validInt(char* input);
bool correctEmail();
void createURL(Organization* orgPtr); 
void setUpDonation(Donation* donPtr, Organization* orgPtr);
void validZip(Donation* donPtr);
void reciept(Organization* orgPtr, Donation* donPtr); 
void cardFee(Donation* donPtr, Organization* orgPtr);
void login(Donation* donPtr, Organization* orgPtr);
void displayFundraiser(Organization* orgPtr); 


int main(void) {
	//create organization structure
	Organization org1;
	Organization* org1Ptr = &org1;
	//initialize variables to zero
	org1Ptr->donations = 0;
	org1Ptr->creditCard = 0;
	org1Ptr->numDonations = 0;
	//create donation structure
	Donation don1;
	Donation* don1Ptr = &don1; 
	
	setUpOrganization(org1Ptr);
	createURL(org1Ptr);
	printf("\nThank you %s. The url to raise funds for %s is %s\n", org1.name, org1.organizationName, org1.url);
	//displayFundraiser(org1Ptr); 
	setUpDonation(don1Ptr, org1Ptr);

	return 0; 
}
//prompt organization questions 
void setUpOrganization(Organization* orgPtr) {
	bool cont = false;
	//fill in organization info
	puts("Enter organization name");
	fgets(orgPtr->organizationName, BUFF_LENGTH, stdin);
	puts("Enter your name");
	fgets(orgPtr->name, BUFF_LENGTH, stdin);
	puts("Enter purpose");
	fgets(orgPtr->purpose, BUFF_LENGTH, stdin);
	puts("Enter goal amount");
	bool contInt = false;
	//loop till valid int
	while (!contInt) {
		fGets(orgPtr->goalAmount);
		contInt = validInt(orgPtr->goalAmount);
	}
	//continue loop while email is incorrect
	while (!cont) {
		puts("Enter email");
		fgets(orgPtr->emailAddress, BUFF_LENGTH, stdin);
		bool correct = correctEmail();
		//create password only if correctEmail function returns true 
		if (correct == true) {
			puts("Create Password");
			fgets(orgPtr->password, BUFF_LENGTH, stdin);
			cont = true;
		}
		//loop until valid email 
		else {
			cont = false;
		}
	}
}
void fGets(char* input) {
	fgets(input, BUFF_LENGTH, stdin);
	//remove ending
	size_t inputLength = strnlen(input, BUFF_LENGTH);
	if (inputLength > 0 && input[inputLength - 1] == '\n')
	{
		input[inputLength - 1] = '\0';
		inputLength--;
	}
}
//validate goal amount 
bool validInt(char* input) {
	
	bool cont = false;
		//test for valid integer
		char* end;
		errno = 0;
		//int validInt = 0;
		double intTest = strtod(input, &end);
		//if the string matches the ending character
		if (end == input) {
			fprintf(stderr, "%s: not an integer\n", input);
		}
		//if it is not the null character at the end of the converted string, there are extra characters 
		else if ('\0' != *end) {
			fprintf(stderr, "%s: extra characters at end of input: %s\n", input, end);
		}
		//when it is unsuccessful and stores ERANGE in errno, check if it was caused by being out of range 
		else if ((LONG_MIN == intTest || LONG_MAX == intTest) && ERANGE == errno) {
			fprintf(stderr, "%s Error out of range of long int\n", input);
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
		return cont; 
}

//checks if email is correct according to user
bool correctEmail() {
	//variables
	char yesNo[BUFF_LENGTH];
	bool correct = false; 
	bool cont = false;
	puts("\nIs this email correct? (y)es y/Y or (n)o n/N");
	//loop until email is correct
	while (!cont) {
		fgets(yesNo, BUFF_LENGTH, stdin);
		//remove extra elements
		size_t inputLength = strnlen(yesNo, BUFF_LENGTH);
		if (inputLength > 0 && yesNo[inputLength - 1] == '\n')
		{
			yesNo[inputLength - 1] = '\0';
			inputLength--;
		}
		//if user enters y/Y then proceed to next step 
		if (strcmp(yesNo, "y") == 0 || strcmp(yesNo, "Y") == 0) {
			correct = true;
			cont = true;
		}
		else if (strcmp(yesNo, "n") == 0 || strcmp(yesNo, "N") == 0) {
			correct = false; 
			cont = true;
		}
		//continues until either y or n is entered 
		else {
			puts("Please enter (y)es y/Y or (n)o n/N");
		}
	}
	return correct; 
}
//create url using organization name
void createURL(Organization* orgPtr) {
	//create strings holding url parts
	char front[BUFF_LENGTH] = "https:donate.com/";
	char back[BUFF_LENGTH] = "?form=popup#";
	//copy organization name to url
	strcpy(orgPtr->url, orgPtr->organizationName);
	char* strPtr = orgPtr->url;
	//loop through url name with pointer and replace spaces with - 
	while ((strPtr = strchr(strPtr, ' ')) != NULL) {
		*strPtr++ = '-';
	}
	//combine strings
	strcat(front, orgPtr->url);
	strcat(front, back);
	strcpy(orgPtr->url, front);

}

//prompts donation questions
void setUpDonation(Donation* donPtr, Organization* orgPtr) {
	bool cont = false; 
	//loop until organization enters q/Q
	while (!cont) {
		displayFundraiser(orgPtr);
		//always prompt for amount
		puts("\nEnter donation amount");
		fGets(donPtr->amount);
		//if q is entered, skip regular donation and move to login 
		if (strcmp(donPtr->amount, "q") == 0 || strcmp(donPtr->amount, "Q") == 0) {
			cont = true;
			login(donPtr, orgPtr); 
		}
		//if regular donation, prompt for info 
		else if (validInt(donPtr->amount) == true) {

			puts("Enter your name");
			fgets(donPtr->name, BUFF_LENGTH, stdin);
			puts("Enter your 5 digit zip code");
			validZip(donPtr);
			//incriment number of donations
			orgPtr->numDonations++;
			cardFee(donPtr, orgPtr);
			//ask for reciept
			reciept(orgPtr, donPtr);
		}
	}
}
//calculates fee
void cardFee(Donation* donPtr, Organization* orgPtr) {
	char* end;
	//convert to double
	double donationAmount = strtod(donPtr->amount, &end);
	//calculate card fee
	double cardFee = donationAmount * FEE; 
	//calculate total
	double total = donationAmount + cardFee;
	//send info to structure 
	orgPtr->creditCard += cardFee;
	donPtr->totalDonation = total; 
	printf("\nThank you for your donation. There is a 2.9 percent credit card processing fee of %.2f. %.2f will be donated.", 
		donationAmount, total);
	orgPtr->donations += total; 
}

//prompts for reciept 
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
			printf("Donation Amount: %.2f", donPtr->totalDonation);
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
				printf("\nDonation Date:  %02d/%02d/%d - %02d:%02d:%02d AM\n", day, month, year, hours, minutes, seconds);
			}
			//if pm
			else {    
				printf("\nDonation Date:  %02d/%02d/%d - %02d:%02d:%02d PM\n", day, month, year, hours - 12, minutes, seconds);
			}

		}
		//move on to next step
		else if (strcmp(yesNo, "n") == 0 || strcmp(yesNo, "N") == 0) {
			cont = true;
		}
		else {
			puts("Please enter (y)es y/Y or (n)o n/N");
		}
	}
}


//validate zip code
void validZip(Donation* donPtr) {
	bool cont = false;
	
	//continue while incorrect input
	while (!cont) {

		fgets(donPtr->zip, BUFF_LENGTH, stdin);

		//remove ending elements
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
		//create character to check if zip starts with 0 
		char first;
		first = donPtr->zip[0];
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
		//if zip starts with 0
		else if (first == '0') {
			puts("Cannot start with zero");
		}
		//if there were no errors, cast intTest into an int and store in validInt
		else {
			cont = true;
		}
	}

}

//login for organization
void login(Donation* donPtr, Organization* orgPtr) {
	char email[BUFF_LENGTH];
	char password[BUFF_LENGTH];
	bool correct = false;
	bool correctP = false;
	int counter = 0;
	int counterP = 0;
	puts("\nEnter email");
	//loop twice to prompt email
	while (!correct && counter != 2) {
		fgets(email, BUFF_LENGTH, stdin);
		//if input does not match email
		if (strcmp(email, orgPtr->emailAddress) != 0) {
			puts("Incorrect email");
			counter++;
		}
		else {
			puts("Enter password");
			//loop twice to prompt password
			while (!correctP && counterP != 2) {
				fgets(password, BUFF_LENGTH, stdin);
				//if input does not match password 
				if (strcmp(password, orgPtr->password) != 0) {
					puts("Incorrect password");
					counterP++;
				}
				//move on to display information 
				else {
					correctP = true;
					displayOrganization(orgPtr);
				}
			}
			correct = true;
		}
	}
	//go back to donations mode if incorrect email and password were entered twice
	if (!correct || !correctP) {
		puts("\nGoing back to donations mode");
		setUpDonation(donPtr, orgPtr);
	}
}

//print info to admin
void displayOrganization(Organization* orgPtr) {
	printf("Organization name: %s\n", orgPtr->organizationName);
	printf("Total Number of Donations: %d\n", orgPtr->numDonations);
	printf("Total Amount Raised: %.2f\n", orgPtr->donations);
	printf("Total amount paid for credit card processing: %.2f\n", orgPtr->creditCard);
}

void displayFundraiser(Organization* orgPtr) {
	puts("\nMAKE A DIFFERENCE BY YOUR DONATION");
	printf("Organization name: %s\n", orgPtr->organizationName);
	printf("Purpose: %s\n", orgPtr->purpose);
	printf("We have currently raised $%.2f\n", orgPtr->donations);
	char* end;
	//convert to double
	double amount = strtod(orgPtr->goalAmount, &end);
	double percent = (orgPtr->donations / amount) * 100;
	if (orgPtr->donations >= amount) {
		puts("We have reached our goal but can still use the donations.");
	}
	else {
		printf("We are %.2f percent towards our goal of $%.2f\n", percent, amount);
	}
}
