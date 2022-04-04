#pragma once
#include <iostream>

class PatientVisit {
    public:
        std::string* getDate();

        std::string* getDiagnosis();

        int getPrice();

        bool get_isFirstVisit();

        void setDate(std::string* _date);

        void setDiagnosis(std::string* _diagnosis);

        void setPrice(int _price);

    private:
        std::string* m_date;
        std::string* m_diagnosis;
        int m_price = 0;
        bool m_first_visit = true;
};
