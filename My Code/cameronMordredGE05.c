//LinkedLists pets
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFF_LENGTH 80

typedef struct pet {
	char name[BUFF_LENGTH];
	int age;
	struct pet* nextPtr; 
}Pet;

Pet* headPtr = NULL; 

//functions
bool correct();
void insertPet(Pet** headPtr);
int compare(Pet* currentPetPtr, char* name);
void printList(Pet* headPtr);
void fGets(char* input);
void toFile(Pet* headPtr); 
void deletePet(Pet** headPtr, char* input);
void deleteList(Pet** headPtr);

int main(void) {
	//Pet pet;
	Pet* head = NULL;
	bool cont = false;
	bool delCont = false;
	//insert pets
	while (!cont) {
		insertPet(&head);
		puts("Do you want to enter another pet? y/n");
		cont = correct();
	}

	printList(head); 
	toFile(head); 
	//delete pets
	while (!delCont) {
		puts("Do you want to delete a pet? y/n");
		delCont = correct();
		if (!delCont) {
			puts("Enter name");
			char name[80];
			fGets(name);
			deletePet(&head, name);
			printList(head); 
		}

	}
	puts("Deleting List"); 
	deleteList(&head); 
	printList(head);
	return 0;
}

//prompt yes or no 
bool correct() {
	char yesNo[BUFF_LENGTH];
	bool correct = false;
	bool cont = false;
	//puts("Do you want to enter another pet? y/n");
	//cont till yes or no 
	while (!cont) {
		fGets(yesNo);
		//if user enters y/Y then proceed to next step 
		if (strcmp(yesNo, "y") == 0 || strcmp(yesNo, "Y") == 0) {
			correct = false;
			cont = true;
		}
		else if (strcmp(yesNo, "n") == 0 || strcmp(yesNo, "N") == 0) {
			correct = true;
			cont = true;
		}
		//continues until either y or n is entered 
		else {
			puts("Please enter (y)es y/Y or (n)o n/N");
		}
	}
	return correct;
}
//insert into linked list
void insertPet(Pet** headPtr) {

	char age[BUFF_LENGTH];
	char* end;

	Pet* newPetPtr = (Pet*)malloc(sizeof(Pet));
	//prompt data
	puts("Enter name");
	fGets(newPetPtr->name);
	puts("Enter age");
	fGets(age);
	newPetPtr->age = (int)strtod(age, &end);
	newPetPtr->nextPtr = NULL;

	//head or greater
	if (*headPtr == NULL || (compare(*headPtr, newPetPtr->name) >= 0)){
		newPetPtr->nextPtr = *headPtr;
		*headPtr = newPetPtr;
		//make it stop aaa
		return;
	}

	//find place to insert
	Pet* current = *headPtr;
	while (current->nextPtr != NULL && (compare(current, newPetPtr->name) <= 0)) {
		current = current->nextPtr;
	}
	//move on yall
	newPetPtr->nextPtr = current->nextPtr;
	current->nextPtr = newPetPtr;
}

//compare strings 
int compare(Pet* currentPetPtr, char* name) {
	char a[80];
	strcpy(a, currentPetPtr->name);
	//make it all lower case 
	for (int i = 0; i < strlen(a); i++)
	{
		a[i] = tolower(a[i]);
	}
	for (int i = 0; i < strlen(name); i++)
	{
		name[i] = tolower(name[i]);
	}
	int result = strcmp(a, name);
	return result; 
}
//print linked list
void printList(Pet* headPtr) {
	Pet* current = headPtr;
	//start from the beginning
	while (current != NULL) {
		printf("%s is %d years old\n", current->name, current->age);
		current = current->nextPtr;
	}
	if (current == NULL) {
		puts("No pets in list");
	}
}

void fGets(char* input) {
	//bootleg fgets
	fgets(input, BUFF_LENGTH, stdin);
	//remove ending
	size_t inputLength = strnlen(input, BUFF_LENGTH);
	if (inputLength > 0 && input[inputLength - 1] == '\n')
	{
		input[inputLength - 1] = '\0';
		inputLength--;
	}
}
//sends info to file
void toFile(Pet* headPtr) {
	FILE* filePtr;
	char info[80];
	filePtr = fopen("C:\\Users\\Mordred\\Documents\\GitHubRepos\\CS2060\\Files\\pets.txt", "w");
	//check if you can make file
	if (filePtr == NULL) {
		printf("Unable to create file.\n");
	}
	Pet* currentPtr = headPtr;

	//put into file line by line
	while (currentPtr != NULL) {
		sprintf(info, "%s is %d years old\n", currentPtr->name, currentPtr->age);
		fputs(info, filePtr);
		currentPtr = currentPtr->nextPtr;
	}
	//close file
	fclose(filePtr);
}

//deletes pets
void deletePet(Pet** headPtr, char* input) {
	Pet* current = *headPtr;
	Pet* previous; 

	// If head 
	if (current != NULL && (compare(current, input) == 0)) {
		//move to next
		*headPtr = current->nextPtr; 
		//deallocate
		free(current); 
		//make it stop
		return;
	}
	// move on
	while (current != NULL && (compare(current, input) != 0)) {
		previous = current;
		current = current->nextPtr;
	}
	// if not found
	if (current == NULL) {
		puts("Not found");
		//make it stoppp 
		return;
	}
	// remove node
	previous->nextPtr = current->nextPtr;
	//deallocate
	free(current); 
	
}
//pets begone 
void deleteList(Pet** headPtr) {
	Pet* current = *headPtr;
	Pet* next;
	//start from the beginning
	while (current != NULL) {
		next = current->nextPtr;
		free(current);
		current = next; 
	}
	*headPtr = NULL;
}