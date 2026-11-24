#include <stdio.h>
#include "clinic.h"

void addAppointment(void){
    Appointment a, temp;
    int isDuplicate;
    //Scan existing file to ensure the new appointment ID is unique
    while (1) {// keep asking until we get an ID that isn't already in the file
        isDuplicate = 0;

        printf("Enter Appointment ID: ");
        scanf(" %d", &a.appointment_id);

        FILE *file = fopen(FILENAME, "r");
        if (file != NULL) {
            while (fscanf(file, "%d,%49[^,],%d,%49[^,],%11[^,],%14[^\n]",
                    &temp.appointment_id,temp.patient_name,&temp.patient_age,temp.doctor_name,temp.appointment_date,temp.status) == 6) {

                if (temp.appointment_id == a.appointment_id) {
                    isDuplicate = 1;
                    break;
                }
            }
            fclose(file);
        }
        if (!isDuplicate) {
            break;
        }
        printf("ID already exists. Enter another ID.\n\n");
    }

    // %[^\n] so names with spaces work, %s is fine for date and status
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

    // Open in append mode so new records are added at end without overwriting existing data.
    FILE *file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf("File not Found!");
        return;
    }
    fprintf(file, "%d,%s,%d,%s,%s,%s\n",
        a.appointment_id,a.patient_name,a.patient_age,a.doctor_name,a.appointment_date,a.status);

    printf("\nAppointment ID: %d\nPatient Name: %s\nPatient Age: %d\nDoctor Assigned: %s\nAppointment Date: %s\nStatus: %s\n\n",
        a.appointment_id, a.patient_name, a.patient_age,a.doctor_name, a.appointment_date, a.status);
    
        printf("\nAppointment added successfully!\n");    
    fclose(file);
}

void searchAppointmentByID(void){
    FILE *file = fopen(FILENAME, "r");
    Appointment a;
    int id;
    int found = 0;

    if (file == NULL) {
        printf("File not Found!");
        return;
    }
    printf("Enter Appointment ID to search: ");
    scanf("%d", &id);
    clearInputBuffer();
    printf("\n");
    // Read records line by line until all 6 fields fail to parse.
    while (fscanf(file, " %d,%49[^,],%d,%49[^,],%11[^,],%14[^\n]",
            &a.appointment_id,a.patient_name,&a.patient_age,a.doctor_name,a.appointment_date,a.status) == 6) {

        if (a.appointment_id == id) {
            printf("Appointment ID: %d\nPatient Name: %s\nPatient Age: %d\nDoctor Assigned: %s\nAppointment Date: %s\nStatus: %s\n\n",
                a.appointment_id, a.patient_name, a.patient_age,a.doctor_name, a.appointment_date, a.status);

            found = 1;
        }
    }
    if (!found) {
        printf("Appointment with ID %d not found.\n", id);
    }
    fclose(file);
}

void displayAllAppointments(void){
    FILE *file = fopen(FILENAME, "r");
    Appointment a;
    int found = 0;

    if (file == NULL) {
        printf("\nNo records found.\n");
        return;
    }
    printf("\nAll Appointments:\n");
// Read records line by line until all 6 fields fail to parse.
    while (fscanf(file, " %d,%49[^,],%d,%49[^,],%11[^,],%14[^\n]",
            &a.appointment_id,a.patient_name,&a.patient_age,a.doctor_name,a.appointment_date,a.status) == 6) {

        printf("ID: %d | Patient: %s | Age: %d | Doctor: %s | Date: %s | Status: %s\n",
            a.appointment_id, a.patient_name, a.patient_age,a.doctor_name, a.appointment_date, a.status);
        found = 1;
    }
    if (!found) {
        printf("No appointments in the file.\n");
    }
    fclose(file);
}