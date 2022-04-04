#pragma once
#include "Patient.h"
#include "global_vars.cpp"

Patient::Patient(std::string* _fullName, std::string* _yearBirth, std::string* _snils, std::string*_phoneNumber) {
    m_fullName = _fullName;
    m_yearBirth = _yearBirth;
    m_snils = _snils;
    m_phoneNumber = _phoneNumber;
}

Patient::Patient(std::string _fullName, std::string _yearBirth, std::string _snils, std::string _phoneNumber) {
    m_fullName = &_fullName;
    m_yearBirth = &_yearBirth;
    m_snils = &_snils;
    m_phoneNumber = &_phoneNumber;
} 

std::string Patient::getFullName() {
    return *m_fullName;
}

std::string Patient::getYearBirth() {
    return *m_yearBirth;
}

std::string Patient::getSNILS() {
    return *m_snils;
}

std::string Patient::getPhoneNumber() {
    return *m_phoneNumber;
}

void Patient::setFullName(std::string _fullName) {
    m_fullName = &_fullName;
}

void Patient::setYearBirth(std::string _yearBirth) {
    if (stoi(_yearBirth) > AGE_RANGE_BEGIN && stoi(_yearBirth) <= AGE_RANGE_END) {
        m_yearBirth = &_yearBirth;
    }
}

void Patient::setSnils(std::string _snils) {
    m_snils = &_snils;
}

void Patient::setPhoneNumber(std::string _phoneNumber) {
    if (_phoneNumber.length() == PHONE_NUMBER_LEN) {
        m_phoneNumber = &_phoneNumber;
    }
}
