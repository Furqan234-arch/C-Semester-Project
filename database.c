#include<stdio.h>
#include<stdlib.h>
#include "clinic.h"


void addAppointment(void) {
    FILE *file = fopen(FILENAME, "a");
    if(file == NULL) {printf("File not Found!"); exit(1);}

    Appointment a;
    
    printf("Enter Appointment ID: ");
    scanf(" %d",&a.appointment_id);

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

    fprintf(file, "%d,%s,%d,%s,%s,%s\n", a.appointment_id, a.patient_name, a.patient_age, a.doctor_name, a.appointment_date, a.status);
    
    printf("\nAppointment added successfully!\n");
    printf("\nAppointment ID: %d\nPatient Name: %s\nPatient Age: %d\nDoctor Assigned: %s\nAppointment Date: %s\nStatus: %s\n",
    a.appointment_id, a.patient_name, a.patient_age, a.doctor_name, a.appointment_date, a.status);
    
    clearInputBuffer(); // Clear the input buffer after reading inputs
    fprintf(file, "%d,%s,%d,%s,%s,%s\n", a.appointment_id, a.patient_name, a.patient_age, a.doctor_name, a.appointment_date, a.status);
    printf("\nAppointment added successfully!\n");
    fclose(file);
  
}

void searchAppointmentByID(void) {
    FILE *file = fopen(FILENAME, "r");
    if(file == NULL) {printf("File not Found!"); exit(1);}
    char line[250];
    int id;
    printf("Enter Appointment ID to search: ");
    scanf("%d", &id);
    clearInputBuffer(); // Clear the input buffer after reading inputs
    printf("\n");
    Appointment a;
    int found = 0;
    while (fscanf(file, "%d,%49[^,],%d,%49[^,],%11[^,],%14[^\n]",
              &a.appointment_id, a.patient_name, &a.patient_age,
              a.doctor_name, a.appointment_date, a.status) == 6) {
    if (a.appointment_id == id) {
       printf("Appointment ID: %d\nPatient Name: %s\nPatient Age: %d\nDoctor Assigned: %s\nAppointment Date: %s\nStatus: %s\n\n",
         a.appointment_id, a.patient_name, a.patient_age, a.doctor_name, a.appointment_date, a.status);
     
       found = 1;
    }
}

    if(!found) {
        printf("Appointment with ID %d not found.\n", id);
    }

    fclose(file);
}

void displayAllAppointments() {
    FILE *file = fopen("Data//appointments.txt", "r");

    // Exit early if the file can't be opened
    if (file == NULL) {
        printf("\nNo records found.\n");
        exit(1);
    }

    Appointment a;
    int found = 0;
    printf("\n=================================\n");
    printf("\nAll Appointments\n");
    printf("\n=================================\n");
    
    while (fscanf(file, "%d|%49[^,]|%d|%49[^,]|%11[^,]|%14[^\n]\n",&a.appointment_id, a.patient_name, &a.patient_age,
                a.doctor_name, a.appointment_date, a.status) == 6) {
        
        printf("ID: %d | Patient: %s (%d) | Doctor: %s | Date: %s | Status: %s\n",
               a.appointment_id, a.patient_name, a.patient_age,
               a.doctor_name, a.appointment_date, a.status);
        found = 1;
    }

    if (!found) {
        printf("No appointments in the file.\n");
    }

    fclose(file);
}
