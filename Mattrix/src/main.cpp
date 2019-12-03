#include "ofMain.h"
#include "ofApp.h"

//My Files
#include <CalculationUtil/interface/InputLine.h>

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

    
    CalculationUtil::InputLine inLine;
    
    std::istrstream(matStr7.c_str()) >> inLine;
    
    std::cout << inLine;
}
