#include "gtest/gtest.h"
#include "../src/Patient.cpp"
using namespace std;

TEST(PatientTest, getFullName) {
    string fullName = "Simple Name";
    string yearBirth = "2000";
    string snils = "00000000000";
    string phoneNumber = "89000000000";
    Patient Unit1(fullName, yearBirth, snils, phoneNumber);
    EXPECT_EQ(Unit1.getFullName(), fullName);
}

TEST(PatientTest, getYearBirth) {
    string fullName = "Simple Name";
    string yearBirth = "2000";
    string snils = "00000000000";
    string phoneNumber = "89000000000";
    Patient Unit1(fullName, yearBirth, snils, phoneNumber);
    EXPECT_EQ(Unit1.getYearBirth(), yearBirth);
}

TEST(PatientTest, getSNILS) {
    string fullName = "Simple Name";
    string yearBirth = "2000";
    string snils = "00000000000";
    string phoneNumber = "89000000000";
    Patient Unit1(fullName, yearBirth, snils, phoneNumber);
    EXPECT_EQ(Unit1.getSNILS(), snils);
}

TEST(PatientTest, getPhoneNumber) {
    string fullName = "Simple Name";
    string yearBirth = "2000";
    string snils = "00000000000";
    string phoneNumber = "89000000000";
    Patient Unit1(fullName, yearBirth, snils, phoneNumber);
    EXPECT_FALSE(Unit1.getPhoneNumber().compare(phoneNumber));
    if (phoneNumber.length() == PHONE_NUMBER_LEN) {
        EXPECT_EQ(Unit1.getPhoneNumber().length(), PHONE_NUMBER_LEN) << "getPhoneNumber returns not " << PHONE_NUMBER_LEN << " nums";
    } else {
        FAIL() << "getPhoneNumber wrang phoneNumber string len";
    }
}

TEST(PatientTest, setPhoneNumber) {
    string fullName = "Simple Name";
    string yearBirth = "2000";
    string snils = "00000000000";
    string phoneNumber = "89000000000";
    string phoneNumber1 = "89111111111";
    string str1 = "12345";
    string str2 = "12345678901234567";
    Patient Unit1(fullName, yearBirth, snils, phoneNumber);
    Unit1.setPhoneNumber(phoneNumber1);
    EXPECT_FALSE(Unit1.getPhoneNumber().compare(phoneNumber1));
    Unit1.setPhoneNumber(str1);
    EXPECT_FALSE(Unit1.getPhoneNumber().compare(phoneNumber1)) << "Setted wrang phoneNumber value"; 
    Unit1.setPhoneNumber(str2);
    EXPECT_FALSE(Unit1.getPhoneNumber().compare(phoneNumber1)) << "Setted wrang phoneNumber value";
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
