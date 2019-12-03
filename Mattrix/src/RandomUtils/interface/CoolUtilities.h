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
    int getIntFromChar(char c);

    int getDoubleFromString(const std::string & str);
    std::string getStringFromDouble(double num);

    void removeWhiteSpace(std::string & str);
    void removeExcessParentheses(std::string & str);
}


#endif /* CoolUtilities_h */
