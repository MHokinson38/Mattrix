//
//  InputLineEvalTest.cpp
//  MattrixTest
//
//  Created by Matthew Hokinson on 12/4/19.
//
//Libraries
#include <stdio.h>
#include <catch.hpp>
#include <string>

//MY Files
#include <CalculationUtil/interface/InputLine.h>

TEST_CASE("Testing Valid Matrix Calculations") {
    //===================
    // Matrix String Constants
    //===================
    std::string noOperation = "[1,0;0,1]";
    std::string noOperationSol = "[[1.000000, 0.000000][0.000000, 1.000000]]";
    std::string simpleAddition = "[1,0;0,1] + [1,1;1,1]";
    std::string simpleAdditionSol = "[[2.000000, 1.000000][1.000000, 2.000000]]";
    std::string simpleSubtraction = "[1,0;0,1] - [1,1;1,1]";
    std::string simpleSubtractionSol = "[[0.000000, -1.000000][-1.000000, 0.000000]]";
    std::string simpleMatMultiplication = "[1,0;0,1] * [1,1;1,1]";
    std::string simpleMatMultiplicationSol = "[[1.000000, 1.000000][1.000000, 1.000000]]";
    std::string simpleScalarMultL = "5 * [1,1;1,1]";
    std::string simpleScalarMultR = "[1,1;1,1] * 5";
    std::string simpleScalarMultSol = "[[5.000000, 5.000000][5.000000, 5.000000]]";
    std::string simpleDivision = "[4,4;4,4] / 4";
    std::string simpleDivisionSol = "[[1.000000, 1.000000][1.000000, 1.000000]]";
    std::string simpleInverse = "[1,2;3,4]^-1";
    std::string simpleTranspose = "[1,2;3,4]^T";
    std::string simpleExponent = "[1,2;3,4]^2";
    
    std::string matStr4 = "[1,0;0,1] * ([1,1;1,1] + [1,1;1,1])"; //good
    std::string matStr5 = "[1,0;0,1] - [1,1;1,1] + [1,1;1,1]"; //good
    std::string matStr6 = "[1,0;0,1] + [1,1;1,1]*[0,1;1,0]"; //good
    std::string matStr11 = "[1,2;3,4]^-2"; //good
    std::string matStr12 = "([1,2;3,4]^T)^T"; //good
    std::string matStr13 = "(([1,2,3;4,5,6;7,8,9]) + [1,2,3;4,5,6;7,8,9]) * [1,0,0;0,1,0;0,0,1]"; //Good
    std::string matStr14 = "[4,4,4;4,4,4] / ([1,1,1,1] * [1;1;1;1])"; //good
    std::string matStr15 = "[1;2;3]^T * [1;1;1]"; //good
    
    //================
    // Input Line
    //=================
    CalculationUtil::InputLine inLine;
    
    SECTION("Simple Matrice (One operation)") {
        inLine.setInput(simpleAddition);
        std::cout << inLine << std::endl;
        std::cout << simpleAdditionSol;
        REQUIRE(inLine.getOutputMatrixString().compare(simpleAdditionSol) == 0);
        
        inLine.setInput(simpleSubtraction);
        std::cout << inLine << std::endl;
        REQUIRE(inLine.getOutputMatrixString().compare(simpleSubtractionSol) == 0);
        
        inLine.setInput(simpleMatMultiplication);
        std::cout << inLine << std::endl;
        REQUIRE(inLine.getOutputMatrixString().compare(simpleMatMultiplicationSol) == 0);
        
        inLine.setInput(simpleDivision);
        std::cout << inLine << std::endl;
        REQUIRE(inLine.getOutputMatrixString().compare(simpleDivisionSol) == 0);
    }
}

