//Iteration one - Set up organization, prompt for donations, and display results after logging in 
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

//constants
#define CHOICE_SIZE 2
#define BUFF_LENGTH 80
#define FEE 0.031
#define FOLDER_PATH	"C:\\Users\\Mordred\\Documents\\GitHubRepos\\CS2060\\fundraiser\\"
#define TXT ".txt"

//Structures
typedef struct organization {
	char organizationName[BUFF_LENGTH];
	char name[BUFF_LENGTH];
	char emailAddress[BUFF_LENGTH];
	char purpose[BUFF_LENGTH];
	char goalAmount[BUFF_LENGTH];
	char password[BUFF_LENGTH];
	char url[BUFF_LENGTH];
	char urlFull[BUFF_LENGTH]; 
	char file[BUFF_LENGTH]; 
	double donations;
	int numDonations;
	double creditCard;
	struct organization* next; 
}Organization;

typedef struct donation {
	char amount[BUFF_LENGTH];
	char name[BUFF_LENGTH];
	char zip[BUFF_LENGTH];
	double totalDonation;
	bool cont; 
}Donation;

//functions
bool correctYN();
void setUpOrganization(Organization* orgPtr);
void displayOrganization(Organization* orgPtr);
void insert(Organization** headPtr);
int compare(char* name, char* input);
void fGets(char* input);
bool validInt(char* input);
bool validEmail(char* input); 
bool validPassword(char* input); 
void createURL(Organization* orgPtr); 
void createRecieptFile(char* name, char* file);
void setUpDonation(Donation* donPtr, Organization* orgPtr);
void selectOrg(Organization** headPtr, Donation* donPtr);
bool validZip(char* input); 
void reciept(char* orgName, double donTotal, char* file);
void cardFee(Donation* donPtr, Organization* orgPtr);
void login(Donation* donPtr, Organization* orgPtr);
void orgFile(Organization* headPtr);
void displayFundraiser(Organization* orgPtr); 
void printFundraisers(Organization* headPtr); 
void deleteList(Organization** headPtr); 


int main(void) {
	//create organization structure
	Organization* orgHeadPtr = NULL;
	//create donation structure
	Donation don;
	Donation* donPtr = &don; 
	bool cont = true;
	bool orgCont = false; 
	donPtr->cont = false; 
	//insert orgs
	while (cont) {
		insert(&orgHeadPtr);
		puts("Do you want to enter another organization? y/n");
		cont = correctYN();
	}

	//continue until organization login is successful
	while (!orgCont && !donPtr->cont) {
		printFundraisers(orgHeadPtr);
		puts("Enter the name of the organization you want to register.");
		selectOrg(&orgHeadPtr, donPtr);
	}
	//create file for orgs
	orgFile(orgHeadPtr); 
	//deallocate list
	deleteList(&orgHeadPtr);

	return 0; 
}
//insert into linked list
void insert(Organization** headPtr) {
	//create new org
	Organization* newOrgPtr = (Organization*)malloc(sizeof(Organization));
	//prompt data
	setUpOrganization(newOrgPtr);
	newOrgPtr->next = NULL;

	//head or greater
	if (*headPtr == NULL || (compare((*headPtr)->organizationName, newOrgPtr->organizationName) >= 0)) {
		newOrgPtr->next = *headPtr;
		*headPtr = newOrgPtr;
		//make it stop aaa
		return;
	}

	//find place to insert
	Organization* current = *headPtr;
	while (current->next != NULL && (compare(current->organizationName, newOrgPtr->organizationName) <= 0)) {
		current = current->next;
	}
	//move on yall
	newOrgPtr->next = current->next;
	current->next = newOrgPtr;

	printf("\nThank you %s. The url to raise funds for %s is %s\n", newOrgPtr->name, newOrgPtr->organizationName, newOrgPtr->url);
}
//compare strings 
int compare(char* name, char* input) {
	char a[BUFF_LENGTH];
	strcpy(a, name);
	//make it all lower case 
	for (int i = 0; i < strlen(a); i++)
	{
		a[i] = tolower(a[i]);
	}
	for (int i = 0; i < strlen(input); i++)
	{
		input[i] = tolower(input[i]);
	}
	int result = strcmp(a, input);
	return result;
}
//return true or false depending on yes/no prompt
bool correctYN() {
	char yesNo[BUFF_LENGTH];
	bool correct = false;
	bool cont = false;
	//cont till yes or no 
	while (!cont) {
		fGets(yesNo);
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
//prompt organization questions 
void setUpOrganization(Organization* orgPtr) {
	bool cont = false;
	//initialize to 0
	orgPtr->donations = 0;
	orgPtr->numDonations = 0;
	orgPtr->creditCard = 0;
	//fill in organization info
	puts("Enter organization name");
	fGets(orgPtr->organizationName);
	puts("Enter your name");
	fGets(orgPtr->name);
	puts("Enter purpose");
	fGets(orgPtr->purpose);
	puts("Enter goal amount");
	orgPtr->donations = 0; 
	bool contInt = false;
	//loop till valid int
	while (!contInt) {
		fGets(orgPtr->goalAmount);
		contInt = validInt(orgPtr->goalAmount);
	}
	//continue loop while email is incorrect
	while (!cont) {
		bool validEm = false;
		while (!validEm) {
			puts("Enter email");
			fGets(orgPtr->emailAddress);
			validEm = validEmail(orgPtr->emailAddress); 
		}

		puts("\nIs this email correct? (y)es y/Y or (n)o n/N");
		bool correct = correctYN(); 
		//create password only if correctEmail function returns true 
		if (correct == true) {
			bool validPass = false;
			while (!validPass) {
				puts("Create Password");
				fGets(orgPtr->password);
				validPass = validPassword(orgPtr->password); 
			}
			cont = true;
		}
		//loop until valid email 
		else {
			cont = false;
		}
	}
	//create url for org
	createURL(orgPtr);
	//create reciept file for org
	createRecieptFile(orgPtr->url, orgPtr->file);
}
//bootleg fgets
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
//valid email format 
bool validEmail(char* input) {
	bool cont = true;
	int length = strlen(input); 
	//declare variables 
	int i = 0,
		at = -1,
		dot = -1;
	//count @ and . locations 
	while (input[i]) {
		if (input[i] == '@') {
			at = i;
		}
		if (input[i] == '.') {
			dot = i;
		}
		i++; 
	}
	if (at == -1 || dot == -1) {
		puts("Needs @ and/or .");
		cont = false; 
	}
	if (at > dot) {
		puts("Not valid location");
		cont = false;
	}
	if (length - dot != 4) {
		puts("Not valid extention");
		cont = false; 
	}
	if (dot - at <= 1) {
		puts("Needs domain"); 
		cont = false;
	}
	if (at == 0) {
		puts("Needs username");
		cont = false;
	}
	return cont; 
}
//valid password format
bool validPassword(char* input) {
	bool cont = true;
	//declare 
	int i = 0,
		lower = 0,
		upper = 0,
		digit = 0;
	//iterate through password and count number of lower, upper, and digits 
	while (input[i]) {
		if (islower(input[i]))
			lower++;
		if (isupper(input[i]))
			upper++;
		if (isdigit(input[i]))
			digit++;
		
		i++;
	}
	if (strlen(input) < 7) {
		puts("Must have at least 7 characters");
		cont = false;
	}
	if (lower == 0) {
		puts("Needs lowercase");
		cont = false;
	}
	if (upper == 0) {
		puts("Needs uppercase");
		cont = false;
	}
	if (digit == 0) {
		puts("Needs number");
		cont = false;
	}
	return cont; 
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
	strcpy(orgPtr->urlFull, orgPtr->url);
	strcat(front, orgPtr->urlFull);
	strcat(front, back);
	strcpy(orgPtr->urlFull, front);
	printf("\nThank you %s. The url to raise funds for %s is %s\n", orgPtr->name, orgPtr->organizationName, orgPtr->urlFull);

}
//creates reciept file for later
void createRecieptFile(char* name, char* file) {
	FILE* filePtr;
	//combine into one string
	char path[BUFF_LENGTH];
	strcpy(path, FOLDER_PATH);
	strcat(path, name);
	sprintf(file, "%s.txt", path); 

	filePtr = fopen(file, "w");
	//check if you can make file
	if (filePtr == NULL) {
		printf("Unable to create file.\n");
	}

	//close file
	fclose(filePtr);
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
			cont = true;
			puts("Enter your name");
			fgets(donPtr->name, BUFF_LENGTH, stdin);
			bool vZip = false;
			while (!vZip) {
				puts("Enter your 5 digit zip code");
				fGets(donPtr->zip); 
				vZip = validZip(donPtr->zip);
			}
			//incriment number of donations
			orgPtr->numDonations++;
			cardFee(donPtr, orgPtr);
			//ask for reciept
			reciept(orgPtr->organizationName, donPtr->totalDonation, orgPtr->file);
		}
	}
}
//select org from list
void selectOrg(Organization** headPtr, Donation* donPtr) {
 
	Organization* current = *headPtr;

	char name[80];
	fGets(name);
	puts((*headPtr)->organizationName);
	//loop while match not found
	while (current != NULL && (compare(current->organizationName, name) != 0)) {
		
			current = current->next;

	}
	//if it is found, continue to set up donation
	if (current != NULL) {
		setUpDonation(donPtr, current);
	}
	if (current == NULL) {
		printf("%s not found", name);
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
	printf("\nThank you for your donation. There is a 3.1 percent credit card processing fee of %.2f. %.2f will be donated.", 
		donationAmount, total);
	orgPtr->donations += total; 
}

//prompts for reciept 
void reciept(char* orgName, double donTotal, char* file) {
	FILE* filePtr;
	bool cont = false;
	puts("Do you want a reciept? (y)es y/Y or (n)o n/N");
	//continue to ask until user inputs acceptable answer 
	while (!cont) {
		bool correct = correctYN();
		//create password only if correctEmail function returns true 
		if (correct == true) {
			//opens reciept file for org
			filePtr = fopen(file, "a");
			cont = true;
			printf("\nOrganization: %s", orgName);
			fprintf(filePtr, "Organization: %s", orgName);
			printf("\nDonation Amount: %.2f", donTotal);
			fprintf(filePtr, "\nDonation Amount: %.2f", donTotal);
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
				fprintf(filePtr, "\nDonation Date : % 02d / % 02d / % d - % 02d : % 02d : % 02d AM\n", day, month, year, hours, minutes, seconds);
			}
			//if pm
			else {    
				printf("\nDonation Date:  %02d/%02d/%d - %02d:%02d:%02d PM\n", day, month, year, hours - 12, minutes, seconds);
				fprintf(filePtr, "\nDonation Date : % 02d / % 02d / % d - % 02d : % 02d : % 02d PM\n", day, month, year, hours - 12, minutes, seconds);
			}
			//close file
			fclose(filePtr);
		}
		//move on to next step
		else if (correct == false) {
			cont = true;
		}
		else {
			puts("Please enter (y)es y/Y or (n)o n/N");
		}
	}
}

//validate zip code
bool validZip(char* input) {
	bool cont = false;

		//test for valid integer
		char* end;
		errno = 0;
		int inputLength = strlen(input); 
		long intTest = strtol(input, &end, 10);
		//create character to check if zip starts with 0 
		char first;
		first = input[0];
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
		return cont; 
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
	while (!correct && counter != 3) {
		fGets(email);
		//if input does not match email
		if (strcmp(email, orgPtr->emailAddress) != 0) {
			puts("Incorrect email");
			counter++;
		}
		else {
			puts("Enter password");
			//loop twice to prompt password
			while (!correctP && counterP != 3) {
				fGets(password);
				//if input does not match password 
				if (strcmp(password, orgPtr->password) != 0) {
					puts("Incorrect password");
					counterP++;
				}
				//move on to display information 
				else {
					correctP = true;
					//end while loop in main
					donPtr->cont = true; 
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
//create file for all orgs
void orgFile(Organization* headPtr) {
	FILE* filePtr;
	filePtr = fopen("C:\\Users\\Mordred\\Documents\\GitHubRepos\\CS2060\\fundraiser\\orgs.txt", "w");
	//check if you can make file
	if (filePtr == NULL) {
		printf("Unable to create file.\n");
	}
	Organization* current = headPtr;

	//put into file line by line
	while (current != NULL) {
		fprintf(filePtr, "Organization name: %s\n", current->organizationName);
		fprintf(filePtr, "Total Number of Donations: %d\n", current->numDonations);
		fprintf(filePtr, "Total Amount Raised: $%.2f\n", current->donations);
		fprintf(filePtr, "Total amount paid for credit card processing: $%.2f\n", current->creditCard);
		current = current->next;
	}
	//close file
	fclose(filePtr);
}
//print info to admin
void displayOrganization(Organization* orgPtr) {
	printf("Organization name: %s\n", orgPtr->organizationName);
	printf("Total Number of Donations: %d\n", orgPtr->numDonations);
	printf("Total Amount Raised: $%.2f\n", orgPtr->donations);
	printf("Total amount paid for credit card processing: $%.2f\n", orgPtr->creditCard);
}
//print all orgs
void printFundraisers(Organization* headPtr) {
	Organization* current = headPtr;
	//start from the beginning
	if (current == NULL) {
		puts("No organizations in list");
	}
	while (current != NULL) {
		puts("\nOrganization    Goal Amount    Donations");
		printf("%s           $%s         $%.2f \n", current->organizationName, current->goalAmount, current->donations);
		current = current->next;
	}
}
//print specific org
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
//orgs begone 
void deleteList(Organization** headPtr) {
	Organization* current = *headPtr;
	Organization* next;
	//start from the beginning
	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
	*headPtr = NULL;
}