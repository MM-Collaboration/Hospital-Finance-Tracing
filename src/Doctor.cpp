#pragma once
#include <iostream>
#include <string>
#include "Doctor.h"
using namespace std;

/*
Категории врачей:
вторая
первая
высшая

Специализации врачей:
хирург
психолог
невролог
окулист
терапевт
*/

Doctor::Doctor(string _fullName, string _specialization, string _qualification) {
    m_fullName = &_fullName;
    m_specialization = &_specialization;
    m_qualification = &_qualification;
} 

string Doctor::getFullName() {
    return *m_fullName;
}

string Doctor::getQualification() {
    return *m_qualification;
}

string Doctor::getSpecialization() {
    return *m_specialization;
}

void Doctor::setFullName(string* _fullName) {
    m_fullName = _fullName;
}

void Doctor::setFullName(string _fullName) {
    m_fullName = &_fullName;
}

void Doctor::setQualification(string* _qualification) {
    m_qualification = _qualification;
}

void Doctor::setQualification(string _qualification) {
    m_qualification = &_qualification;
}

void Doctor::setSpecialization(string* _specialization) {
    m_specialization = _specialization;
}

void Doctor::setSpecialization(string _specialization) {
    m_specialization = &_specialization;
}
