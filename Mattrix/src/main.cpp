#include "ofMain.h"
#include "ofApp.h"

//My Files
#include <CalculationUtil/interface/InputLine.h>
#include <MatrixUtil/interface/Exceptions/InvalidSyntaxException.h>
#include <MatrixUtil/interface/Exceptions/UnsupportedComputationException.h>
#include <MatrixUtil/interface/Exceptions/ComputationalLogicException.h>

#include <RandomUtils/interface/InvalidCharacterException.h>

//Libraries
#include <string>
#include <iostream>
#include <strstream>

//========================================================================
int main( ){
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
//    CalculationUtil::InputLine inLine;
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
//            std::cout << inLine << std::endl;
//        }
//        catch(MatrixUtil::InvalidSyntaxException& synError) {
//            std::cerr << synError.what() << std::endl;
//        }
//        catch(MatrixUtil::UnsupportedComputationException& compuError) {
//            std::cerr << compuError.what() << std::endl;
//        }
//        catch(MatrixUtil::ComputationalLogicException& logError) {
//            std::cerr << logError.what() << std::endl;
//        }
//        catch(RandomUtils::InvalidCharacterException& charError) {
//            std::cerr << charError.what() << std::endl;
//        }
//    }
//    std::cout << "Goodbye" << std::endl;
//
//    return 0;
}
