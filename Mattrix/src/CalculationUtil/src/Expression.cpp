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
#include <exception>

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
void CalculationUtil::Expression::getBaseOperation() {
    int numOpenParentheses = 0;
    bool hasParenthese = false;
    OperationType lowestOp(OperationType::OpType::empty);
    
    for(int i = 0; i < inputLine.size(); ++i) {
        if(inputLine[i] == OPENING_PARENTHESE) {
            hasParenthese = true;
            numOpenParentheses++;
        }
        else if(inputLine[i] == CLOSING_PARENTHESE) {
            numOpenParentheses--;
        }
        else if(OperationType::isOperationCharacter(inputLine[i]) && numOpenParentheses == 0) {
            if(OperationType::getPemdasFromChar(inputLine[i]) < lowestOp.getHierarchyLevel()) {
                lowestOp = OperationType(inputLine[i]);
            }
            
            // Going to use try to avoid putting in extra bounds check and will catch out of bounds
            if(lowestOp.isExponent()) {
                try {
                    if(inputLine[i+1] == TRANSPOSE_CHARACTER) {
                        lowestOp = OperationType(OperationType::OpType::transpose);
                    }
                    else if(inputLine[i+1] == INVERSE_CHARACTER) {
                        lowestOp = OperationType(OperationType::OpType::inverse);
                    }
                }
                catch(const std::out_of_range & excp) {
                    continue; //Do nothing, just thought this would be cooler than manual bounds check
                }
            }
        }
    }
    
    isBase = lowestOp.isNull() && !hasParenthese;
    baseOperation = lowestOp;
}

void CalculationUtil::Expression::parseInputLine() {
    std::string newPartialExp = "";
    
    if(isBase) {
        baseMatrix = MatrixUtil::Matrix(inputLine);
    }
    else {
        std::string currentInternalExp = "";
        int numOpenParentheses = 0;
        
        for(auto& c : inputLine) {
            if(c == OPENING_PARENTHESE) {
                numOpenParentheses++;
            }
            else if(c == CLOSING_PARENTHESE) {
                numOpenParentheses--;
            }
            else if(c == baseOperation.getOpAsChar() && numOpenParentheses == 0) {
                internalExpressions.push_back(Expression(currentInternalExp));
                currentInternalExp = "";
                
                if(baseOperation.isTranspose() ||
                   baseOperation.isInverse()) {break;} //We are going to ignore the T
                
                continue;
            }
            
            currentInternalExp += c;
        }
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

