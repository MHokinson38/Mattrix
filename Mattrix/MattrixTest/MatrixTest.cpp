//
//  MatrixTest.cpp
//  MattrixTest
//
//  Created by Matthew Hokinson on 11/19/19.
//
//Libraries
#include <stdio.h>
#include <catch.hpp>

//My Files
#include <../src/MatrixUtil/interface/Matrix.h>

//====================
// Testing Creation
//====================
TEST_CASE("Test Default Constructor") {
    MatrixUtil::Matrix testMat;

    REQUIRE(testMat.getIsScalar() == false);
}
