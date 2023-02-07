//Mordred Cameron HW03

#include <stdio.h>
#include <stdbool.h>

const double MIN_HOURS_AT_FLAT_RATE = 3;
const double MIN_FLAT_RATE_CHARGE = 3;
const double ADDITIONAL_HOURS_RATE = 0.75;
const double MAX_HOURS_ALLOWED = 24;
const double MAX_CHARGE_CHARGE = 12;

//func
bool isValid(double, double);
double calculateCost(double);
void displaySummary(double, int, double);

int main(void) {

    double input = 0;
    bool valid = false;
    unsigned int numberCars = 0;
    double totalCost = 0;
    double totalHours = 0;

    //loop till exit
    do {
        puts("Enter number of hours car was parked or enter -1 to quit");
        //prompt input
            double scanfReturn = scanf("%lf", &input);
            //clear buffer
            while ((getchar()) != '\n');
            //display no cars if -1 entered and then leave loop
            if (input == -1) {
                displaySummary(totalCost, numberCars, totalHours);
                valid = true;
            }
            else {
                valid = isValid(scanfReturn, input);
                if (valid == true) {
                    numberCars++;
                    totalCost += calculateCost(input);
                    totalHours += input;
                    displaySummary(calculateCost(input), numberCars, input);
                }
            }        
      
    } while (valid == false || input != -1);
  
}

bool isValid(double scanfReturn, double validInput) {

    bool valid = false;

        //check for int
        if (scanfReturn == 1) {
            //check in range
            if (validInput >= 0 && validInput <= MAX_HOURS_ALLOWED) {
                // calculate cost
                calculateCost(validInput);
                valid = true;
            }
            else {
                printf("Please enter 1 through %lf \n", MAX_HOURS_ALLOWED);
            }
        }
        else {
            puts("You did not enter a number");
        }

    return valid;
}

double calculateCost(double hours) {

    double cost = MIN_FLAT_RATE_CHARGE;
    int additionalHours = 0;

    if (hours > MIN_HOURS_AT_FLAT_RATE) {
        //caclulate cost
        additionalHours = (int)((hours - MIN_HOURS_AT_FLAT_RATE) + 1);
        cost += additionalHours * ADDITIONAL_HOURS_RATE;
    }
    if (cost > MAX_CHARGE_CHARGE) {
        cost = MAX_CHARGE_CHARGE;
    }

    return cost;
}

void displaySummary(double cost, int cars, double hours) {
    //with input
    if (hours > 0) {
        puts("Parking Garage Summary \nTotal Cars   Total Hours   Total Charge");
        printf("%.2d           %.1lf           $%.2lf \n", cars, hours, cost);
    }
    //if -1 entered
    else {
        puts("Parking Garage Summary \nTotal Cars   Total Hours   Total Charge");
        puts("There were no cars parked");
    }
}

