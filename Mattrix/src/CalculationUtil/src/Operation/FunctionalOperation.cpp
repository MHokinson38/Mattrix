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

std::vector<Matrix> FunctionalOperation::perform() {
    std::vector<Matrix> result;
    switch (operand.getOperation()) {
        case OperationType::exponent:
            result.push_back(object^pow);
            break;
        case OperationType::inverse:
            result.push_back(object.inverse());
            break;
        case OperationType::transpose:
            result.push_back(object.transpose());
        default:
            break;
    }
    
    return result;
}

std::ostream& FunctionalOperation::print(std::ostream& os) {
    if(operand.getOperation() == OperationType::exponent ||
       operand.getOperation() == OperationType::inverse) {
        return os << object << operand;
    }
    
    return os << operand << "(" << object << ")";
}


