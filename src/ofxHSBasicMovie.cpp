#include "ofxHSBasicMovie.h"

//--------------------------------------------------------------
ofxHSBasicMovie::ofxHSBasicMovie()
{
    bMovieLoaded = bFadeIn = bFadeOut = bPlaying = false;
    xpos = 0;
    ypos = 0;
    alpha = 0;
    delay = 0;
    bNotifiedEvent = bInitialized = false;
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
bool ofxHSBasicMovie::loadMovie(const string name)
{
    filename = name;
    //bMovieLoaded = movie.loadMovie(filename);
    bMovieLoaded = movie.loadMovie(filename);
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
void ofxHSBasicMovie::play()
{
    
}

//--------------------------------------------------------------
void ofxHSBasicMovie::update(ofEventArgs &e)
{
    if (!bInitialized) 
    {
        movie.loadMovie(filename);
        if (movie.isLoaded())
        {
            bInitialized = true;
        }
    }
    
    if (bInitialized && !movie.isPlaying()) movie.play();
    cout << "movie.isLoaded : " << movie.isLoaded() << endl;
    if (movie.isLoaded() && movie.isPlaying()) movie.idleMovie();
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
    
    if (movie.isLoaded())
    {
        ofPushStyle();
        ofEnableAlphaBlending();
        ofSetColor(255, 255, 255, 255);
        movie.draw(xpos, ypos, w, h);
        ofDisableAlphaBlending();
        ofPopStyle();
    }
}

//--------------------------------------------------------------
void ofxHSBasicMovie::fadeIn()
{
    ofAddListener(alphaTween.end_E, this, &ofxHSBasicMovie::onShowComplete);
    alphaTween.setParameters(100, easingQuart, ofxTween::easeOut, 0, 255, 1000, delay);
}

//--------------------------------------------------------------
void ofxHSBasicMovie::fadeOut()
{
    ofAddListener(alphaTween.end_E, this, &ofxHSBasicMovie::onHideComplete);
    alphaTween.setParameters(101, easingCirc, ofxTween::easeOut, 255, 0, 1000, delay);
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
    
    static ofEventArgs eventArgs;
    ofNotifyEvent(FADE_IN_COMPLETE, eventArgs, this);
}

//--------------------------------------------------------------
void ofxHSBasicMovie::onHideComplete(int &id)
{
    if (hasUpdateListener)
    {
        ofRemoveListener(ofEvents.update, this, &ofxHSBasicMovie::update);
        hasUpdateListener = false;
    }
    
    static ofEventArgs eventArgs;
    ofNotifyEvent(FADE_OUT_COMPLETE, eventArgs, this);
}
