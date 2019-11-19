//
//  InvalidCharacterException.h
//  Mattrix
//
//  Created by Matthew Hokinson on 11/19/19.
//

#ifndef InvalidCharacterException_h
#define InvalidCharacterException_h

//Libraries
#include <string>
#include <exception>

namespace RandomUtils {
    class InvalidCharacterException : public std::exception {
    public:
        //=============
        // Constructor
        //=============
        explicit InvalidCharacterException(std::string  eMesg = "This is not a valid Character!") : message(std::move(eMesg)) {}

        //=============
        // What overload
        //=============
        const char* what() {return message.c_str();}

    private:
        std::string message;
    };
}


#endif /* InvalidCharacterException_h */
