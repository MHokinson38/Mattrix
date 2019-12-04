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
#include <MatrixUtil/interface/Exceptions/InvalidSyntaxException.h>
#include <MatrixUtil/interface/Exceptions/UnsupportedComputationException.h>
#include <MatrixUtil/interface/Exceptions/ComputationalLogicException.h>

#include <RandomUtils/interface/InvalidCharacterException.h>

TEST_CASE("Testing Valid Matrix Calculations") {
    //===================
    // Matrix String Constants
    //===================
    //Single Operations
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
    std::string simpleInverseSol = "[[-2.000000, 1.000000][1.500000, -0.500000]]";
    std::string simpleTranspose = "[1,2;3,4]^T";
    std::string simpleTransposeSol = "[[1.000000, 3.000000][2.000000, 4.000000]]";
    std::string simpleExponent = "[1,2;3,4]^2";
    std::string simpleExponentSol = "[[7.000000, 10.000000][15.000000, 22.000000]]";
    
    //Multiple Operation Expressions
    std::string additionAndSubtraction = "[1,0;0,1] - [1,1;1,1] + [1,1;1,1]";
    std::string additionAndSubtractionSol = "[[1.000000, 0.000000][0.000000, 1.000000]]";
    std::string inverseAndExponent = "[1,2;3,4]^-2";
    std::string inverseAndExponentSol = "[[5.500000, -2.500000][-3.750000, 1.750000]]";
    std::string dotProduct = "[1;2;3]^T * [1;1;1]"; //Multiplication and Transpose
    std::string dotProductSol = "[6.000000]";
    std::string multAndDivision = "[1,0;0,1] * [4,4;4,4] / 4";
    std::string multAndDivisionSol = "[[1.000000, 1.000000][1.000000, 1.000000]]";
    std::string multAndAddition = "[1,0;0,1] + [1,1;1,1]*[0,1;1,0]";
    std::string multAndAdditionSol = "[[2.000000, 1.000000][1.000000, 2.000000]]";
    
    std::string parnethesesMulAdd = "[1,0;0,1] * ([1,1;1,1] + [1,1;1,1])";
    std::string parenthesesMulAddSol = "[[2.000000, 2.000000][2.000000, 2.000000]]";
    std::string parenthesesTranspose = "([1,2;3,4]^T)^T";
    std::string parenthesesTransposeSol = "[[1.000000, 2.000000][3.000000, 4.000000]]";
    std::string parenthesesSubAdd = "(([1,2,3;4,5,6;7,8,9]) - [1,2,3;4,5,6;7,8,1]) * [1,0,0;0,1,0;0,0,1]";
    std::string parenthesesSubAddSol = "[[0.000000, 0.000000, 0.000000][0.000000, 0.000000, 0.000000][0.000000, 0.000000, 8.000000]]";
    std::string parenthesesDiv = "[4,4,4;4,4,4] / ([1,1,1,1] * [1;1;1;1])";
    std::string parenthesesDivSol = "[[1.000000, 1.000000, 1.000000][1.000000, 1.000000, 1.000000]]";
    std::string parenthesesExp = "[1,1;0,1] ^ ([1;2;3]^T * [1;1;1])";
    std::string parenthesesExpSol = "[[1.000000, 6.000000][0.000000, 1.000000]]";
    
    //================
    // Input Line
    //=================
    CalculationUtil::InputLine inLine;

    SECTION("Simple Matrice (One operation)") {
        inLine.setInput(noOperation);
        std::cout << inLine << std::endl;
        REQUIRE(inLine.getOutputMatrixString().compare(noOperationSol) == 0);

        inLine.setInput(simpleAddition);
        std::cout << inLine << std::endl;
        REQUIRE(inLine.getOutputMatrixString().compare(simpleAdditionSol) == 0);

        inLine.setInput(simpleSubtraction);
        std::cout << inLine << std::endl;
        REQUIRE(inLine.getOutputMatrixString().compare(simpleSubtractionSol) == 0);

        inLine.setInput(simpleMatMultiplication);
        std::cout << inLine << std::endl;
        REQUIRE(inLine.getOutputMatrixString().compare(simpleMatMultiplicationSol) == 0);

        inLine.setInput(simpleScalarMultL);
        std::cout << inLine << std::endl;
        REQUIRE(inLine.getOutputMatrixString().compare(simpleScalarMultSol) == 0);

        inLine.setInput(simpleScalarMultR);
        std::cout << inLine << std::endl;
        REQUIRE(inLine.getOutputMatrixString().compare(simpleScalarMultSol) == 0);

        inLine.setInput(simpleDivision);
        std::cout << inLine << std::endl;
        REQUIRE(inLine.getOutputMatrixString().compare(simpleDivisionSol) == 0);

        inLine.setInput(simpleInverse);
        std::cout << inLine << std::endl;
        REQUIRE(inLine.getOutputMatrixString().compare(simpleInverseSol) == 0);

        inLine.setInput(simpleTranspose);
        std::cout << inLine << std::endl;
        REQUIRE(inLine.getOutputMatrixString().compare(simpleTransposeSol) == 0);

        inLine.setInput(simpleExponent);
        std::cout << inLine << std::endl;
        REQUIRE(inLine.getOutputMatrixString().compare(simpleExponentSol) == 0);
    }

    SECTION("More Complex Expressios (Two or more opearations)") {
        inLine.setInput(additionAndSubtraction);
        std::cout << inLine << std::endl;
        REQUIRE(inLine.getOutputMatrixString().compare(additionAndSubtractionSol) == 0);

        inLine.setInput(inverseAndExponent);
        std::cout << inLine << std::endl;
        REQUIRE(inLine.getOutputMatrixString().compare(inverseAndExponentSol) == 0);

        inLine.setInput(dotProduct);
        std::cout << inLine << std::endl;
        REQUIRE(inLine.getOutputMatrixString().compare(dotProductSol) == 0);

        inLine.setInput(multAndDivision);
        std::cout << inLine << std::endl;
        REQUIRE(inLine.getOutputMatrixString().compare(multAndDivisionSol) == 0);

        inLine.setInput(multAndAddition);
        std::cout << inLine << std::endl;
        REQUIRE(inLine.getOutputMatrixString().compare(multAndAdditionSol) == 0);
    }

    SECTION("Expressions with Parentheses") {
        inLine.setInput(parnethesesMulAdd);
        std::cout << inLine << std::endl;
        REQUIRE(inLine.getOutputMatrixString().compare(parenthesesMulAddSol) == 0);

        inLine.setInput(parenthesesSubAdd);
        std::cout << inLine << std::endl;
        REQUIRE(inLine.getOutputMatrixString().compare(parenthesesSubAddSol) == 0);

        inLine.setInput(parenthesesDiv);
        std::cout << inLine << std::endl;
        REQUIRE(inLine.getOutputMatrixString().compare(parenthesesDivSol) == 0);

        inLine.setInput(parenthesesExp);
        std::cout << inLine << std::endl;
        REQUIRE(inLine.getOutputMatrixString().compare(parenthesesExpSol) == 0);

        inLine.setInput(parenthesesTranspose);
        std::cout << inLine << std::endl;
        REQUIRE(inLine.getOutputMatrixString().compare(parenthesesTransposeSol) == 0);
    }
}

TEST_CASE("Expressions with Invalid Inputs") {
    //===================
    // Testing Constants
    //===================
    //Invalid Character Errors
    std::string badInputLetters = "[1,2,3;jkflds,2,3]";

    //Syntax Errors
    std::string matrixDimensionError = "[1,2,3;1,2]";
    std::string invalidMatrixSyntax = "-[1,2;3,4]";

    //Unsupported Computation Errors
    std::string unsupportedPower = "[1,2;3,4] ^ 1.5";

    //Computational Logic Error
    std::string multiplicationDimensionError = "[1,2;3,4] * [1,0,0;0,1,0;0,0,1]";
    std::string singularMatrixInversion = "[1,1;0,0]^-1";

    //================
    // Input Line
    //=================
    CalculationUtil::InputLine inLine;

    SECTION("Invalid Character Exceptions") {
        try {
            inLine.setInput(badInputLetters);

            REQUIRE(false); //So we know we leave before this line
        }
        catch(RandomUtils::InvalidCharacterException& er) {
            REQUIRE(true); //Threw the right exception
        }
        catch(...) {
            REQUIRE(false); //Threw some other exception
        }
    }

    SECTION("Syntax Exceptions") {
        try {
            inLine.setInput(matrixDimensionError);

            REQUIRE(false); //So we know we leave before this line
        }
        catch(MatrixUtil::InvalidSyntaxException& er) {
            REQUIRE(true); //Threw the right exception
        }
        catch(...) {
            REQUIRE(false); //Threw some other exception
        }
        //===============================================================
        try {
            inLine.setInput(invalidMatrixSyntax);

            REQUIRE(false); //So we know we leave before this line
        }
        catch(MatrixUtil::InvalidSyntaxException& er) {
            REQUIRE(true); //Threw the right exception
        }
        catch(...) {
            REQUIRE(false); //Threw some other exception
        }
    }

    SECTION("Computational Logic Erros") {
        try {
            inLine.setInput(multiplicationDimensionError);

            REQUIRE(false); //So we know we leave before this line
        }
        catch(MatrixUtil::ComputationalLogicException& er) {
            REQUIRE(true); //Threw the right exception
        }
        catch(...) {
            REQUIRE(false); //Threw some other exception
        }
        //===============================================================
        try {
            inLine.setInput(singularMatrixInversion);

            REQUIRE(false); //So we know we leave before this line
        }
        catch(MatrixUtil::ComputationalLogicException& er) {
            REQUIRE(true); //Threw the right exception
        }
        catch(...) {
            REQUIRE(false); //Threw some other exception
        }
    }
    
    SECTION("Unsupported Computation Errors") {
        try {
            inLine.setInput(unsupportedPower);
        
            REQUIRE(false); //So we know we leave before this line
        }
        catch(MatrixUtil::UnsupportedComputationException& er) {
            REQUIRE(true); //Threw the right exception
        }
        catch(...) {
            REQUIRE(false); //Threw some other exception
        }
    }
}
