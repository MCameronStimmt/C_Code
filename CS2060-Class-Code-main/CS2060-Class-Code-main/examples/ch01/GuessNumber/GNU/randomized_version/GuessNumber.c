/*
* The program randomly generates numbers   
* between 1 and 1000 for the user to guess.
*/


// Preprocessor
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Declaring Global Variables
#define MIN_NUMBER 1

//Declaring constant 
const int MAX_NUMBER = 100;

//declaring functions
void guessGame(void); 
bool isCorrect(int, int); 


int main(void)
{
<<<<<<< HEAD
    //
  // srand(time(0));
=======
    //randomize seed
   srand(time(0));
>>>>>>> 82a2aab7c88c3a3f64bc3085f4b08516cd0b00ef

   //start guessGame() function
   guessGame(); 

   //Required for main exit code
   return 0;
}

//Generates number between 1-100
void guessGame(void)
{
    //declare and initialize variables
   int answer = 0; 
   int guess = 0; 
   int response = 0; 

   do {

       //generates number
      answer = MIN_NUMBER + rand() % MAX_NUMBER;


      //prompt user to enter guess
      printf("Hello, I have a number between %d and %d .\n" 
          "Can you guess my number?\n"
           "Please type your first guess.", MIN_NUMBER, MAX_NUMBER);

      //do while loop for isCorrect(), could use just while loop or place while loop in isCorrect()
      do
      {
          //reads user input
          scanf("%d", &guess);
      } while (!isCorrect(guess, answer));
         
      //ask to play again
      puts("\nExcellent! You guessed the number!\n"
         "Would you like to play again?");

      printf("%s", "Please type ( 1=yes, 2=no ) ");
      scanf("%d", &response);

      puts("");
   } while (response == 1);
} 

//tests if guess is equal to answer
bool isCorrect(int g, int a)
{
    //Is the use of a boolean nessesary here? 
    bool found = false;

    //if else statement to either print hints or return true when number is guessed
    if (g == a){
        found = true;
    }else  if (g < a)
      printf( "%s", "Too low. Try again.\n? " );
   else
      printf( "%s", "Too high. Try again.\n? " );

    //returns true, but involves extra boolean variable 
   return found;
} 

