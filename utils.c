#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define PASSWORD "admin123"

void clearInputBuffer(){
    int c;
    while(c!='\n' && c!=EOF){
        c = getchar();
    }
}

void loginSystem(){
    int attempts = 3;
    char input[50];

    printf("\n*********************************************************************************\n");
    printf("\n                             SYSTEM AUTHENTICATION                               \n");
    printf("\n*********************************************************************************\n");

    while(attempts > 0){
        printf("\nEnter Authentication Password: ");
        scanf("%49s",input);

        clearInputBuffer();

        if(strcmp(input,PASSWORD) == 0){
            printf("Password is correct, Access Granted\n");
            return ;
        }else{
            attempts--;
            printf("Invalid password, Access denied, no of attempts remaining is %d\n",attempts);
        }
    }

    printf("\n[Security Alert] Too many unsuccessful attempts, program is terminated\n\n");
    exit(1);
}

