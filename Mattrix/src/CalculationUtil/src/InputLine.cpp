//
//  InputLine.cpp
//  Mattrix
//
//  Created by Matthew Hokinson on 12/1/19.
//
//Libraries
#include <stdio.h>
#include <iostream>
#include <string>
#include <strstream>

//My Files
#include <CalculationUtil/interface/InputLine.h>

//===================
// Constructors
//===================
CalculationUtil::InputLine::InputLine(const std::string & input) : mode(Mode::EXPRESSION) {
    setInput(input);
}

//===================
// Calculator
//===================
void CalculationUtil::InputLine::setInput(const std::string& input) {
    rawInput = input;
    
    switch (mode) {
        case Mode::EQUATION:
            eq.setInput(input);
            output = eq.solve();
            break;
        case Mode::EXPRESSION:
            exp.setInputLine(input);
            output = exp.evaluate();
            break;
        case Mode::APPROXEQUATION:
            eq.setInput(input);
            output = eq.leastSquaresSolve();
            break;
        case Mode::DETERMINANT:
            exp.setInputLine(input);
            output = (exp.evaluate()).getDeterminant();
            break;
    }
}

//===================
// Stream Overloads
//===================
std::ostream& CalculationUtil::operator<<(std::ostream& os, const InputLine& line) {
    return os << line.output.regularPrint();
}

std::istream& CalculationUtil::operator>>(std::istream& is, InputLine& line) {
    std::string input = "";
    std::getline(is, input);
    
    line.setInput(input);
    
    return is;
}
