#include <stdio.h>
#include "clinic.h"
int main(void) {
    int choice = 0;

    loginSystem();//login function call for admin (no input or output)
    clearInputBuffer();//clear left over newline from scanf in login system (defined in utils.c)

    //admin have to select from five choices
    //I used dowhile loop so admin can make atleast one choice even if it invalid.
    do {
printf("\n=================================\n");
        printf("     CLINIC APPOINTMENT SYSTEM\n");
        printf("=================================\n");
        printf("1. Add Appointment\n");
        printf("2. Search Appointment by ID\n");
        printf("3. Update Patient Record\n");
        printf("4. Delete Patient  Recrd\n");
        printf("5. Exit\n");
        printf("Enter your choice:");

        //Check whether the admin entered a valid integer
        if (scanf("%d",   &choice) !=1) {
            choice = 0;
}
        clearInputBuffer();//clear any leftover input from the input buffer

        //Execute the function according to the admin's choice
        switch (choice) {
            case 1:
                addAppointment();
                break;
            case 2:
                searchAppointmentByID();
                break;
            case 3:
                updatePatientRecord();
                break;
            case 4:
                deletePatientRecord();
                break;
            case 5:
                printf("\nExiting system.\n");
                break;
            default:
                printf("\nInvalid choice (please enter 1-5)\n");
        }
    } while (choice != 5);//repeat menu until admin chooses 5
    return 0;
}