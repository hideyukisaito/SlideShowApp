#include "ofxHSBasicMovie.h"

//--------------------------------------------------------------
ofxHSBasicMovie::ofxHSBasicMovie()
{
    bMovieLoaded = bFadeIn = bFadeOut = bPlaying = false;
    xpos = 0;
    ypos = 0;
    alpha = 0;
    delay = 0;
    bNotifiedEvent = false;
    fadeInDuration = fadeInDuration = 1500;
    
    ofAddListener(ofEvents.update, this, &ofxHSBasicMovie::update);
}

//--------------------------------------------------------------
ofxHSBasicMovie::~ofxHSBasicMovie()
{
    ofRemoveListener(ofEvents.update, this, &ofxHSBasicMovie::update);
    movie.close();
}

//--------------------------------------------------------------
bool ofxHSBasicMovie::load(const string filename)
{
    //bMovieLoaded = movie.loadMovie(filename);
    bMovieLoaded = movie.loadMovie(ofToDataPath("1.mov"));
    return bMovieLoaded;
}

//--------------------------------------------------------------
void ofxHSBasicMovie::close()
{
    movie.close();
}

//--------------------------------------------------------------
void ofxHSBasicMovie::setAlpha(int a)
{
    alpha = a;
}

//--------------------------------------------------------------
bool ofxHSBasicMovie::isMovieLoaded()
{
    return bMovieLoaded;
}

//--------------------------------------------------------------
void ofxHSBasicMovie::setPosition(float x, float y)
{
    xpos = x;
    ypos = y;
}

//--------------------------------------------------------------
void ofxHSBasicMovie::setFadeDuration(float in, float out)
{
    fadeInDuration = in;
    fadeOutDuration = out;
}

//--------------------------------------------------------------
void ofxHSBasicMovie::setDelay(float d)
{
    delay = d;
}

//--------------------------------------------------------------
void ofxHSBasicMovie::setLoopState(ofLoopType state)
{
    movie.setLoopState(state);
}

//--------------------------------------------------------------
void ofxHSBasicMovie::update(ofEventArgs &e)
{
    alpha = alphaTween.update();
    cout << "movie alpha = " << alpha << endl;
    if (!bNotifiedEvent && !movie.isPlaying())
    {
        static ofEventArgs eventArgs;
        ofNotifyEvent(PLAY_COMPLETE, eventArgs, this);
        bNotifiedEvent = true;
    }
}

//--------------------------------------------------------------
void ofxHSBasicMovie::draw()
{
    ofPushStyle();
        ofSetupScreen();
        ofEnableAlphaBlending();
        
        ofSetColor(255, 255, 255, 255 - alpha);
        ofRect(0, 0, movie.width, movie.height);
        
        ofSetColor(255);
        movie.draw(xpos, ypos);
        ofDisableAlphaBlending();
    ofPopStyle();
}

//--------------------------------------------------------------
void ofxHSBasicMovie::draw(float x, float y, float w, float h)
{
    xpos = x;
    ypos = y;
    
//    ofPushStyle();
//        ofSetupScreen();
//        ofEnableAlphaBlending();
//        
//        ofSetColor(255, 255, 255, 255 - alpha);
//        ofRect(x, y, w, h);
//        
//        ofSetColor(255, 255, 255, 255);
//        movie.draw(xpos, ypos, w, h);
//        ofDisableAlphaBlending();
//    ofPopStyle();
    
    ofPushStyle();
        ofSetupScreen();
        ofEnableAlphaBlending();
        
        ofSetColor(255, 255, 255, 255);
        movie.draw(xpos, ypos, w, h);
        ofDisableAlphaBlending();
    ofPopStyle();
}

//--------------------------------------------------------------
void ofxHSBasicMovie::fadeIn()
{
    cout << "========== FADE IN ==========" << endl;
    bFadeIn = true;
    bFadeOut = !bFadeIn;
    
    if (!hasUpdateListener)
    {
        ofAddListener(ofEvents.update, this, &ofxHSBasicMovie::update);
        hasUpdateListener = true;
        bNotifiedEvent = false;
    }
    
    ofAddListener(alphaTween.end_E, this, &ofxHSBasicMovie::onShowComplete);
    alphaTween.setParameters(1, easingQuart, ofxTween::easeOut, alpha, 255, 1000, delay);
    posTween.setParameters(2, easingCirc, ofxTween::easeOut, ofGetWidth(), 0, fadeInDuration, delay);
}

//--------------------------------------------------------------
void ofxHSBasicMovie::fadeOut()
{
    //alpha = 255;
    bFadeOut = true;
    bFadeIn = !bFadeOut;
    
    if (!hasUpdateListener)
    {
        ofAddListener(ofEvents.update, this, &ofxHSBasicMovie::update);
        hasUpdateListener = true;
        bNotifiedEvent = false;
    }
    
    ofAddListener(alphaTween.end_E, this, &ofxHSBasicMovie::onHideComplete);
    alphaTween.setParameters(1, easingCirc, ofxTween::easeOut, alpha, 0, 1000, delay);
    posTween.setParameters(2, easingQuint, ofxTween::easeOut, 0, -ofGetWidth(), fadeOutDuration, delay);
}

//--------------------------------------------------------------
void ofxHSBasicMovie::idleMovie()
{
    movie.idleMovie();
}

//--------------------------------------------------------------
void ofxHSBasicMovie::onShowComplete(int &id)
{
    if (!hasUpdateListener)
    {
        ofAddListener(ofEvents.update, this, &ofxHSBasicMovie::update);
        hasUpdateListener = true;
        bNotifiedEvent = false;
    }
    
    if (movie.isLoaded()) movie.play();
    static ofEventArgs eventArgs;
    ofNotifyEvent(FADE_IN_COMPLETE, eventArgs, this);
}

//--------------------------------------------------------------
void ofxHSBasicMovie::onHideComplete(int &id)
{
    if (hasUpdateListener)
    {
        ofAddListener(ofEvents.update, this, &ofxHSBasicMovie::update);
        hasUpdateListener = false;
    }
    
    if (movie.isLoaded()) movie.stop();
    static ofEventArgs eventArgs;
    ofNotifyEvent(FADE_OUT_COMPLETE, eventArgs, this);
}
