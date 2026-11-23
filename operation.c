#include<stdio.h>
#include<stdlib.h>
#include "clinic.h"

void updateAppointmentRecord(void)
{
    FILE *file, *temp;
    Appointment a;
     int searchID;
     int found = 0;

    file = fopen(FILENAME, "r");
    if (file == NULL){
        printf("Unable to open appointments file.\n");
        exit(1);}

    temp = fopen("Data//temp.txt", "w");
    if(temp == NULL){
    printf("Unable to create temporary file.\n");
        fclose(file);
        exit(1);}

    printf("Enter Appointment ID to update: ");
     scanf("%d", &searchID);
    clearInputBuffer();
    // Read each appointment from the original file
       while (fscanf(file, " %d,%49[^,],%d,%49[^,],%11[^,],%14[^\n]",
        &a.appointment_id,a.patient_name, &a.patient_age, a.appointment_date, a.status) == 6){
        
            if (a.appointment_id == searchID){
            found = 1;
            printf("\nCurrent Appointment Details:\n");
            printf("\nAppointment ID: %d\nPatient Name: %s\nPatient Age: %d\nDoctor Assigned: %s\nAppointment Date: %s\nStatus: %s\n",
            a.appointment_id, a.patient_name, a.patient_age, a.doctor_name, a.appointment_date, a.status);    

            printf("\nAppointment found!\n");

            printf("Enter new patient name: ");
            scanf(" %49[^\n]", a.patient_name);
            clearInputBuffer();
            
            printf("Enter new age: ");
            scanf("%d", &a.patient_age);
            clearInputBuffer();
            
            printf("Enter new doctor name: ");
            scanf(" %49[^\n]", a.doctor_name);
            clearInputBuffer();
            
            printf("Enter new date (DD-MM-YYYY): ");
            scanf("%11s", a.appointment_date);
            clearInputBuffer();

            printf("Enter new status (Pending/Confirmed/Completed): ");
            scanf("%14s", a.status);
            clearInputBuffer();}
        
            fprintf(temp,"%d,%s,%d,%s,%s,%s\n",
            a.appointment_id,a.patient_name,a.patient_age,a.doctor_name,a.appointment_date,a.status);
            
            printf("\nAppointment updated successfully!\n");     
            printf("\nAppointment ID: %d\nPatient Name: %s\nPatient Age: %d\nDoctor Assigned: %s\nAppointment Date: %s\nStatus: %s\n",
            a.appointment_id, a.patient_name, a.patient_age, a.doctor_name, a.appointment_date, a.status);    
    }
    fclose(file);
    fclose(temp);

if (!found) {
    remove("Data//temp.txt");
    printf("\nAppointment ID not found!\n");
    exit(1);
}
remove(FILENAME);

if (rename("Data//temp.txt", FILENAME) != 0) {
    printf("\nError replacing original file.\n");
    exit(1); 
}
printf("\nAppointment updated successfully!\n");
}

void deleteAppointmentRecord(void)
{
    FILE *file = fopen(FILENAME, "r");
    FILE *temp;

    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    temp = fopen("Data//temp.txt", "w");
    if (temp == NULL) {
        printf("Error opening temporary file\n");
        fclose(file);
        return;
    }

    int found = 0;
    int deleteID;
    Appointment a;

    printf("Enter Appointment ID to delete: ");
    scanf(" %d", &deleteID);

    while (fscanf(file, " %d,%49[^,],%d,%49[^,],%11[^,],%14[^\n]",
                  &a.appointment_id, a.patient_name, &a.patient_age,
                  a.doctor_name, a.appointment_date, a.status) == 6) {
        if (a.appointment_id == deleteID) {
            found = 1;
            continue;
        }

        fprintf(temp, "%d,%s,%d,%s,%s,%s\n",
                a.appointment_id, a.patient_name, a.patient_age,
                a.doctor_name, a.appointment_date, a.status);
    }

    fclose(file);
    fclose(temp);

    if (found == 1) {
        remove(FILENAME);

        if (rename("Data//temp.txt", FILENAME) == 0) {
            printf("Appointment Record deleted successfully!\n");
        } else {
            printf("Error renaming file.\n");
        }
    } else {
        remove("Data//temp.txt");
        printf("ID not found\n");
    }
}
