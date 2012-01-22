#include "testApp.h"
//#include "ofxState.h"
#include "TitleImagesState.h"
#include "PersonImagesState.h"
#include "GlassImagesState.h"
#include "LoadingState.h"

//--------------------------------------------------------------
void testApp::setup()
{
    ofBackground(255);
    ofEnableSmoothing();
    ofSetFrameRate(60);
    ofEnableSmoothing();
    
    receiver.setup(PORT);
    ofAddListener(receiver.onMessageReceived, this, &testApp::onMessageReceived);
    
    initStates();
}

//--------------------------------------------------------------
void testApp::initStates()
{
    stateMachine.addState(new TitleImagesState());
    stateMachine.addState(new PersonImagesState());
    stateMachine.addState(new GlassImagesState());
    stateMachine.addState(new LoadingState());
    stateMachine.changeState("title");
}

//--------------------------------------------------------------
void testApp::onMessageReceived(ofxOscMessage &msg)
{
    stateMachine.changeState("loading");
    cout << "message received : " << msg.getArgAsString(0) << endl;
}

//--------------------------------------------------------------
void testApp::update()
{
}

//--------------------------------------------------------------
void testApp::draw()
{
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::exit()
{
    cout << "BYE!" << endl;
}