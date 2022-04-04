#pragma once
#include <iostream>
#include <string>

class Patient {
    public:
        Patient(std::string* _fullName, std::string* _yearBirth, std::string* _snils, std::string*_phoneNumber); 

        Patient(std::string _fullName, std::string _yearBirth, std::string _snils, std::string _phoneNumber); 

        std::string getFullName();

        std::string getYearBirth();

        std::string getSNILS();

        std::string getPhoneNumber();

        void setFullName(std::string* _fullName);

        void setFullName(std::string _fullName);

        void setYearBirth(std::string* _yearBirth);

        void setYearBirth(std::string _yearBirth);

        void setSnils(std::string* _snils);

        void setSnils(std::string _snils);

        void setPhoneNumber(std::string* _phoneNumber);

        void setPhoneNumber(std::string _phoneNumber);

    private:
        std::string* m_fullName;
        std::string* m_yearBirth;
        std::string* m_snils;
        std::string* m_phoneNumber;
};
