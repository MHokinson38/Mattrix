//
//  CoolUtilities.cpp
//  Mattrix
//
//  Created by Matthew Hokinson on 11/19/19.
//
//Libraries
#include <string>
#include <exception>
#include <stdio.h>

//My Files
#include <RandomUtils/interface/CoolUtilities.h>
#include <RandomUtils/interface/InvalidCharacterException.h>

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

int RandomUtils::getDoubleFromString(const std::string & str) {
    return std::stod(str);
}

std::string RandomUtils::getStringFromDouble(double num) {
    return std::to_string(num);
}

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
