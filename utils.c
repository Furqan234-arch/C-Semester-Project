#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "clinic.h"

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

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

        if(strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0){
            printf("Login successful, Access Granted\n");
            return 0;
        }else{
            attempts--;
            printf("Invalid credentials, Access denied, no of attempts remaining is %d\n",attempts);
        }
    }

    printf("\n[Security Alert] Too many unsuccessful attempts, program is terminated\n\n");
    return 0;
}
