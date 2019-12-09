//
//  Equation.cpp
//  Mattrix
//
//  Created by Matthew Hokinson on 12/8/19.
//

#include <stdio.h>

//My Files
#include <CalculationUtil/interface/Equation.h>
#include <CalculationUtil/interface/Expression.h>

#include <MatrixUtil/interface/Exceptions/InvalidSyntaxException.h>
#include <MatrixUtil/interface/Exceptions/UnsupportedComputationException.h>
#include <MatrixUtil/interface/Exceptions/ComputationalLogicException.h>

#include <RandomUtils/interface/CoolUtilities.h>

//==================
// Constructor
//==================
CalculationUtil::Equation::Equation(const std::string & equInput) {
    setInput(equInput);
}

//==================
// Set Input
//==================
void CalculationUtil::Equation::setInput(const std::string &equInput) {
    rawInput = equInput;
    
    RandomUtils::removeWhiteSpace(rawInput);
    checkBasicSyntax(rawInput);
    
    parseInput(rawInput);
}

//==================
// Syntax Check
//==================
void CalculationUtil::Equation::checkBasicSyntax(const std::string & input) {
    int numVariables = 0;
    int numEquals = 0;
    
    for(auto& c : input) {
        if(c == VARIABLE_CHAR) {
            numVariables++;
        }
        else if(c == EQUALS_SIGN) {
            numEquals++;
        }
    }
    
    if(numVariables != 1 || numEquals != 1) {
        throw MatrixUtil::InvalidSyntaxException("Invalid Equation Syntax!");
    }
}

//==================
// Parsing
//==================
void CalculationUtil::Equation::parseInput(const std::string &input) {
    std::string aString = "";
    std::string bString = "";
    bool onLHS = true;
    bool foundX = false;
    
    for(auto& c : input) {
        if(c == VARIABLE_CHAR) {// We will have already checked for syntax here
            continue;
        }
        else if(c == EQUALS_SIGN) {
            onLHS = false;
            continue;
        }
        
        if(onLHS) {
            aString += c;
        }
        else {
            bString += c;
        }
    }
    
    //Get As Matrices
    Expression exp(aString);
    a = exp.evaluate();
    
    exp.setInputLine(bString);
    b = exp.evaluate();
}

//==================
// Solving
//==================
MatrixUtil::Matrix CalculationUtil::Equation::solve() {
    MatrixUtil::Matrix aInverse = a.inverse();
        
    return MatrixUtil::Matrix(aInverse * b);
}
