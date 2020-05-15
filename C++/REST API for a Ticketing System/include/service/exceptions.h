/**
 * @author Jonathan Flores
 * @date 2019-12-01
 * Copyright 2019
*/

#ifndef EXCEPTIONS_H_INCLUDED
#define EXCEPTIONS_H_INCLUDED

#include <stdexcept>

/**
* Exception just in case
*/
class justincase_error: public std::runtime_error {
 public:
    /**
    * @param errMessage An error message.
    */
    explicit justincase_error(const char* errMessage) :
        std::runtime_error(errMessage) {
    }
};

#endif // EXCEPTIONS_H_INCLUDED
