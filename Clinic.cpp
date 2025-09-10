#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Date {
    int day, month, year;
};

class Appointment {
    private:
        Date date;
        string time;
        string reason;
        string status;  //scheduled, completed, or canceled
        string patientID;
        string doctorID;
    public:
        Appointment() {}
        Appointment(Date date, string time, string reason, string status, string patientID, string doctorID) {
            this->date = date;
            this->time = time;
            this->reason = reason;
            this->status = status;
            this->patientID = patientID;
            this->doctorID = doctorID;
        }

        //getter and setter
        Date getDate() {return date;}
        string getTime() {return time;}
        string getReason() {return reason;}
        string getStatus() {return status;}
        string getPatientID() {return patientID;}
        string getDoctorID() {return doctorID;}

        void setDate(Date date) {this->date = date;}
        void setTime(string time) {this->time = time;}
        void setReason(string reason) {this->reason = reason;}
        void setStatus(string status) {this->status = status;}
        void setPatientID(string patientID) {this->patientID = patientID;}
        void setDoctorID(string doctorID) {this->doctorID = doctorID;}

        //Show Information
        void displayInfo() {
            cout << "Appointment on " << date.day << "/" << date.month << "/" << date.year 
                 << " at " << time << " for " << reason << " between patient " << patientID << " and doctor " << doctorID << ". Status: " << status << endl;
        }

        //Update status for appointment
        void updateStatus(string newStatus) {
            status = newStatus;
        }
};

class Patient {
    private:
        string name;
        string ID;
        int age;
        vector <string> medicalHistory;
        vector <Appointment> appointments;
    public:
        Patient() {}
        Patient(string name, string ID, int age, vector<string> medicalHistory) {
            this->name = name;
            this->ID = ID;
            this->age = age;
            this->medicalHistory = medicalHistory;
        }

        string getName() {return name;}
        string getID() {return ID;}
        int getAge() {return age;}
        vector<string> getMedicalHistory() {return medicalHistory;}

        void setName(string name) {this->name = name;}
        void setID(string ID) {this->ID = ID;}
        void setAge(int age) {this->age = age;}
        void setMedicalHistory(vector<string> history) {medicalHistory = history;}

        void scheduleAppointment(Date date, string time, string reason, string doctorID) {
            cout << "Appointment scheduled for " << name << " with ID " << ID  << " on " << date.day << "/" << date.month << "/" << date.year << " at " << time << endl;
            appointments.push_back(Appointment(date, time, reason, "scheduled", ID, doctorID));
        }

        void updateMedicalHistory(string record) {
            medicalHistory.push_back(record);
        }

        void displayInfo() {
            cout << "Patient Name: " << name << ", ID: " << ID << ", Age: " << age << endl;
            cout << "Medical History: ";
            for (const string& record : medicalHistory) {
                cout << record << "; ";
            }
            cout << endl;
            cout << "Appointments: " << endl;
            for ( Appointment& app : appointments) {
                app.displayInfo();
            }
        }
};

class Doctor {
    private: 
        string name;
        string ID;
        string specialty;
        vector <Appointment> appointments;
    public:
        Doctor() {}
        Doctor(string name, string ID, string specialty, vector<Appointment> appointments) {
            this->name = name;
            this->ID = ID;
            this->specialty = specialty;
            this->appointments = appointments;
        }
        
        string getName() {return name;}
        string getID() {return ID;}
        string getSpecialty() {return specialty;}
        vector<Appointment> getAppointments() {return appointments;}

        void setName(string name) {this->name = name;}
        void setID(string ID) {this->ID = ID;}
        void setSpecialty(string specialty) {this->specialty = specialty;}
        void setAppointments(vector<Appointment> apps) {appointments = apps;}

        void assignAppointment(Date date, string time, string reason, string patientID) {
            appointments.push_back(Appointment(date, time, reason, "scheduled", patientID, ID));
        }

        void viewAppointmentStatus() {
            for (Appointment& app : appointments) {
                Date d = app.getDate();
                cout << "Appointment on " << app.getTime() << " at " << d.day << "/" << d.month << "/" << d.year << " is " << app.getStatus() << endl;
            }
        }
    
        void displayInfo() {
            cout << "Doctor Name: " << name << ", ID: " << ID << ", specialty" << specialty << endl;
            cout << "Appointments:" << endl;
            for ( Appointment& app : appointments) {
                app.displayInfo();
            }
        }
};

class ChronicPatient : public Patient {
    private:
        string conditionType;
        Date lastCheckupDate;
    public:
        ChronicPatient() {}
        ChronicPatient(string name, string ID, int age, vector<string> medicalHistory,string conditionType, Date lastCheckupDate) : Patient(name, ID, age, medicalHistory) {
            this->conditionType = conditionType;
            this->lastCheckupDate = lastCheckupDate;
        }

        string getConditionType() {return conditionType;}
        Date getLastCheckupDate() {return lastCheckupDate;}
        
        void setConditionType(string conditionType) {this->conditionType = conditionType;}
        void setLastCheckupDate(Date lastcheckupDate) {this->lastCheckupDate = lastCheckupDate;}

        void scheduleAppointment(Date date, string time, string reason, string doctorID) {
            Patient::scheduleAppointment(date, time, reason, doctorID);

            Date nextDate = date;
            nextDate.month += 3;
            if (nextDate.month > 12) {
                nextDate.month -= 12;
                nextDate.year++;
            }
            cout << "Next follow-up should be around " << nextDate.day << "/" << nextDate.month << "/" << nextDate.year << endl;

            // Cập nhật lần checkup gần nhất
            lastCheckupDate = date;
        }

        void displayInfo() {
            cout << "The condition: " << conditionType << endl;
            Patient::displayInfo();
        }
};

class Staff {
private:
    string name;
    string ID;
    string role;   // ví dụ: Receptionist, Nurse, Technician
public:
    Staff() {}
    Staff(string name, string ID, string role) {
        this->name = name;
        this->ID = ID;
        this->role = role;
    }

    string getName() { return name; }
    string getID() { return ID; }
    string getRole() { return role; }

    void setName(string name) { this->name = name; }
    void setID(string ID) { this->ID = ID; }
    void setRole(string role) { this->role = role; }

    void displayInfo() {
        cout << "Staff Name: " << name << ", ID: " << ID << ", Role: " << role << endl;
    }
};

class Clinic {
    private:
        vector<Patient> patients;
        vector<Doctor> doctors;
        vector<Appointment> appointments;
        vector<Staff> staffMembers;
    public:
        //Quản lý bệnh nhân
        void addPatient(Patient& p) {
            patients.push_back(p);
        }

        void displayAllPatients() {
            for (auto& p : patients) {
                p.displayInfo();
                cout << endl;
            }
            cout << endl;
        }

        Patient* findPatientByID(string& id) {
            for (auto& p : patients) {
                if (p.getID() == id) {return &p;}
            }
            return nullptr;
        }

        //Quản lý bác sĩ
        void addDoctor(Doctor& d) {
        doctors.push_back(d);
        }

        void displayAllDoctors() {
            for (auto& d : doctors) {
                d.displayInfo();
            }
            cout << endl;
        }

        Doctor* findDoctorByID(string& id) {
            for (auto& d : doctors) {
                if (d.getID() == id) return &d;
            }
            return nullptr;
        }

        // Quản lý nhân viên
        void addStaff( Staff& s) {
            staffMembers.push_back(s);
        }

        void displayAllStaff() {
            for (auto& s : staffMembers) {
                s.displayInfo();
            }
            cout << endl;
        }

        // Quản lý lịch hẹn
        void scheduleAppointment(string patientID, string doctorID, Date date, string time, string reason) {
            Patient* p = findPatientByID(patientID);
            Doctor* d = findDoctorByID(doctorID);
            if (p && d) { //khi cả hai con trỏ khác nullptr
            Appointment app(date, time, reason, "scheduled", patientID, doctorID);
                appointments.push_back(app);
                p->scheduleAppointment(date, time, reason, doctorID);
                d->assignAppointment(date, time, reason, patientID);
            } else {
                cout << "Error: Invalid patient or doctor ID.\n";
            }
        }

        void cancelAppointment(string patientID, string doctorID, Date date) {
            for (auto& app : appointments) {
                if (app.getPatientID() == patientID && app.getDoctorID() == doctorID &&
                    app.getDate().day == date.day &&
                    app.getDate().month == date.month &&
                    app.getDate().year == date.year) {
                    app.updateStatus("canceled");
                    cout << "Appointment canceled successfully.\n";
                    return;
                }
            }
            cout << "Error: Appointment not found.\n";
        }

        void displayAllAppointments() {
            for (auto& app : appointments) {
                app.displayInfo();
            }
        }
};

int main() {
    //Date provided by ChatGPT 
    cout << "========== TEST CASE 1 ==========\n";
    {
        Clinic clinic;

        // Bệnh nhân thường
        Patient p1("Nguyen Van A", "P001", 30, {"Cough in 2022"});
        clinic.addPatient(p1);

        // Bệnh nhân mãn tính
        Date lastCheckup1 = {1, 6, 2025};
        ChronicPatient cp1("Tran Thi B", "CP001", 45, {"Diabetes since 2020"}, "Diabetes", lastCheckup1);
        clinic.addPatient(cp1);

        // Bác sĩ
        Doctor d1("Le Van C", "D001", "Noi tiet", {});
        clinic.addDoctor(d1);

        // Nhân viên
        Staff s1("Pham Van D", "S001", "Receptionist");
        clinic.addStaff(s1);

        // Appointment cho bệnh nhân thường
        Date date1 = {10, 9, 2025};
        clinic.scheduleAppointment("P001", "D001", date1, "09:00", "General Checkup");

        // Appointment cho bệnh nhân mãn tính
        Date date2 = {15, 9, 2025};
        clinic.scheduleAppointment("CP001", "D001", date2, "14:00", "Follow-up for Diabetes");

        // Hiển thị thông tin
        clinic.displayAllPatients();
        clinic.displayAllDoctors();
        clinic.displayAllStaff();
        clinic.displayAllAppointments();
    }

    cout << "\n========== TEST CASE 2 ==========\n";
    {
        Clinic clinic;

        // Bệnh nhân thường
        Patient p2("Phan Van K", "P101", 28, {"Eye check 2023"});
        clinic.addPatient(p2);

        // Bệnh nhân mãn tính
        Date lastCheckup2 = {20, 5, 2025};
        ChronicPatient cp2("Hoang Thi M", "CP101", 60, {"Hypertension since 2018"}, "Hypertension", lastCheckup2);
        clinic.addPatient(cp2);

        // Bác sĩ
        Doctor d2("Nguyen Van E", "D002", "Tim mach", {});
        clinic.addDoctor(d2);

        // Nhân viên
        Staff s2("Le Thi F", "S002", "Nurse");
        clinic.addStaff(s2);

        // Appointment cho bệnh nhân thường
        Date date3 = {18, 9, 2025};
        clinic.scheduleAppointment("P101", "D002", date3, "10:00", "Vision problem");

        // Appointment cho bệnh nhân mãn tính
        Date date4 = {22, 9, 2025};
        clinic.scheduleAppointment("CP101", "D002", date4, "15:30", "Blood pressure follow-up");

        // Hiển thị thông tin
        clinic.displayAllPatients();
        clinic.displayAllDoctors();
        clinic.displayAllStaff();
        clinic.displayAllAppointments();
    }

    return 0;
}

