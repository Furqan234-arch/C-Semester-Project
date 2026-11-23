#ifndef CLINIC_H
#define CLINIC_H

#define maxAppointments 100
#define FILENAME "Data//appointments.txt"
#define USERNAME "admin"
#define PASSWORD "admin123"


typedef struct {
    int appointment_id;
    char patient_name[50];
    int patient_age;
    char doctor_name[50];
    char appointment_date[12]; // Format: DD-MM-YYYY
    char status[15];           // Pending, Confirmed, Completed
} Appointment;
<<<<<<< Updated upstream

void clearInputBuffer(void);
int loginSystem(void);
void addAppointment();
void searchAppointmentByID();
void updateAppointmentRecord();
void deleteAppointmentRecord();
=======
int loginSystem(void);
void addAppointment(void);
void searchAppointmentByID(void);
void displayAllAppointments(void);
void updateAppointment(void);
void deleteAppointment(void);
void clearInputBuffer(void);
>>>>>>> Stashed changes

#endif
