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
}
