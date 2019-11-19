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

