#include<stdio.h>
#include<stdlib.h>
#include "clinic.h"

void updatePatientRecord(void){
    FILE *fp, *temp;
    Appointment a;
    int searchID;
    int found = 0;
    char choice;

    fp = fopen(FILENAME, "r");

    if (fp == NULL){
        printf("Unable to open appointments file.\n");
        return;
    }

    temp = fopen("Data//temp.txt", "w");

    if(temp == NULL){
        printf("Unable to create temporary file.\n");
        fclose(fp);
        return;}

    printf("Enter Appointment ID to update: ");
    scanf("%d", &searchID);
    clearInputBuffer();

    // Read each appointment from the original file
       while (fscanf(fp, " %d,%49[^,],%d,%19[^,],%49[^,],%49[^,],%11[^,],%14[^\n]",
                &a.appointment_id,
                a.patient_name,
                &a.patient_age,
                a.phone_number,
                a.gmail,
                a.doctor_name,
                a.appointment_date,
                a.status) == 8){
                    if (a.appointment_id == searchID){
                        found = 1;
                        printf("\nAppointment found!\n");

                        // Take updated information from admin
                        printf("Enter new patient name: ");
                        scanf(" %49[^\n]", a.patient_name);
                        clearInputBuffer();

                        printf("Enter new age: ");
                        scanf("%d", &a.patient_age);
                        clearInputBuffer();

                        printf("Enter new phone number: ");
                        scanf("%19s", a.phone_number);
                        clearInputBuffer();

                        printf("Enter new gmail: ");
                        scanf("%49s", a.gmail);
                        clearInputBuffer();

                        printf("Enter new doctor name: ");
                        scanf(" %49[^\n]", a.doctor_name);
                        clearInputBuffer();

                        printf("Enter new date (DD-MM-YYYY): ");
                        scanf("%15s", a.appointment_date);
                        clearInputBuffer();

                        printf("Enter new status (Pending/Confirmed): ");
                        scanf("%14s", a.status);
                        clearInputBuffer();

                        // Ask admin to confirm before saving the updated record
                        printf("\nConfirm updated record? (y/n): ");
                        scanf(" %c", &choice);
                        clearInputBuffer();

                        // Cancel update if admin does not enter y
                        if (choice != 'y' && choice != 'Y'){
                            fclose(fp);
                            fclose(temp);
                            remove("Data//temp.txt");
                            printf("\nUpdate cancelled!\n");
                            return;
                        }
                    }

                        // Write appointment to the file
                        fprintf(temp, "%d,%s,%d,%s,%s,%s,%s,%s\n",
                                a.appointment_id,
                                a.patient_name,
                                a.patient_age,
                                a.phone_number,
                                a.gmail,
                                a.doctor_name,
                                a.appointment_date,
                                a.status);
    }

    fclose(fp);
    fclose(temp);

    // Replace original file with temporary file if record was found
    if (found){
        remove(FILENAME);
        if (rename("Data//temp.txt", FILENAME) == 0){
             printf("\nAppointment updated successfully!\n");
            }
        else
            printf("\nError replacing original file.\n");
    }
    else{
        remove("Data//temp.txt");
        printf("\nAppointment ID not found!\n");
    }
}

void deletePatientRecord(void)
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

    while (fscanf(file, " %d,%49[^,],%d,%19[^,],%49[^,],%49[^,],%15[^,],%14[^\n]",
                  &a.appointment_id, a.patient_name, &a.patient_age,
                  a.phone_number, a.gmail, a.doctor_name, a.appointment_date, a.status) == 8) {
        if (a.appointment_id == deleteID) {
            found = 1;

            printf("\nAppointment Found!\n");
            printf("Patient Name: %s\n", a.patient_name);
            printf("Age: %d\n", a.patient_age);
            printf("Phone Number: %s\n", a.phone_number);
            printf("Gmail: %s\n", a.gmail);
            printf("Doctor Name: %s\n", a.doctor_name);
            printf("Appointment Date: %s\n", a.appointment_date);
            printf("Status: %s\n", a.status);

            continue;
        }

        // Write all records except the one being deleted
        fprintf(temp, "%d,%s,%d,%s,%s,%s,%s,%s\n",
                a.appointment_id, a.patient_name, a.patient_age,
                a.phone_number, a.gmail, a.doctor_name, a.appointment_date, a.status);
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