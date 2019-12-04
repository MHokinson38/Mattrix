//
//  ComputationalLogicException.h
//  Mattrix
//
//  Created by Matthew Hokinson on 12/4/19.
//

#ifndef ComputationalLogicException_h
#define ComputationalLogicException_h

namespace MatrixUtil {
    class ComputationalLogicException : public std::exception {
    public:
        //================
        // Constructor
        //================
        explicit ComputationalLogicException(const std::string & msg = "Logic Error!") : message(msg) {}
        
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

#endif /* ComputationalLogicException_h */
