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
#include <strstream>

//My Files
#include <GUIUtil/interface/OutputScreen.h>

#include <MatrixUtil/interface/Exceptions/InvalidSyntaxException.h>
#include <MatrixUtil/interface/Exceptions/UnsupportedComputationException.h>
#include <MatrixUtil/interface/Exceptions/ComputationalLogicException.h>
#include <RandomUtils/interface/InvalidCharacterException.h>


//===================
// Constructor
//===================
GUIUtil::OutputScreen::OutputScreen(int xPos, int yPos, int width, int height) {
    //Position is
    backgroundArea = ofRectangle(xPos, yPos, xPos + width, yPos + height);
    backgroundColor = ofColor(178, 178, 178);
    fontColor = backgroundColor;
    fontColor.invert();
}

//===================
// Draw Function
//===================
void GUIUtil::OutputScreen::draw() {
    //Draw the background
    ofSetColor(backgroundColor);
    ofDrawRectangle(backgroundArea.getX(), backgroundArea.getY(),
                    backgroundArea.getWidth(), backgroundArea.getHeight());
    
    //Draw the Text output
    ofSetColor(fontColor);
    int currentLine = 0;
    for(int i = consoleIOs.size() - 1; i >= 0; --i) { //Newest are kept in the back
        //Check for bounds
        if(currentLine * LINE_SPACING > backgroundArea.getHeight()) {break;}
        
        std::string answer = consoleIOs[i].getAnswer();
        currentLine += fitLineToScreen(answer);
        //Draw the answer centered to the right
        font.drawString(answer,
                        backgroundArea.getX() + backgroundArea.getWidth() / 4,
                        backgroundArea.getY() + backgroundArea.getHeight() -
                        (currentLine) * LINE_SPACING - BORDER_PADDING);
        
        std::string question = consoleIOs[i].getQuestion();
        currentLine += fitLineToScreen(question) + 1;
        //Draw the question centered to the left
        font.drawString(question,
                        backgroundArea.getX() + 10,
                        backgroundArea.getY() + backgroundArea.getHeight() -
                        currentLine * LINE_SPACING - BORDER_PADDING);
        
        currentLine++;
    }
}

//=====================
// Line Padding
//=====================
int GUIUtil::OutputScreen::fitLineToScreen(std::string& input) {
    std::string fittedString = "";
    int numLines = 0;
    
    for(int i = 0; i < input.size(); ++i) {
        if((i % OUTPUT_CONSOLE_LINE_LENGTH) == 0 && i != 0) {
            fittedString += "\n";
            numLines++;
        }
        fittedString += input[i];
    }
    
    input = fittedString;
    return numLines;
}

//=====================
// Add Function
//=====================
void GUIUtil::OutputScreen::addInput(const std::string &inputLine) {
    //Ignore any null/blank inputs
    if(inputLine.compare("") == 0) {return;}
    
    //Find the output string
    std::string output = getOutputString(inputLine);
    
    consoleIOs.push_back(InputOutput(inputLine, output));
}

std::string GUIUtil::OutputScreen::getOutputString(const std::string & inputLine) {
    try {
        std::istrstream(inputLine.c_str()) >> processor;
        return processor.getOutputMatrixString();
    }
    catch(MatrixUtil::InvalidSyntaxException& synError) {
        return synError.what();
    }
    catch(MatrixUtil::UnsupportedComputationException& compuError) {
        return compuError.what();
    }
    catch(MatrixUtil::ComputationalLogicException& logError) {
        return logError.what();
    }
    catch(RandomUtils::InvalidCharacterException& charError) {
        return charError.what();
    }
    catch(...) {
        return "Something has gone terribly wrong!";
    }
}
