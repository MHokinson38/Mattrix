//
//  CoolUtilities.cpp
//  Mattrix
//
//  Created by Matthew Hokinson on 11/19/19.
//
//Libraries
#include <string>
#include <exception>
#include <cmath>

//My Files
#include <RandomUtils/interface/CoolUtilities.h>
#include <RandomUtils/interface/InvalidCharacterException.h>

//=================
// Casting
//=================
int RandomUtils::getIntFromChar(char c) {
    switch(c) {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
    }
    throw InvalidCharacterException(&"You entered a non-valid numberical character: " [ c]);
}

double RandomUtils::getDoubleFromString(const std::string & str) {
    try {
        return std::stod(str);
    }
    catch(std::invalid_argument& err) {
        throw InvalidCharacterException("Invalid Number Entered: " + str);
    }
}

std::string RandomUtils::getStringFromDouble(double num) {
    return std::to_string(num);
}

//==============
// String Manipulation
//==============
void RandomUtils::removeWhiteSpace(std::string &str) {
    std::string condensed = "";
    
    for(auto& c : str) {
        if(c != ' ') {condensed += c;}
    }
    
    str = condensed;
}

void RandomUtils::removeExcessParentheses(std::string &str) {
    //This works post white Space removal
    bool hasRedundantParentheses = str[0] == '(' && str[str.size() - 1] == ')';
    
    if(hasRedundantParentheses) {
        str = str.substr(1, str.size() - 2);
    }
}

//=============
// Value Checking
//=============
bool RandomUtils::isIntegerValue(double val) {
    return doubleEqual(val - std::floor(val), 0);
}

bool RandomUtils::doubleEqual(double a, double b) {
    return std::abs(a - b) < DOUBLE_EPSILON;
}
