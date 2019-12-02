//
//  Expression.cpp
//  Mattrix
//
//  Created by Matthew Hokinson on 11/30/19.
//
//Libraries
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

//My Files
#include <CalculationUtil/interface/Operations/Operation.h>
#include <CalculationUtil/interface/Operations/OperationType.h>
#include <CalculationUtil/interface/Operations/ArithmeticOperation.h>
#include <CalculationUtil/interface/Operations/FunctionalOperation.h>
#include <CalculationUtil/interface/Expression.h>

//==================
// Constructors
//==================
CalculationUtil::Expression::Expression(const std::string & input) : inputLine(input) {
    getBaseOperation();
    parseInputLine();
}

//==================
// Evaluation
//==================
MatrixUtil::Matrix CalculationUtil::Expression::evaluate() {
    if(isBase) {
        return baseMatrix; //This is the "base case for recursion"
    }
    else if(baseOperation.isFunctional()) {
        //If the base operation is functional, there should only be two internal expressions
        // The base, and the exponent
        MatrixUtil::Matrix baseMatrix = internalExpressions[0].evaluate();
        
        Operation* opToPerform = baseOperation.isTranspose() ?
                new FunctionalOperation(baseOperation, baseMatrix) :
                new FunctionalOperation(baseOperation, baseMatrix,
                                        internalExpressions[1].evaluate().getScalarValue());
        
        return opToPerform->perform();
    }
    else {
        MatrixUtil::Matrix currentResult = internalExpressions[0].evaluate();
        
        for(int i = 0; i < internalExpressions.size() - 1; ++i) {
            Operation* opToPerform = new ArithmeticOperation(baseOperation,
                                                             currentResult,
                                                             internalExpressions[i+1].evaluate());
            
            currentResult = opToPerform->perform();
        }
        
        return currentResult;
    }
}

//==================
// Parsing
//==================
void CalculationUtil::Expression::parseInputLine() {
    std::string newPartialExp = "";
    
    for(auto& c : inputLine) {
        
    }
}

//==================
// Stream overloads
//==================
std::istream& CalculationUtil::operator>>(std::istream& is, Expression & exp) {
    std::string inputLine = "";
    
    char currentChar;
    while(is.get(currentChar)) {inputLine += currentChar;}
    
    exp.setInputLine(inputLine);
    
    return is;
}

