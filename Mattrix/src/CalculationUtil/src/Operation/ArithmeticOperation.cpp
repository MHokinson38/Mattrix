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

Matrix ArithmeticOperation::perform() {
    switch (operand.getOperation()) {
        case OperationType::add:
            return lhs + rhs;
        case OperationType::subtract:
            return lhs - rhs;
        case OperationType::multiply:
            return lhs * rhs; //Error will be thrown for dimension
        case OperationType::divide:
            return lhs / rhs; //Error will be thrown if rhs is not scalar (1x1)
        default:
            break; //TODO Add exception
    }
}

std::ostream& ArithmeticOperation::print(std::ostream& os) const {
    return os << operand;
}
