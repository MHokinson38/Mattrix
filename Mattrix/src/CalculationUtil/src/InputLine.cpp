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
CalculationUtil::InputLine::InputLine(const std::string & input) {
    setInput(input);
}

//===================
// Calculator
//===================
void CalculationUtil::InputLine::setInput(const std::string& input) {
    if(solveEquation) {
        eq.setInput(input);
        output = eq.solve();
    }
    else {
        exp.setInputLine(input);
        output = exp.evaluate();
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
