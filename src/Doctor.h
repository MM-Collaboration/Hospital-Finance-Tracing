#pragma once
#include <iostream>
#include <string>

class Doctor {
    public:
        Doctor(std::string* _fullName, std::string* _speciatization, std::string* _qualification); 

        Doctor(std::string _fullName, std::string _speciatization, std::string _qualification); 

        std::string getFullName();

        std::string getSpecialization();

        std::string getQualification();

        void setFullName(std::string* _fullName);
        
        void setFullName(std::string _fullName);

        void setSpecialization(std::string* _specialization);
        
        void setSpecialization(std::string _specialization);

        void setQualification(std::string* _qualification);

        void setQualification(std::string _qualification);

    private:
        std::string* m_fullName;
        std::string* m_specialization;
        std::string* m_qualification;
};
