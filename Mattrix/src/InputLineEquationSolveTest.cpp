//
//  InputLineEquationSolveTest.cpp
//  MattrixTest
//
//  Created by Matthew Hokinson on 12/8/19.
//
//Libraries
#include <stdio.h>
#include <catch.hpp>
#include <string>

//MY Files
#include <CalculationUtil/interface/InputLine.h>
#include <MatrixUtil/interface/Exceptions/InvalidSyntaxException.h>
#include <MatrixUtil/interface/Exceptions/UnsupportedComputationException.h>
#include <MatrixUtil/interface/Exceptions/ComputationalLogicException.h>

#include <RandomUtils/interface/InvalidCharacterException.h>

TEST_CASE("Testing Valid Equation Solves") {
    //=========================
    // Testing Constants
    //=========================
    //Simple Solves
    const std::string simpleScalarEqn1 = "3x = 9";
    const std::string simpleScalarEqn1Sol = "[3.000000]";
    const std::string simpleScalarEqn2 = "-15x = 30";
    const std::string simpleScalarEqn2Sol = "[-2.000000]";
    
    //Simple Matrix Equations
    const std::string simpleMatrixEqn1 = "[1,0;0,1]x = [3;4]";
    const std::string simpleMatrixEqn1Sol = "[[3.000000][4.000000]]";
    const std::string simpleMatrixEqn2 = "[1,2;3,4]x = [4;4]";
    const std::string simpleMatrixEqn2Sol = "[[-4.000000][4.000000]]";

    
    //==================
    // Input Line
    //==================
    CalculationUtil::InputLine inLine;
    inLine.equationMode();
    
    SECTION("Solving simple equations with scalars") {
        inLine.setInput(simpleScalarEqn1);
        std::cout << inLine << std::endl;
        REQUIRE(inLine.getOutputMatrixString().compare(simpleScalarEqn1Sol) == 0);
        
        inLine.setInput(simpleScalarEqn2);
        std::cout << inLine << std::endl;
        REQUIRE(inLine.getOutputMatrixString().compare(simpleScalarEqn2Sol) == 0);
    }
    
    SECTION("Solving Simple matrix equations") {
        inLine.setInput(simpleMatrixEqn1);
        std::cout << inLine << std::endl;
        REQUIRE(inLine.getOutputMatrixString().compare(simpleMatrixEqn1Sol) == 0);
        
        inLine.setInput(simpleMatrixEqn2);
        std::cout << inLine << std::endl;
        REQUIRE(inLine.getOutputMatrixString().compare(simpleMatrixEqn2Sol) == 0);
    }
    
}
