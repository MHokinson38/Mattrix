//
//  CoolUtilities.h
//  Mattrix
//
//  Created by Matthew Hokinson on 11/19/19.
//

#ifndef CoolUtilities_h
#define CoolUtilities_h

namespace RandomUtils {
    //=================
    // Random Utility functions
    //=================
    //=============
    // Constants
    //=============
    static const inline double DOUBLE_EPSILON = .0001;

    //=============
    // Casting
    //=============
    int getIntFromChar(char c);
    double getDoubleFromString(const std::string & str);
    std::string getStringFromDouble(double num);

    //=============
    // String Manipulation
    //=============
    void removeWhiteSpace(std::string & str);
    void removeExcessParentheses(std::string & str);

    //=============
    // Number Checking
    //=============
    bool isIntegerValue(double val);

    bool doubleEqual(double a, double b);
}


#endif /* CoolUtilities_h */
