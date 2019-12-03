//
//  InputLine.cpp
//  Mattrix
//
//  Created by Matthew Hokinson on 12/1/19.
//
//Libraries
#include <stdio.h>
#include <iostream>

//My Files
#include <CalculationUtil/interface/InputLine.h>

//===================
// Stream Overloads
//===================
std::ostream& CalculationUtil::operator<<(std::ostream& os, const InputLine& line) {
    return os << line.output.prettyPrint();
}

std::istream& CalculationUtil::operator>>(std::istream& is, InputLine& line) {
    is >> line.exp;
    
    line.output = line.exp.evaluate();
    
    return is;
}
