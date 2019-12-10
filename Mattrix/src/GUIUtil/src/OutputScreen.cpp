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
#include <fstream>

//My Files
#include <GUIUtil/interface/OutputScreen.h>

#include <MatrixUtil/interface/Exceptions/InvalidSyntaxException.h>
#include <MatrixUtil/interface/Exceptions/UnsupportedComputationException.h>
#include <MatrixUtil/interface/Exceptions/ComputationalLogicException.h>
#include <RandomUtils/interface/InvalidCharacterException.h>


//===================
// Constructor
//===================
GUIUtil::OutputScreen::OutputScreen(int xPos, int yPos, int width, int height, std::string saveFilePath) :
outputFilePath(saveFilePath)
{
    //Positioning and color
    backgroundArea = ofRectangle(xPos, yPos, xPos + width, yPos + height);
    backgroundColor = ofColor(178, 178, 178);
    fontColor = backgroundColor;
    fontColor.invert();
    
    //Read the save (if there is one)
    readSave();
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
    for(int i = 0; i < consoleIOs.size(); ++i) {
        std::string answer = consoleIOs[i].getAnswer();
        currentLine += fitLineToScreen(answer);
        
        //Check for bounds
        if(((currentLine * LINE_SPACING) + BORDER_PADDING) >
           (backgroundArea.getHeight() - BORDER_PADDING)) {break;}
        //Draw the answer centered to the right
        font.drawString(answer,
                        backgroundArea.getX() + backgroundArea.getWidth() / 4,
                        backgroundArea.getY() + backgroundArea.getHeight() -
                        (currentLine) * LINE_SPACING - BORDER_PADDING);
        
        std::string question = consoleIOs[i].getQuestion();
        currentLine += fitLineToScreen(question) + 1;
        
        //Check for bounds
        if(((currentLine * LINE_SPACING) + BORDER_PADDING) >
           (backgroundArea.getHeight() - BORDER_PADDING)) {break;}
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
    
    consoleIOs.insert(consoleIOs.begin(), InputOutput(inputLine, output));
    if(consoleIOs.size() >= MAX_OUTPUT_COUNT) {
        consoleIOs.pop_back();
    }
    
    writeSave();
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

//==================
// Reading/Writing
//==================
void GUIUtil::OutputScreen::writeSave() {
    std::ofstream saveFile(outputFilePath);
    
    for(auto& outputPair : consoleIOs) {
        saveFile << outputPair;
    }
}

void GUIUtil::OutputScreen::readSave() {
    std::ifstream saveFile(outputFilePath);
    consoleIOs.clear();
    
    while(saveFile) {
        InputOutput nextIO;
        saveFile >> nextIO;
        
        consoleIOs.push_back(nextIO);
        
        if(saveFile.eof()) {break;}
    }
}

//=====================
// InputOutput IOs
//=====================
std::ostream& GUIUtil::operator<<(std::ostream& os, const InputOutput& io) {
    return os << io.question << std::endl << io.answer << std::endl;
}

std::istream& GUIUtil::operator>>(std::istream& is, InputOutput& io) {
    std::string currentLine = "";
    //Get the question
    std::getline(is, currentLine);
    io.question = currentLine;
    
    //Get the answer
    std::getline(is, currentLine);
    io.answer = currentLine;
    
    return is;
}
