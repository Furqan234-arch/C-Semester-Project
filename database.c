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

    printf("\nEnter Phone Number: ");
    scanf(" %19s", a.phone_number);

    printf("\nEnter Gmail: ");
    scanf(" %49s", a.gmail);

    printf("\nEnter Doctor Assigned: ");
    scanf(" %49[^\n]", a.doctor_name);
  
    printf("\nEnter Appointment Date(DD-MM-YYYY): ");
    scanf(" %15s", a.appointment_date);


    printf("\nEnter Patient status(Pending/Confirmed): ");
    scanf(" %14s", a.status);
    


    fprintf(file, "%d,%s,%d,%s,%s,%s,%s,%s\n", a.appointment_id, a.patient_name, a.patient_age, a.phone_number, a.gmail, a.doctor_name, a.appointment_date, a.status);

    fclose(file);
  
}

void searchAppointmentByID(void) {
    FILE *file = fopen(FILENAME, "r");
    if(file == NULL) {printf("File not Found!"); exit(1);}
    char line[250];
    int id;
    printf("Enter Appointment ID to search: ");
    scanf("%d", &id);

    Appointment a;
    int found = 0;
    while (fscanf(file, " %d,%49[^,],%d,%19[^,],%49[^,],%49[^,],%15[^,],%14[^\n]",
              &a.appointment_id, a.patient_name, &a.patient_age,
              a.phone_number, a.gmail, a.doctor_name, a.appointment_date, a.status) == 8) {
    if (a.appointment_id == id) {
       printf("Appointment ID: %d\nPatient Name: %s\nPatient Age: %d\nPhone Number: %s\nGmail: %s\nDoctor Assigned: %s\nAppointment Date: %s\nStatus: %s\n",
         a.appointment_id, a.patient_name, a.patient_age, a.phone_number, a.gmail, a.doctor_name, a.appointment_date, a.status);
     
       found = 1;
    }
}

    if(!found) {
        printf("Appointment with ID %d not found.\n", id);
    }

    fclose(file);
}
