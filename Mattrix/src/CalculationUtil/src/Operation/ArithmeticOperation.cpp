//
//  ArithmeticOperation.cpp
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
#include <CalculationUtil/interface/Operations/ArithmeticOperation.h>
#include <MatrixUtil/interface/Matrix.h>

using ArithmeticOperation = CalculationUtil::ArithmeticOperation;
using Matrix = MatrixUtil::Matrix;

std::vector<Matrix> ArithmeticOperation::perform() {
    std::vector<Matrix> result;
    switch (operand.getOperation()) {
        case OperationType::add:
            result.push_back(lhs + rhs);
            break;
        case OperationType::subtract:
            result.push_back(lhs - rhs);
            break;
        case OperationType::multiply:
            result.push_back(lhs * rhs); //Error will be thrown for dimension
            break;
        case OperationType::divide:
            result.push_back(lhs / rhs); //Error will be thrown if rhs is not scalar (1x1)
            break;
        default:
            break;
    }
    
    return result;
}

std::ostream& ArithmeticOperation::print(std::ostream& os) {
    return os << operand;
}
