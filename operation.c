#include <stdio.h>
#include "clinic.h"
//Searches an appointment by ID and updates its fields via a temp file.
void updateAppointment(void){
    FILE *file, *temp;
    Appointment a;
    int searchID;
    int found = 0;

    file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Unable to open appointments file.\n");
        return;
    }

    // it writes changes to a temporary file and then swap it in the end
    temp = fopen("Data//temp.txt", "w");
    if (temp == NULL) {
        printf("Unable to create temporary file.\n");
        fclose(file);// Close original file to prevent resource leak
        return;
    }

    printf("Enter Appointment ID to update: ");
    scanf("%d", &searchID);
    clearInputBuffer();

    /* CSV parsing is done to prevent %s to stop on space.
    The numbers in the format %49 etc prevent overflowing the arrays*/
    while (fscanf(file, " %d,%49[^,],%d,%49[^,],%11[^,],%14[^\n]",
            &a.appointment_id,a.patient_name,&a.patient_age,a.doctor_name,a.appointment_date,a.status) == 6) {
    // Match found: display old record and overwrite struct fields with new input
        if (a.appointment_id == searchID) {
            found = 1;

            printf("\nAppointment found!\n");
            printf("\nCurrent details:\n");
            printf("\nAppointment ID: %d\nPatient Name: %s\nPatient Age: %d\nDoctor Assigned: %s\nAppointment Date: %s\nStatus: %s\n",
                a.appointment_id, a.patient_name, a.patient_age,a.doctor_name, a.appointment_date, a.status);

            printf("\nEnter new patient name: ");
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
            clearInputBuffer();

            // Only show this for the record we actually changed
            printf("\nUpdated details:\n");
            printf("\nAppointment ID: %d\nPatient Name: %s\nPatient Age: %d\nDoctor Assigned: %s\nAppointment Date: %s\nStatus: %s\n ",
                a.appointment_id, a.patient_name, a.patient_age,a.doctor_name, a.appointment_date, a.status);
        }
        // Write every record (updated or unchanged) into the temp file
        fprintf(temp, "%d,%s,%d,%s,%s,%s\n",
            a.appointment_id,a.patient_name,a.patient_age,a.doctor_name,a.appointment_date,a.status);
    }
    // Close both files before deleting or renaming on Windows
    fclose(file);
    fclose(temp);
    //If ID was not found, discard temp file and keep original intact
    if (!found) {
        remove("Data//temp.txt");
        printf("\nAppointment ID not found!\n");
        return;
    }
    // Replace original file with the updated temporary file
    remove(FILENAME);
    if (rename("Data//temp.txt", FILENAME) != 0) {
        printf("\nError replacing original file.\n");
        return;
    }
    printf("\nAppointment updated successfully!\n");
}

void deleteAppointment(void)
{
    FILE *file = fopen(FILENAME, "r");
    FILE *temp;
    Appointment a;
    int found = 0;
    int deleted = 0;
    int deleteID;
    char choice;

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

    printf("Enter Appointment ID to delete: ");
    scanf(" %d", &deleteID);

    while (fscanf(file, " %d,%49[^,],%d,%49[^,],%11[^,],%14[^\n]",
            &a.appointment_id,a.patient_name,&a.patient_age,a.doctor_name,a.appointment_date,a.status) == 6) {

        if (a.appointment_id == deleteID) {
            found = 1;

            printf("\nAppointment to be deleted:\n");
            printf("\nAppointment ID: %d\nPatient Name: %s\nPatient Age: %d\nDoctor Assigned: %s\nAppointment Date: %s\nStatus: %s\n",
                a.appointment_id, a.patient_name, a.patient_age,a.doctor_name, a.appointment_date, a.status);

            // only ask about the record that matched, not every line in the file
            printf("\nAre you sure you want to delete this appointment? (y/n): ");
            scanf(" %c", &choice); //Confirm deletion with admin before modifying records
            clearInputBuffer();
            // 'y' = skip the write so the record disappears
            if (choice == 'y' || choice == 'Y') {
                deleted = 1;
                continue;
            }
        }
        // everything else (and a cancelled delete) gets copied over as normal
        fprintf(temp, "%d,%s,%d,%s,%s,%s\n",
            a.appointment_id,a.patient_name,a.patient_age,a.doctor_name,a.appointment_date,a.status);
    }
    fclose(file);
    fclose(temp);
    if (!found) {
        remove("Data//temp.txt");
        printf("ID not found\n");
        return;
    }
    // If user cancelled deletion, remove temp file and abort
    if (!deleted) {
        remove("Data//temp.txt");
        printf("Deletion cancelled.\n");
        return;
    }
    remove(FILENAME);
    if (rename("Data//temp.txt", FILENAME) != 0) {
        printf("Error renaming file.\n");
        return;
    }
    printf("Appointment deleted successfully!\n");
}