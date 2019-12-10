#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

//My Files
#include <GUIUtil/interface/OutputScreen.h>
#include <MatrixUtil/interface/Matrix.h>

class ofApp : public ofBaseApp {

	public:
        //====================
        // COnstants
        //=====================
        inline static const std::string CONSOLE_SAVE_FILE_PATH = "ConsoleOutput.txt";
    
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    private:
    
        string getHex(int hex);
        
        std::map<std::string, CalculationUtil::InputLine::Mode> nameModeMap = {
            {"Expression Mode", CalculationUtil::InputLine::Mode::EXPRESSION},
            {"Equation Mode", CalculationUtil::InputLine::Mode::EQUATION},
            {"Approx Equation Mode", CalculationUtil::InputLine::Mode::APPROXEQUATION},
            {"Determinant Mode", CalculationUtil::InputLine::Mode::DETERMINANT}};
    
        ofxDatGuiDropdown* menu;
        std::vector<std::string> menuOptions;
        void onDropdownEvent(ofxDatGuiDropdownEvent e);
    
        ofxDatGuiTextInput* inputLine;
        void onTextInputEvent(ofxDatGuiTextInputEvent e);
    
        ofxDatGuiLabel* titleBar;
    
        GUIUtil::OutputScreen* console;
    
        ofTrueTypeFont font;
		//This is a test
};
