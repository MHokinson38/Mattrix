//
//  OutputScreen.cpp
//  Mattrix
//
//  Created by Matthew Hokinson on 12/7/19.
//
//Libraries
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>

//My Files
#include <GUIUtil/interface/OutputScreen.h>

//===================
// Constructor
//===================
GUIUtil::OutputScreen::OutputScreen(int xPos, int yPos, int width, int height) {
    background = ofRectangle(xPos, yPos, xPos + width, yPos + height);
}

//===================
// Draw Function
//===================
void GUIUtil::OutputScreen::draw() {
    ofSetColor(255,0,0);
    ofDrawRectangle(100,100,100,100);
}
