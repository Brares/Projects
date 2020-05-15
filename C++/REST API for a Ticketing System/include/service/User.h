/**
 * @author Jonathan Flores
 * @date 2019-12-01
 * Copyright 2019
*/

#include <string>
#ifndef USER_H
#define USER_H

class User {
 public:
  /**
  * @enum UserType - Enum for user type
  * @brief User is employee or client
  */
  enum UserType { Employee, Client };
  /**
  * @brief Default constructor
  */
  User() {}
  /**
  * @brief Constructor for User
  * @param _name - Username of User
  * @param _typeuser - The user's type (employee or client)
  */
  User(std::string _name, UserType _typeuser);
  /**
  * @brief Return the user ID
  */
  int getID();
  /**
  *@brief Return the username
  */
  std::string getName();
  /**
  * @brief Return the type of the user
  */
  UserType getUserType();
  /**
  * @brief Turn the enum to a string
  */
  std::string getStringUserType();
  /**
  * @brief Setting the user ID
  * @param _ID - The id of the user
  */
  void setID(int _ID);
  /**
  *@brief Setting username
  *@param _name - The username
  */
  void setName(std::string _name);
  /**
  *@brief Setting user type
  *@param _userType - The type of user
  */
  void setUserType(UserType _userType);

 private:
  /**
  *@brief user ID
  */
  int ID;
  /**
  *@brief user name
  */
  std::string name;
  /**
  *@brief user type
  */
  UserType userType;
};

#endif // USER_H
