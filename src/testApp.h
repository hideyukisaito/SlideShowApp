#pragma once

#include "ofMain.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <time.h>

#define SCREEN_WIDTH  1200
#define SCREEN_HEIGHT 1920

#define NUM_THUMBNAILS    16

#define DISPLAY_MODE_THUMB_SWITCH  1
#define DISPLAY_MODE_THUMB_FIX     2
#define DISPLAY_MODE_REGULAR_SLIDE 3

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
    
    void switchThumbnails();
    void tilingThumbnails();
    
    std::vector<ofImage> smallImages;
    std::vector<ofImage> largeImages;
    
    int currentThumbnailIndex;
    int displayMode;
    
    std::vector<int> availableThumbIndexes;
    std::vector<int>::iterator iter;
    
    int drawCount;
};
