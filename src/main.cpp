#include <iostream> 
#include <string.h>
#include "Patient.cpp"
#include "Doctor.cpp"
using namespace std;

int main() {
    string fullName = "ФИО";
    string specialization= "Специал";
    string qualification = "Высшая";
    
    string fullName = "Simple Name";
    string yearBirth = "2000";
    string snils = "00000000000";
    string phoneNumber = "8900000000";

    Doctor D1(fullName, specialization, qualification);
    D1.setFullName(fullName);
    cout << D1.getFullName() << endl;
    
    Patient Unit1(fullName, yearBirth, snils, phoneNumber);
    Unit1.setFullName(fullName);
    cout << Unit1.getFullName() << endl;
    
    return 0;
}
