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
        InputOutput() = default;
        InputOutput(const std::string & q, const std::string & ans) : question(q), answer(ans) {}
        
        //===============
        // Getters
        //===============
        std::string getQuestion() {return question;}
        std::string getAnswer() {return answer;}
        
        //===============
        // Stream overloads for saving
        //================
        friend std::ostream& operator<<(std::ostream& os, const InputOutput& io);
        friend std::istream& operator>>(std::istream& is, InputOutput& io);
        
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
        //Constants
        //================
        inline static const int OUTPUT_CONSOLE_LINE_LENGTH = 55;
        inline static const int BORDER_PADDING = 20; //Pixels
        inline static const int LINE_SPACING = 30; //Pixels
        
        inline static const int MAX_OUTPUT_COUNT = 12;
        
        //================
        // Constructor
        //================
        OutputScreen(int xPos, int yPos, int width, int height, std::string saveFilePath);
        
        //================
        // Basic Getters / Setters
        //================
        void setBackgroundColor(ofColor c) {backgroundColor = c;}
        void setFont(ofTrueTypeFont f) {font = f;}
        
        //================
        // For Mode Updates
        //================
        void expressionMode() {processor.expressionMode();}
        void equationMode() {processor.equationMode();}
        void determinantMode() {processor.determinantMode();}
        void approxMode() {processor.approxMode();}
        
        //================
        // Draw / Update
        //================
        void draw();
        
        //================
        // Add Input
        //================
        void addInput(const std::string & inputLine);
        
        std::string getOutputString(const std::string & inputLine);
        
        //================
        // Reading/Writing Saves
        //================
        void writeSave();
        void readSave();
        
    private:
        //================
        // Line Padding
        //================
        int fitLineToScreen(std::string & input);
        
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
        
        std::string outputFilePath;
        //================
        // Data Processors
        //================
        CalculationUtil::InputLine processor;
    };
}

#endif /* OutputScreen_h */
