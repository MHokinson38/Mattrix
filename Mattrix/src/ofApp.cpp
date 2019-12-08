#include "ofApp.h"
#include "ofxDatGui.h"

//My Files
#include <GUIUtil/interface/OutputScreen.h>

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowPosition(0, 0);

    // create a vector of colors to populate our dropdown //
        colors.push_back(ofColor::fromHex(0xFFD00B));
        colors.push_back(ofColor::fromHex(0x2FA1D6));
        colors.push_back(ofColor::fromHex(0x1ED36F));
        colors.push_back(ofColor::fromHex(0xC63256));
        
    // convert the hex values of those colors to strings for the menu labels //
        vector<string> options;
        for (int i=0; i<colors.size(); i++) options.push_back(getHex(colors[i].getHex()));

    // instantiate the dropdown //
        menu = new ofxDatGuiDropdown("SELECT A COLOR", options);
        
    // and position it in the middle of the screen //
        menu->setPosition(0, menu->getHeight());
        
    // let's set the stripe of each option to its respective color //
        for (int i=0; i<menu->size(); i++) menu->getChildAt(i)->setStripeColor(colors[i]);

    // register to listen for change events //
        menu->onDropdownEvent(this, &ofApp::onDropdownEvent);
        
    // finally let's have it open by default //
        menu->expand();
    
    //=================
    inputLine = new ofxDatGuiTextInput("Expression Input", "Enter Text Here");
    inputLine->setWidth(ofGetWidth(), .25);
    inputLine->setPosition(ofGetWidth() - inputLine->getWidth(), ofGetHeight() - inputLine->getHeight());
    
    inputLine->onTextInputEvent(this, &ofApp::onTextInputEvent);
    
    textOutput = new ofxDatGuiLabel("No Text Entered Yet");
    textOutput->setWidth(ofGetWidth());
    
    font.load("ofxbraitsch/fonts/Verdana.ttf", 24);
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
    
    textOutput->draw();
    
    GUIUtil::OutputScreen* output = new GUIUtil::OutputScreen(1,1,1,1);
    output->draw();
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
    ofSetBackgroundColor(colors[e.child]);
    menu->setStripeColor(ofColor::white);
}

void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent e)
{
// text input events carry the text of the input field //
    std::cout << "From Event Object: " << e.text << std::endl;
// although you can also retrieve it from the event target //
    std::cout << "From Event Target: " << e.target->getText() << std::endl;
    
    string output = "Text input: " + e.text;
    textOutput = new ofxDatGuiLabel(output);
    textOutput->setWidth(ofGetWidth());
    textOutput->draw();
    
    inputLine->setText("");
    
//    std::string str = "Text Input: " + e.target->getText();
//    ofSetColor(ofColor::blue);
//    ofRectangle bounds = font.getStringBoundingBox(str, ofGetWidth()/2, ofGetHeight()/4);
//    font.drawString(str, bounds.x-bounds.width/2, bounds.y-bounds.height/2);
}

