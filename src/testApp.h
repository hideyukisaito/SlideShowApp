#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxStateMachine.h"
#include "HSSharedData.h"

#define SCREEN_WIDTH  1200
#define SCREEN_HEIGHT 1920

#define NUM_IMAGES 20
#define NUM_THUMBNAILS    16

#define DISPLAY_MODE_THUMB_SWITCH  1
#define DISPLAY_MODE_THUMB_FIX     2
#define DISPLAY_MODE_REGULAR_SLIDE 3

#define PORT 15002


class testApp : public ofBaseApp
{

public:
    void setup();
    void update();
	void draw();

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
    void exit();
    
    void initStates();
    
    void onMessageReceived(ofxOscMessage &msg);
    
    Apex::ofxStateMachine<HSSharedData> stateMachine;
    
    ofxOscReceiver receiver;
};
