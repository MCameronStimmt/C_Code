//Mordred Cameron HW04

#include <stdio.h>
#include <stdbool.h>
//constants
#define STUDENTS 4
#define GRADE_CATEGORIES 5
#define CATEGORIES "1. Learning Activity 2. Homework 3. Project 4. Midterm 5. Final "
const double GRADE_CATEGORY_WEIGHT[] = { 0.1, 0.3, 0.3, 0.15, .15 };
const int MAX_GRADE = 105;

//functions
void printWeight(int, const double weight[]);
void promptGrades(int, int, int, int grades[][GRADE_CATEGORIES]);
void calculateGrade(const int studentGrades[][GRADE_CATEGORIES], double totalGrade[], const double weight[], int, int);
int isValid(int);
void printArray(const int studentGrades[][GRADE_CATEGORIES], int, int);
void print1DArray(const double grades[], int);
char printLetter(double, int);
double average(const double grades[], int);

int main(void) {
    int grades[STUDENTS][GRADE_CATEGORIES];
    double totalGrades[STUDENTS];

    printf("This program will calculate the grades for these categories %s", CATEGORIES);
    printWeight(GRADE_CATEGORIES, GRADE_CATEGORY_WEIGHT);
    //prompt for grades
    printf("The correct order to enter grades for each student is: %s", CATEGORIES);
    promptGrades(GRADE_CATEGORIES, STUDENTS, MAX_GRADE, grades);
    //print 2D array
    puts("\nGrades entered for each student\n");
    printArray(grades, STUDENTS, GRADE_CATEGORIES);

    puts("\n\nFinal grades for students, respectively: \n");
    calculateGrade(grades, totalGrades, GRADE_CATEGORY_WEIGHT, STUDENTS, GRADE_CATEGORIES);
    //print array
    print1DArray(totalGrades, STUDENTS);

    printf("\n\nClass average is %.1lf\n", average(totalGrades, STUDENTS));

}

//functions
void printWeight(int catagorySize, const double weight[]) {
    puts("\nThe category weights are");

    for (size_t i = 0; i < catagorySize; i++) {
        int catNum = (int)i + 1;
        printf("Catagory %d weight is: %.2lf \n", catNum, weight[i]);
    }

}

void promptGrades(int catagorySize, int students, int maxGrade, int grades[][GRADE_CATEGORIES]) {
    
    for (size_t i = 0; i < students; i++) {
        for (size_t j = 0; j < catagorySize; j++) {
            //print list starting at 1
            int stud = (int)i + 1;
            int catNum = (int)j + 1;
            printf("\nEnter the grade for each category for student %d, category %d: ", stud, catNum);
            //set current array element to input
            grades[i][j] = isValid(maxGrade);
        } 
    }
}

void printArray(const int grades[][GRADE_CATEGORIES], int students, int catagorySize){

    for (size_t i = 0; i < students; i++) {
        //print students starting at 1
        int stud = (int)i + 1;
        printf("\nStudent %d:  ", stud);
        //print grades in format
        for (size_t j = 0; j < catagorySize; j++) {
            printf("%.2d ", grades[i][j]);
        }
    }
}

void print1DArray(const double grades[], int students) {
    for (size_t i = 0; i < students; i++) {
        //print students starting at 1
        int stud = (int)i + 1;
        printf("\nStudent %d:  %.1lf  %c", stud, grades[i], printLetter(grades[i], students));
    }
}

void calculateGrade(const int grades[][GRADE_CATEGORIES], double totalGrade[], const double weight[], int students, int catagorySize) {
    double gradeWeight = 0;
   // double total = 0;
    for (size_t i = 0; i < students; i++) {
        for (size_t j = 0; j < catagorySize; j++) {
            gradeWeight += weight[j] * grades[i][j];

        }
        totalGrade[i] = gradeWeight;
        //clear grade 
        gradeWeight = 0;
    }
}

char printLetter(double grade, int students) {
    char letter = 'F';
    if (grade >= 90) {
        letter = 'A';
    }
    else if (grade >= 80) {
        letter = 'B';
    }
    else if (grade >= 70) {
        letter = 'C';
    }
    else if (grade >= 60) {
        letter = 'D';
    }
    else {
        letter = 'F';
    }
    return letter;
}

double average(const double grades[], int students) {
    double average = 0;
    for (size_t i = 0; i < students; i++) {
        average += grades[i];
    }
    return (average / students);
}

int isValid(int maxGrade) {
    bool valid = false;
    int scanfReturn = 0;
    int input = 0;

    while (!valid) {
        //prompt input
        scanfReturn = scanf("%d", &input);
        //clear buffer
        while ((getchar()) != '\n');
        //check for int
        if (scanfReturn == 1) {
            //check in range
            if (input >= 0 && input <= maxGrade) {

                valid = true;
            }
            else {
                printf("Please enter 1 through %.d \n", maxGrade);
            }
        }
        else {
            puts("You did not enter a number");
        }
    }

    return input;
}