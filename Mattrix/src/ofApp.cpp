#include "ofApp.h"
#include "ofxDatGui.h"

//My Files
#include <GUIUtil/interface/OutputScreen.h>

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowPosition(0, 0);

    //Create Options Menu
    for(std::map<std::string, CalculationUtil::InputLine::Mode>::iterator it = nameModeMap.begin();
        it != nameModeMap.end(); ++it) {
        menuOptions.push_back(it->first);
    }

    // instantiate the dropdown
        menu = new ofxDatGuiDropdown("SELECT MODE", menuOptions);
        
    // Put it to the side of the screen
        menu->setPosition(0, menu->getHeight());
        menu->setWidth(ofGetWidth() * .25);
        
    // Set the stripe colors
        for (int i=0; i<menu->size(); i++) menu->getChildAt(i)->setStripeColor(0xFFFFFF);

    // register to listen for change events //
        menu->onDropdownEvent(this, &ofApp::onDropdownEvent);
        
    // finally let's have it open by default //
        menu->expand();
    
    //=================
    inputLine = new ofxDatGuiTextInput("Expression Input", "Enter Text Here");
    inputLine->setWidth(ofGetWidth(), .25);
    inputLine->setPosition(ofGetWidth() - inputLine->getWidth(), ofGetHeight() - inputLine->getHeight());
    
    inputLine->onTextInputEvent(this, &ofApp::onTextInputEvent);
    
    titleBar = new ofxDatGuiLabel("Mattrix: A Matrix Calculator by Matt");
    titleBar->setWidth(ofGetWidth());
    
    console = new GUIUtil::OutputScreen(menu->getWidth(), titleBar->getHeight(), ofGetWidth() - menu->getWidth(), ofGetHeight() - 3*inputLine->getHeight(), CONSOLE_SAVE_FILE_PATH);
    
    font.load("ofxbraitsch/fonts/Verdana.ttf", 12);
    console->setFont(font);
}

//--------------------------------------------------------------
void ofApp::update(){
    menu->update();
    inputLine->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    menu->draw();
    inputLine->draw();
    
    titleBar->draw();
    console->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//---------------------------------------------------------------
//TODO delete this later when I am not using it anymore
std::string ofApp::getHex(int hex)
{
// convert decimal value to hex //
    std::stringstream ss;
    ss<< std::hex << hex;
    std::string res ( ss.str() );
    while(res.size() < 6) res+="0";
    return "#"+ofToUpper(res);
}

void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
    switch(nameModeMap.at(menuOptions[e.child])) {
        case CalculationUtil::InputLine::Mode::EXPRESSION:
            console->expressionMode();
            break;
        case CalculationUtil::InputLine::Mode::EQUATION:
            console->equationMode();
            break;
        case CalculationUtil::InputLine::Mode::APPROXEQUATION:
            console->approxMode();
            break;
        case CalculationUtil::InputLine::Mode::DETERMINANT:
            console->determinantMode();
            break;
    }
    
    //Recreate the Input line with the correct label
    inputLine = new ofxDatGuiTextInput(menuOptions[e.child], "Enter Text Here");
    inputLine->setWidth(ofGetWidth(), .25);
    inputLine->setPosition(ofGetWidth() - inputLine->getWidth(), ofGetHeight() - inputLine->getHeight());
    
    inputLine->onTextInputEvent(this, &ofApp::onTextInputEvent);
}

void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent e)
{
// text input events carry the text of the input field //
//    std::cout << "From Event Object: " << e.text << std::endl;
// although you can also retrieve it from the event target //
//    std::cout << "From Event Target: " << e.target->getText() << std::endl;
    
    console->addInput(e.text);
    
    inputLine->setText("");
}

