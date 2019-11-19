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

int RandomUtils::getIntFromString(const std::string & str) {
    bool isNegative = str[0] == '-'; //Set to negative if appropriate
    int returnNum = 0;
    
    for(auto& num : str.substr(1)) {
        returnNum *= 10;
        returnNum += getIntFromChar(num);
    }
    
    return isNegative ? -1 * returnNum : returnNum;
}
