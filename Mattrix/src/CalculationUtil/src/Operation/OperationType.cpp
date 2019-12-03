//
//  OperationType.cpp
//  Mattrix
//
//  Created by Matthew Hokinson on 11/18/19.
//
//Libraries
#include <stdio.h>
#include <iostream>
#include <map>

//My Files
#include "CalculationUtil/interface/Operations/OperationType.h"

using OperationType = CalculationUtil::OperationType;

//=================
// Constructors
//=================
OperationType::OperationType(char c) {
    if(isOperationCharacter(c)) {
        operation = charToOpMap[c];
    }
    else {
        //TODO add exception
    }
}

//=================
// Copy Assignment Operator
//=================
OperationType& OperationType::operator=(const OperationType& other) {
    this->operation = other.operation;
    
    return *this;
}

//=================
// Getters
//=================
bool OperationType::isFunctional() {
    switch(operation) {
        case OpType::add:
        case OpType::subtract:
        case OpType::multiply:
        case OpType::divide:
            return false;
        default:
            return true;
    }

}

char OperationType::getOpAsChar() {
    switch (operation) {
        case OperationType::add:
            return '+';
        case OperationType::subtract:
            return '-';
        case OperationType::multiply:
            return '*';
        case OperationType::divide:
            return '/';
        case OperationType::exponent:
        case OperationType::inverse:
        case OperationType::transpose:
            return '^';
        default:
            return ' ';
    }
}

//=================
// Static Helping Functions
//=================
bool OperationType::isOperationCharacter(char opChar) {
    std::map<char, OpType>::iterator finder = charToOpMap.find(opChar);
    
    //If the finder is at the end, we went through the whole map without hitting char 
    return finder != charToOpMap.end();
}

int OperationType::getPemdasFromChar(char opChar) {
    return pemdas[charToOpMap[opChar]];
}

//=================
// Ostream overload
//=================
std::ostream& CalculationUtil::operator<<(std::ostream &ostream, const OperationType &op) {
    switch (op.getOperation()) {
        case OperationType::add:
            ostream << " + ";
            break;
        case OperationType::subtract:
            ostream << " - ";
            break;
        case OperationType::multiply:
            ostream << " * ";
            break;
        case OperationType::divide:
            ostream << " / ";
            break;
        case OperationType::inverse:
            ostream << "^-1 ";
            break;
        case OperationType::exponent:
            ostream << "^";
            break;
        case OperationType::transpose:
            ostream << "T";
            break;
        default:
            ostream << "";
    }
    
    return ostream;
}

