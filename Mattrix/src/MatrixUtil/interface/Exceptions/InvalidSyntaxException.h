//
//  InvalidSyntaxException.h
//  Mattrix
//
//  Created by Matthew Hokinson on 12/3/19.
//

#ifndef InvalidSyntaxException_h
#define InvalidSyntaxException_h

//Libraries
#include <exception>
#include <string>

namespace MatrixUtil {
    class InvalidSyntaxException : public std::exception {
    public:
        //================
        // Constructor
        //================
        explicit InvalidSyntaxException(const std::string & msg = "Syntax Error!") : message(msg) {}
        
        //================
        // What Overload
        //================
        const char* what() {return message.c_str();}
        
    private:
        //=============
        // Data Members
        //=============
        std::string message;
    };
}

#endif /* InvalidSyntaxException_h */
