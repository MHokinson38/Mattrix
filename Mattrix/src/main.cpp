#include "ofMain.h"
#include "ofApp.h"

//My Files
#include <CalculationUtil/interface/InputLine.h>
#include <MatrixUtil/interface/Exceptions/InvalidSyntaxException.h>
#include <MatrixUtil/interface/Exceptions/UnsupportedComputationException.h>
#include <RandomUtils/interface/InvalidCharacterException.h>

//Libraries
#include <string>
#include <iostream>
#include <strstream>

//========================================================================
int main( ){
//	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context
//
//	// this kicks off the running of my app
//	// can be OF_WINDOW or OF_FULLSCREEN
//	// pass in width and height too:
//	ofRunApp(new ofApp());
    //Some Jank tests
    std::string matStr = "[1,0;0,1]"; //good
    std::string matStr1 = "[1,0;0,1] + [1,1;1,1]"; //good
    std::string matStr2 = "[1,0;0,1]*[1,1;1,1]"; //good
    std::string matStr3 = "5*[1,0;0,1]"; //good
    std::string matStr4 = "[1,0;0,1] * ([1,1;1,1] + [1,1;1,1])"; //good
    std::string matStr5 = "[1,0;0,1] - [1,1;1,1] + [1,1;1,1]"; //good
    std::string matStr6 = "[1,0;0,1] + [1,1;1,1]*[0,1;1,0]"; //good
    std::string matStr7 = "[1,2;3,4]^-1"; //good
    std::string matStr8 = "[1,2;3,4]^T"; //good
    std::string matStr9 = "[4,4;4,4]/4"; //good
    std::string matStr10 = "[1,2;3,4]^2"; //good
    std::string matStr11 = "[1,2;3,4]^-2"; //good
    std::string matStr12 = "([1,2;3,4]^T)^T"; //good
    std::string matStr13 = "(([1,2,3;4,5,6;7,8,9]) + [1,2,3;4,5,6;7,8,9]) * [1,0,0;0,1,0;0,0,1]"; //Good
    std::string matStr14 = "[4,4,4;4,4,4] / ([1,1,1,1] * [1;1;1;1])"; //good
    std::string matStr15 = "[1;2;3]^T * [1;1;1]"; //good
    
    //Exception Testing
    std::string multiplicationDimensionError = "[1,2;3,4] * [1,0,0;0,1,0;0,0,1]"; //good
    std::string matrixDimensionError = "[1,2,3;1,2]"; //good
    std::string badInputLetters = "[1,2,3;jkflds,2,3]"; //good
    std::string invalidMatrixSyntax = "-[1,2;3,4]"; //good
    
    CalculationUtil::InputLine inLine;
//    std::cout << "Input calculation" << std::endl;
//
//    while(1) {
//        std::string inputLine = "";
//        std::getline(std::cin, inputLine);
//
//        if(inputLine.compare(".") == 0) {break;}
//
//        try {
//            std::istrstream(inputLine.c_str()) >> inLine;
//            std::cout << inLine;
//        }
//        catch(MatrixUtil::InvalidSyntaxException& synError) {
//            std::cerr << synError.what() << std::endl;
//        }
//        catch(MatrixUtil::UnsupportedComputationException& compuError) {
//            std::cerr << compuError.what() << std::endl;
//        }
//        catch(RandomUtils::InvalidCharacterException& charError) {
//            std::cerr << charError.what() << std::endl;
//        }
//    }
//    std::cout << "Goodbye" << std::endl;
    
    try {
        std::istrstream(matStr15.c_str()) >> inLine;
        std::cout << inLine;
    }
    catch(MatrixUtil::InvalidSyntaxException& synError) {
        std::cerr << synError.what() << std::endl;
    }
    catch(MatrixUtil::UnsupportedComputationException& compuError) {
        std::cerr << compuError.what() << std::endl;
    }
    catch(RandomUtils::InvalidCharacterException& charError) {
        std::cerr << charError.what() << std::endl;
    }
          
    return 0;
}
