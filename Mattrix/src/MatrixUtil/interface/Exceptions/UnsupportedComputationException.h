//
//  UnsupportedComputationException.h
//  Mattrix
//
//  Created by Matthew Hokinson on 12/3/19.
//

#ifndef UnsupportedComputationException_h
#define UnsupportedComputationException_h

//Libraries
#include <exception>
#include <string>

namespace MatrixUtil {
    class UnsupportedComputationException : public Exception {
    public:
        //================
        // Constructor
        //================
        explicit UnsupportedComputationException(const std::string & msg =
                                                 "This opperation is not supported yet!") :
                                                message(msg) {}
        
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

#endif /* UnsupportedComputationException_h */
