//
//  OutputScreen.h
//  Mattrix
//
//  Created by Matthew Hokinson on 12/6/19.
//

#ifndef OutputScreen_h
#define OutputScreen_h

//Libraries
#include <../../openFrameworks/ofMain.h>

#include <string>
#include <iostream>
#include <vector>

//My Files
#include <CalculationUtil/interface/InputLine.h>

namespace GUIUtil {
    class InputOutput {
    public:
        //===============
        // Constructor
        //===============
        InputOutput(const std::string & q, const std::string & ans) : question(q), answer(ans) {}
        
        //===============
        // Getters
        //===============
        std::string getQuestion() {return question;}
        std::string getAnswer() {return answer;}
        
    private:
        //===============
        // Data members
        //===============
        std::string question;
        std::string answer;
    };

    class OutputScreen {
    public:
        //================
        // Constructor
        //================
        OutputScreen(int xPos, int yPos, int width, int height);
        
        //================
        // Basic Getters / Setters
        //================
        void setBackgroundColor(ofColor c) {backgroundColor = c;}
        void setFont(ofTrueTypeFont f) {font = f;}
        
        //================
        // Draw / Update
        //================
        void draw();
        
        //================
        // Add Input
        //================
        void addInput(const std::string & inputLine);
        
        std::string getOutputString(const std::string & inputLine);
        
    private:
        //================
        // Graphics Members
        //================
        ofRectangle backgroundArea;
        
        ofColor backgroundColor;
        ofColor fontColor;
        ofTrueTypeFont font;
        
        //================
        // Data Members
        //================
        std::vector<InputOutput> consoleIOs;
        
        //================
        // Data Processors
        //================
        CalculationUtil::InputLine processor;
    };
}

#endif /* OutputScreen_h */
