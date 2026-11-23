#include<stdio.h>
#include<stdlib.h>
#include "clinic.h"

void addAppointment(void) {
    Appointment a, temp;
    int duplicateId;
    while (true) {
        duplicateId = 0;
        printf("Enter Appointment ID: ");
        scanf(" %d", &a.appointment_id);

        FILE *file = fopen(FILENAME, "r");
        if (file != NULL) {
            while (fscanf(file, "%d,%49[^,],%d,%49[^,],%11[^,],%14[^\n]",
                          &temp.appointment_id, temp.patient_name, &temp.patient_age,
                          temp.doctor_name, temp.appointment_date, temp.status) == 6) {
                if (temp.appointment_id == a.appointment_id) {
                    duplicateId = 1;
                    break;
                }
            }
            fclose(file);
        }else {
            printf("File not Found!");
            exit(1);
        }

        if (!duplicateId) {
            break;
        }
        printf("ID already exists. Enter another ID.\n\n");
    }
    printf("\nEnter Patient Name: ");
    scanf(" %49[^\n]", a.patient_name);
  
    printf("\nEnter Patient Age: ");
    scanf(" %d", &a.patient_age);

    printf("\nEnter Doctor Assigned: ");
    scanf(" %49[^\n]", a.doctor_name);
  
    printf("\nEnter Appointment Date(DD-MM-YYYY): ");
    scanf(" %11s", a.appointment_date);

    printf("\nEnter Patient status(Pending/Confirmed): ");
    scanf(" %14s", a.status);

    FILE *file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf("File not Found!");
        exit(1);
    }

    fprintf(file, "%d,%s,%d,%s,%s,%s\n", a.appointment_id, a.patient_name, a.patient_age, a.doctor_name, a.appointment_date, a.status);

    printf("\nAppointment ID: %d\nPatient Name: %s\nPatient Age: %d\nDoctor Assigned: %s\nAppointment Date: %s\nStatus: %s\n",
    a.appointment_id, a.patient_name, a.patient_age, a.doctor_name, a.appointment_date, a.status);
    
    fclose(file);
}

void searchAppointmentByID(void) {
    FILE *file = fopen(FILENAME, "r");
    if(file == NULL) {printf("File not Found!"); exit(1);}
    int searchedId;
    printf("Enter Appointment ID to search: ");
    scanf("%d", &searchedId);

    Appointment a;
    int found = 0;
    while (fscanf(file, "%d,%49[^,],%d,%49[^,],%11[^,],%14[^\n]",
              &a.appointment_id, a.patient_name, &a.patient_age,
              a.doctor_name, a.appointment_date, a.status) == 6) {
    if (a.appointment_id == searchedId) {
       printf("\nAppointment ID: %d\nPatient Name: %s\nPatient Age: %d\nDoctor Assigned: %s\nAppointment Date: %s\nStatus: %s\n",
         a.appointment_id, a.patient_name, a.patient_age, a.doctor_name, a.appointment_date, a.status);
     
       found = 1;
    }
}

    if(!found) {
        printf("Appointment with ID %d not found.\n", searchedId);
    }

    fclose(file);
}