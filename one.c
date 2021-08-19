#include <stdio.h>

#define PI 3.14

/*
    This first program serves simple to receive a radius length
    and provides the user with the area of the circle
*/

int main() {
    float radius;
    printf("Enter the radius: ");
    scanf("%f", &radius);
    float a = PI * (radius * radius);
    printf("The area is: %.2f", a);

    return 0;
}