#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "clinic.h"

void updateAppointmentRecord(void)
{
    FILE *fp, *temp;
    Appointment a;
     int searchID;
     int found = 0;

fp = fopen(FILENAME, "r");

if (fp == NULL){
        printf("Unable to open appointments file.\n");
        return;}
    temp = fopen("Data//temp.txt", "w");
if(temp == NULL){
    printf("Unable to create temporary file.\n");
        fclose(fp);
        return;}
    printf("Enter Appointment ID to update: ");
     scanf("%d", &searchID);
    clearInputBuffer();
    // Read each appointment from the original file
       while (fscanf(fp, " %d,%49[^,],%d,%49[^,],%11[^,],%14[^\n]",
                  &a.appointment_id,
                    a.patient_name,
                  &a.patient_age,
                  a.doctor_name,
                a.appointment_date,
                  a.status) == 6){
        if (a.appointment_id == searchID){
            found = 1;
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
            scanf(" %11s", a.appointment_date);
            clearInputBuffer();

            printf("Enter new status (Pending/Confirmed/Completed): ");
            scanf(" %14s", a.status);
            clearInputBuffer();}
        // Write appointment (updated or unchanged)
        fprintf(temp, "%d,%s,%d,%s,%s,%s\n",
                a.appointment_id,
                a.patient_name,
                a.patient_age,
                a.doctor_name,
                a.appointment_date,
                a.status);
    }

    fclose(fp);
    fclose(temp);

    if (found){
    remove(FILENAME);
if (rename("Data//temp.txt", FILENAME) == 0) printf("\nAppointment updated successfully!\n");
        else printf("\nError replacing original file.\n");
    }
    else{
remove("Data//temp.txt");
printf("\nAppointment ID not found!\n");
}}
