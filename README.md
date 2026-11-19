# C Semester Project 
Clinic Management System Project 

Basic Information

#define maxAppointments 100
#define fileName "appointments.txt"
#define Password "admin123"


typedef struct {
    int appointment_id;
    char patient_name[50];
    int patient_age;
    char doctor_name[50];
    char appointment_date[12]; // Format: DD-MM-YYYY
    char status[15];           // Pending, Confirmed, Completed
} Appointment;
xcghjas