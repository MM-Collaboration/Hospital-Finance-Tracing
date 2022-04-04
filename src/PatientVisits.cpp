#pragma once
#include "PatientVisits.h"

std::string* PatientVisit::getDate() {
    return m_date;
}

std::string* PatientVisit::getDiagnosis() {
    return m_diagnosis;
}

int PatientVisit::getPrice() {
    return m_price;
}

bool PatientVisit::get_isFirstVisit() {
    return m_first_visit;
}

void PatientVisit::setDate(std::string* _date) {
    m_date = _date;
}

void PatientVisit::setDiagnosis(std::string* _diagnosis) {
    m_diagnosis = _diagnosis;
}

void PatientVisit::setPrice(int _price) {
    m_price = _price;
}
