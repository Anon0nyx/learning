#include <stdio.h>

int main() {
    float seconds;

    printf("Enter the seconds: ");
    scanf("%f", &seconds);

    float hours;
    float minutes;
    float seconds_left;

    // 3600 seconds to an hour
    // So round how many hours by doing
    // seconds/3600
    hours = (int)(seconds/3600);

    // Once the hours have been determined
    // Find the mintues by taking the total 
    // Seconds and removing the number of seconds
    // that equate to the number of hours and then
    // take the seconds left over and see how many minutes
    // Because 60 seconds to a minutes do seconds/60
    minutes = (int)((seconds - (hours*3600))/60);

    /*
        Similarly to the minutes variable, we need to remove
        the number of seconds that equate to our hours and minutes
        by taking the total seconds and subtracting the seconds 
        equivilent for the hours an minutes, then we are left with
        the remaining seconds in the equation
    */
    seconds_left = (seconds - (hours*3600) - (minutes*60));

    printf("%0.0f Seconds is %0.0f Hours %0.0f Minutes and %0.0f Seconds", seconds, hours, minutes, seconds_left);
}