//
//  OperationType.cpp
//  Mattrix
//
//  Created by Matthew Hokinson on 11/18/19.
//
//Libraries
#include <stdio.h>
#include <iostream>

//My Files
#include "CalculationUtil/interface/Operations/OperationType.h"

using OperationType = CalculationUtil::OperationType;

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

//=================
// Helping Functions
//=================
int OperationType::getPemdasFromChar(char opChar) {
    switch(opChar) {
        case '+':
            return OperationType::pemdas[OpType::add];
        case '-':
            return OperationType::pemdas[OpType::subtract];
        case '*':
            return OperationType::pemdas[OpType::multiply];
        case '/':
            return OperationType::pemdas[OpType::divide];
        case '^':
            return OperationType::pemdas[OpType::exponent];
    }
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

