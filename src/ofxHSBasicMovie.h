#pragma once

#ifndef HSBasicMovie_h
#define HSBasicMovie_h

#include "ofMain.h"
#include "ofxTween.h"

class ofxHSBasicMovie
{
public:
    ofxHSBasicMovie();
    ~ofxHSBasicMovie();
    
    bool loadMovie(const string name);
    void setAlpha(int a);
    void setPosition(float x, float y);
    void setFadeDuration(float in, float out);
    void setDelay(float d);
    void setLoopState(ofLoopType state);
    void play();
    void draw();
    void draw(float x, float y, float w, float h);
    void fadeIn();
    void fadeOut();
    void idleMovie();
    void close();
    
    bool isMovieLoaded();
    
    ofEvent<ofEventArgs> FADE_IN_COMPLETE;
    ofEvent<ofEventArgs> FADE_OUT_COMPLETE;
    ofEvent<ofEventArgs> PLAY_COMPLETE;
    
private:
    void update(ofEventArgs &e);
    void onHideComplete(int &id);
    void onShowComplete(int &id);
    
    ofVideoPlayer movie;
    ofImage canvas;
    bool bMovieLoaded;
    
    bool hasUpdateListener;
    bool bFadeIn;
    bool bFadeOut;
    bool bPlaying;
    bool bNotifiedEvent;
    bool bInitialized;
    
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
    
    string filename;
};

#endif
