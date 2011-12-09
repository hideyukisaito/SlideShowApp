#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxControlPanel.h"
#include "ofxOsc.h"
#include "ofxHSBasicImage.h"
#include "ofxTimer.h"
#include "LoadingOverlay.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <time.h>

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
    
    void initImages();
    void reload();
    void onReloadCompleted(ofEventArgs&);
    
    void switchThumbnails();
    void tilingThumbnails();
    
    ofxXmlSettings XML;
    
    ofxControlPanel control;
    
    ofxTimer timer;
    void onTimerReached(ofEventArgs &e);
    
    bool bImageInitialized;
    
    std::vector<string> titleImageFileNames;
    int numTitleImages;
    int titleImageIndex;
    ofxHSBasicImage currentImage;
    void onTitleImageFadeOutComplete(ofEventArgs &e);
    
    bool bPersonImagesAvailable;
    int numPersonImages;
    int personImageIndex;
    ofxHSBasicImage titleImage;
    void onFadeOutComplete(ofEventArgs &e);
    
    std::vector<string> fileNames;
    std::vector<ofImage> smallImages;
    std::vector<ofImage> largeImages;
    
    int currentThumbnailIndex;
    int displayMode;
    
    std::vector<int> availableThumbIndexes;
    std::vector<int>::iterator iter;
    
    ofxOscReceiver receiver;
    
    LoadingOverlay overlay;
};
