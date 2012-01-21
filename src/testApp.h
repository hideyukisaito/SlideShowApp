#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxControlPanel.h"
#include "ofxOsc.h"
#include "ofxHSBasicImage.h"
#include "ofxHSBasicMovie.h"
#include "ofxTimer.h"
#include "LoadingOverlay.h"
#include "ofxTween.h"

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
    void exit();
    
    void initImages();
    void reload();
    void onReloadCompleted(ofEventArgs&);
    
    void switchThumbnails();
    void tilingThumbnails();
    bool isKeyIndex(int index);
    
    void onTitleImageFadeOutComplete(ofEventArgs &e);
    void onImageFadeOutComplete(ofEventArgs &e);
    void onMovieFadeOutComplete(int &id);
    
    ofxXmlSettings XML;
    
    ofxControlPanel control;
    
    ofxTimer timer;
    void onTimerReached(ofEventArgs &e);
    
    bool bImageInitialized;
    bool bShowMovie;
    bool bSkipCheckingIndex;
    
    vector<string> titleImageFileNames;
    int numTitleImages;
    int titleImageIndex;
    ofxHSBasicImage titleImage;
    
    bool bPersonImagesAvailable;
    int numPersonImages;
    int personImageIndex;
    ofxHSBasicImage currentImage;
    
    vector<string> fileNames;
    vector<ofImage> smallImages;
    vector<ofImage> largeImages;
    vector<int> movieKeyIndexes;
    
    vector<ofVideoPlayer> movies;
    vector<string> movieFileNames;
    int numMovieFiles;
    int movieIndex;
    bool bMoviePlayed;
    ofVideoPlayer currentMovie;
    
    int currentThumbnailIndex;
    int displayMode;
    
    vector<int> availableThumbIndexes;
    vector<int>::iterator iter;
    
    ofxOscReceiver receiver;
    
    LoadingOverlay overlay;
    
    int movieAlpha;
    ofxTween movieAlphaTween;
    ofxEasingCirc easingCirc;
};
