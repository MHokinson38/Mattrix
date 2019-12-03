//
//  FunctionalOperation.cpp
//  Mattrix
//
//  Created by Matthew Hokinson on 11/18/19.
//
//Libraries
#include <stdio.h>
#include <iostream>
#include <vector>

//My Files
#include <CalculationUtil/interface/Operations/OperationType.h>
#include <CalculationUtil/interface/Operations/Operation.h>
#include <CalculationUtil/interface/Operations/FunctionalOperation.h>
#include <MatrixUtil/interface/Matrix.h>

using FunctionalOperation = CalculationUtil::FunctionalOperation;
using Matrix = MatrixUtil::Matrix;

Matrix FunctionalOperation::perform() {
    switch (operand.getOperation()) {
        case OperationType::exponent:
            return object^(MatrixUtil::Matrix(pow));
            break;
        case OperationType::inverse:
            return object.inverse();
            break;
        case OperationType::transpose:
            return object.transpose();
        default:
            break; //TODO Add exception
    }
}

std::ostream& FunctionalOperation::print(std::ostream& os) const {
    if(operand.getOperation() == OperationType::exponent ||
       operand.getOperation() == OperationType::inverse) {
        return os << object << operand;
    }
    
    return os << operand << "(" << object << ")";
}


