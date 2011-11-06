#pragma once

#include "ofMain.h"

#include <iostream>
#include <sstream>
#include <vector>

#define SCREEN_WIDTH  1200
#define SCREEN_HEIGHT 1920
#define NUM_IMAGES    16

// #define ENV_RELAESE // uncomment this when release

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
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
    
    std::vector<ofImage> smallImages;
    std::vector<ofImage> largeImages;
    
    int currentImageIndex;
};
