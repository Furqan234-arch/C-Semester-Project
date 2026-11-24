#include<stdio.h>
#include<string.h>
#include "clinic.h"
// Consume remaining characters up to newline to prevent scanf skipping
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}
// Allow up to 3 attempts using strcmp to validate username and password
int loginSystem(void){
    int attempts = 3;
    char username[50];
    char password[50];

    printf("\n*********************************************************************************\n");
    printf("\n                             SYSTEM AUTHENTICATION                               \n");
    printf("\n*********************************************************************************\n");

    while(attempts > 0){
        printf("\nEnter Authentication username: ");
        scanf("%49s",username);
        printf("\nEnter Authentication Password: ");
        scanf("%49s",password);
        printf("\n");

        if(strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0){
            printf("Login successful!\n");
            return 0;
        }else{
            attempts--;
            printf("Invalid credentials, no. of attempts remaining is %d\n",attempts);
        }
    }

    printf("\nToo many unsuccessful attempts\n\n");
    return 1;
}
