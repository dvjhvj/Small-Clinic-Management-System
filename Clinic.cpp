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
    public:
        Appointment() {}
        Appointment(Date date, string time, string reason, string status) {
            this->date = date;
            this->time = time;
            this->reason = reason;
            this->status = status;
        }

        Date getDate() {return date;}
        string getTime() {return time;}
        string getReason() {return reason;}
        string getStatus() {return status;}

        void setDate(Date date) {this->date = date;}
        void setTime(string time) {this->time = time;}
        void setReason(string reason) {this->reason = reason;}
        void setStatus(string status) {this->status = status;}

        void displayInfo() {
            cout << "Appointment on " << date.day << "/" << date.month << "/" << date.year 
                 << " at " << time << " for " << reason << ". Status: " << status << endl;
        }

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

        void scheduleAppointment(Date date, string time, string reason) {
            cout << "Appointment scheduled for " << name << " with ID " << ID  << " on " << date.day << "/" << date.month << "/" << date.year << " at" << time << endl;
            appointments.push_back(Appointment(date, time, reason, "scheduled"));
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

        void updateAppointment(Appointment app) {
            appointments.push_back(app);
        }

        void viewAppointmentStatus() {
            for (Appointment& app : appointments) {
                Date d = app.getDate();
                cout << "Appointment on" << app.getTime() << " at " << d.day << "/" << d.month << "/" << d.year << " is " << app.getStatus() << endl;
            }
        }
    
        void displayInfo() {
            cout << "Dotor Name: " << name << ", ID: " << ID << ", specialty" << specialty << endl;
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

        void scheduleAppointment(Date date, string time, string reason) {
            Patient::scheduleAppointment(date, time, reason);

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

int main() {
    // Ngày mẫu
    Date d1 = {10, 9, 2025};
    Date d2 = {15, 9, 2025};
    Date d3 = {20, 9, 2025};

    // Bệnh nhân thường
    vector<string> history1 = {"Cam cum 2024", "Kham tong quat 2025"};
    Patient p1("Nguyen Van A", "BN001", 25, history1);
    p1.scheduleAppointment(d1, "09:00", "Kham suc khoe");
    p1.updateMedicalHistory("Tiem phong 2025");

    // Bệnh nhân mãn tính
    vector<string> history2 = {"Dai thao duong loai 2"};
    ChronicPatient cp1("Tran Thi B", "BNDB001", 50, history2, "Diabetes", d2);
    cp1.scheduleAppointment(d2, "14:00", "Tai kham dinh ky");

    // Bác sĩ
    vector<Appointment> doctorApps;
    Doctor doc("Le Van C", "DR001", "Noi tiet", doctorApps);

    // Bác sĩ nhận thêm lịch hẹn
    doc.updateAppointment(Appointment(d3, "10:00", "Kham cho benh nhan A", "scheduled"));
    doc.updateAppointment(Appointment(d2, "14:00", "Kham cho benh nhan B", "scheduled"));

    // In thông tin
    cout << "==== Patient 1 Info ====" << endl;
    p1.displayInfo();

    cout << "\n==== Chronic Patient Info ====" << endl;
    cp1.displayInfo();

    cout << "\n==== Doctor Info ====" << endl;
    doc.displayInfo();

    cout << "\n==== Doctor Appointment Status ====" << endl;
    doc.viewAppointmentStatus();

    return 0;
}
