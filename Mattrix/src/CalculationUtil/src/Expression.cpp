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

#include <MatrixUtil/interface/Matrix.h>

#include <RandomUtils/interface/CoolUtilities.h>


//==================
// Constructors
//==================
CalculationUtil::Expression::Expression(const std::string & input) : inputLine(input) {
    RandomUtils::removeWhiteSpace(inputLine);
    RandomUtils::removeExcessParentheses(inputLine); //Takes off parentheses in from and back in needed
    
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
        MatrixUtil::Matrix base = internalExpressions[0].evaluate();
        
        Operation* opToPerform = baseOperation.isTranspose() ?
                new FunctionalOperation(baseOperation, base) :
                new FunctionalOperation(baseOperation, base,
                                        internalExpressions[1].evaluate().getScalarValue());
        
        return opToPerform->perform();
    }
    else {
        MatrixUtil::Matrix currentResult = internalExpressions[0].evaluate();
        
        for(int i = 0; i < internalExpressions.size() - 1; ++i) {
            Operation* opToPerform = new ArithmeticOperation(operations[i],
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
        if(inputLine[i] == INVERSE_CHARACTER && i == 0) {
            continue; //This is a minus sign, not subtraction (i.e. -5)
        }
        
        if(inputLine[i] == OPENING_PARENTHESE) {
            hasParenthese = true;
            numOpenParentheses++;
        }
        else if(inputLine[i] == CLOSING_PARENTHESE) {
            numOpenParentheses--;
        }
        else if(OperationType::isOperationCharacter(inputLine[i]) && numOpenParentheses == 0) {
            if(OperationType::getPemdasFromChar(inputLine[i]) < lowestOp.getHierarchyLevel()) {
                if(OperationType(inputLine[i]).getOperation() == OperationType::OpType::subtract &&
                   OperationType(inputLine[i-1]).getOperation() == OperationType::OpType::exponent) {
                    continue;
                }
                
                lowestOp = OperationType(inputLine[i]);
            }
            
            // Going to use try to avoid putting in extra bounds check and will catch out of bounds
            if(lowestOp.isExponent()) {
                try {
                    if(inputLine[i+1] == TRANSPOSE_CHARACTER) {
                        lowestOp = OperationType(OperationType::OpType::transpose);
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
        
        for(int i = 0; i < inputLine.size(); ++i) {
            if(inputLine[i] == OPENING_PARENTHESE) {
                numOpenParentheses++;
            }
            else if(inputLine[i] == CLOSING_PARENTHESE) {
                numOpenParentheses--;
            }
            else if(OperationType::isOperationCharacter(inputLine[i]) &&
                    OperationType(inputLine[i]).getHierarchyLevel() == baseOperation.getHierarchyLevel() &&
                     numOpenParentheses == 0) {
                internalExpressions.push_back(Expression(currentInternalExp));
                operations.push_back(OperationType(inputLine[i]));
                currentInternalExp = "";
                
                if(baseOperation.isTranspose()) {break;} //We are going to ignore the T
                
                continue;
            }
            
            currentInternalExp += inputLine[i];
            
            if(i == (inputLine.size() - 1)) {
                internalExpressions.push_back(Expression(currentInternalExp));
            }
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
    
    exp = Expression(inputLine);
    
    return is;
}

