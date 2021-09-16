#include <stdio.h>

int main() {
    int numerator;
    int denomenator;
    
    printf("Enter a numerator: ");
    scanf("%d", &numerator);

    printf("Enter a denomenator: ");
    scanf("%d", &denomenator);

    if (numerator % denomenator == 0) {
        printf("There is no remainder");
    } else {
        printf("There is a denomenator");
    }

    return 0;
}