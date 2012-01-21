#pragma once

#ifndef HSBasicImage_h
#define HSBasicImage_h

#include "ofMain.h"
#include "ofxTween.h"

class ofxHSBasicImage
{
public:
    ofxHSBasicImage();
    ~ofxHSBasicImage();
    
    void load(string filename);
    void load(string filename, int w, int h);
    void setAlpha(int a);
    void setPosition(float x, float y);
    void setFadeDuration(float in, float out);
    void setDelay(float d);
    void draw();
    void draw(float x, float y);
    void fadeIn();
    void fadeOut();
    void clear();
    
    bool isImageLoaded();
    
    ofEvent<ofEventArgs> FADE_IN_COMPLETE;
    ofEvent<ofEventArgs> FADE_OUT_COMPLETE;
    
private:
    void update(ofEventArgs &e);
    void onHideComplete(int &id);
    void onShowComplete(int &id);
    
    ofImage image;
    bool bImageLoaded;
    
    bool bFadeIn;
    bool bFadeOut;
    
    float xpos;
    float ypos;
    int alpha;
    float fadeInDuration;
    float fadeOutDuration;
    
    ofxTween alphaTween;
    ofxTween posTween;
    ofxEasingCirc easingCirc;
    ofxEasingCubic easingCubic;
    ofxEasingQuint easingQuint;
    ofxEasingQuart easingQuart;
    
    float delay;
};

#endif
