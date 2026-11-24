#ifndef CLINIC_H
#define CLINIC_H
// File path and admin credentials
#define FILENAME "Data//appointments.txt" 
#define USERNAME "admin"
#define PASSWORD "admin123"

// Structure to store details of a single patient appointment
typedef struct {
    int appointment_id;
    char patient_name[50];
    int patient_age;
    char doctor_name[50];
    char appointment_date[12]; // Format: DD-MM-YYYY
    char status[15];           // Pending, Confirmed, Completed
} Appointment;
// Function declarations for authentication, CRUD operations, and input handling
int loginSystem(void);
void addAppointment(void);
void searchAppointmentByID(void);
void displayAllAppointments(void);
void updateAppointment(void);
void deleteAppointment(void);
void clearInputBuffer(void);

#endif
