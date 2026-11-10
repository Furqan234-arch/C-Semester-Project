#include<stdio.h>
#include "clinic.h"


void addAppointment() {
    FILE *file = fopen(fileName, "a");
    if(file == NULL) printf("File not Found!");

    Appointment a;
    printf("Enter Appointment ID: ");
    scanf("%d",&a.appointment_id);
    printf("\nEnter Patient Name: ");
    scanf("%s", a.patient_name);
    printf("\nEnter Patient Age: ");
    scanf("%d", &a.patient_age);
    printf("\nEnter Doctor Assigned: ");
    scanf("%s", a.doctor_name);
    printf("\nEnter Appointment Date(DD-MM-YYYY): ");
    scanf("%s", a.appointment_date);
    printf("\nEnter Patient status(Pending/Confirmed): ");
    scanf("%s", a.status);

    fprintf(file, "%d,%s,%d,%s,%s,%s\n", a.appointment_id, a.patient_name, a.patient_age, a.doctor_name, a.appointment_date, a.status);

    fclose(file);
  
}

