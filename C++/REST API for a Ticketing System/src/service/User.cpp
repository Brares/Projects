/**
 * @author Jonathan Flores
 * @date 2019-12-01
 * Copyright 2019
*/

#include "string"
#include "User.h"

User::User(std::string _name, UserType _typeuser) {
    name = _name;
    userType = _typeuser;
}

int User::getID() {
    return ID;
}

std::string User::getName() {
    return name;
}

User::UserType User::getUserType() {
    return userType;
}

std::string User::getStringUserType() {
    std::string type;
    if (userType == Client)
        type = "Client";
    if (userType == Employee)
        type = "Employee";
    return type;
}

void User::setID(int _ID) {
    ID = _ID;
}

void User::setName(std::string _name) {
    name = _name;
}

void User::setUserType(UserType _userType) {
    userType = _userType;
}
