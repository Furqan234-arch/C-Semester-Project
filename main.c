#include <stdio.h>
#include "clinic.h"
int main(void) {
    int choice = 0;

    if(loginSystem()) {//login function call for admin (no input or output)
        printf("Login failed!\n");
        return 1;
    }

    //admin have to select from five choices
    //I used dowhile loop so admin can make atlest one choice even if it invalid (display default msg)
    //5 to exit the loop
    do {
        printf("\n=================================\n");
        printf("     CLINIC APPOINTMENT SYSTEM");
        printf("\n=================================\n");
        printf("1. Add Appointment\n");
        printf("2. Search Appointment by ID\n");
        printf("3. Update Appointment Record\n");
        printf("4. Delete Appointment Record\n");
        printf("5. Exit\n\n");

        printf("Enter your choice: ");
        scanf("%d",   &choice);

        clearInputBuffer();
        printf("\n");

        switch (choice) {
            case 1:
                addAppointment();
                break;
            case 2:
                searchAppointmentByID();
                break;
            case 3:
                updateAppointmentRecord();
                break;
            case 4:
                deleteAppointmentRecord();
                break;
            case 5:
                printf("\nExiting system.\n");
                break;
            default:
                printf("\nInvalid choice (please enter 1-5)\n");
        }
    } while (choice != 5);
    return 0;
}