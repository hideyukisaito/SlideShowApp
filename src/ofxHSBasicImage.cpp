#include "ofxHSBasicImage.h"

//--------------------------------------------------------------
ofxHSBasicImage::ofxHSBasicImage()
{
    bImageLoaded = bFadeIn = bFadeOut = false;
    xpos = 0;
    ypos = 0;
    alpha = 0;
    delay = 0;
    fadeInDuration = fadeInDuration = 1500;
    
    ofAddListener(ofEvents.update, this, &ofxHSBasicImage::update);
}

//--------------------------------------------------------------
ofxHSBasicImage::~ofxHSBasicImage()
{
    ofRemoveListener(ofEvents.update, this, &ofxHSBasicImage::update);
    image.clear();
}

//--------------------------------------------------------------
void ofxHSBasicImage::load(string filename)
{
    bImageLoaded = image.loadImage(filename);
    image.setImageType(OF_IMAGE_COLOR_ALPHA);
}

//--------------------------------------------------------------
void ofxHSBasicImage::clear()
{
    image.clear();
}

//--------------------------------------------------------------
void ofxHSBasicImage::load(string filename, int w, int h)
{
    bImageLoaded = image.loadImage(filename);
    image.setImageType(OF_IMAGE_COLOR_ALPHA);  
    image.resize(w, h);
}

//--------------------------------------------------------------
void ofxHSBasicImage::setAlpha(int a)
{
    alpha = a;
}

//--------------------------------------------------------------
bool ofxHSBasicImage::isImageLoaded()
{
    return bImageLoaded;
}

//--------------------------------------------------------------
void ofxHSBasicImage::setPosition(float x, float y)
{
    xpos = x;
    ypos = y;
}

//--------------------------------------------------------------
void ofxHSBasicImage::setFadeDuration(float in, float out)
{
    fadeInDuration = in;
    fadeOutDuration = out;
}

//--------------------------------------------------------------
void ofxHSBasicImage::setDelay(float d)
{
    delay = d;
}

//--------------------------------------------------------------
void ofxHSBasicImage::update(ofEventArgs &e)
{
    alpha = alphaTween.update();
}

//--------------------------------------------------------------
void ofxHSBasicImage::draw()
{
    ofPushStyle();
        ofSetupScreen();
        ofEnableAlphaBlending();
        ofSetColor(255, 255, 255, alpha);
        image.draw(xpos, ypos);
        ofDisableAlphaBlending();
    ofPopStyle();
}

//--------------------------------------------------------------
void ofxHSBasicImage::draw(float x, float y)
{
    xpos = x;
    ypos = y;
    
    ofPushStyle();
        ofSetupScreen();
        ofEnableAlphaBlending();
        ofSetColor(255, 255, 255, alpha);
        image.draw(xpos, ypos);
        ofDisableAlphaBlending();
    ofPopStyle();
}

//--------------------------------------------------------------
void ofxHSBasicImage::fadeIn()
{
    bFadeIn = true;
    bFadeOut = !bFadeIn;

    ofAddListener(alphaTween.end_E, this, &ofxHSBasicImage::onShowComplete);
    alphaTween.setParameters(1, easingQuart, ofxTween::easeOut, alpha, 255, 1000, delay);
    posTween.setParameters(2, easingCirc, ofxTween::easeOut, ofGetWidth(), 0, fadeInDuration, delay);
}

//--------------------------------------------------------------
void ofxHSBasicImage::fadeOut()
{
    //alpha = 255;
    bFadeOut = true;
    bFadeIn = !bFadeOut;
    
    ofAddListener(alphaTween.end_E, this, &ofxHSBasicImage::onHideComplete);
    alphaTween.setParameters(1, easingCirc, ofxTween::easeOut, alpha, 0, 1000, delay);
    posTween.setParameters(2, easingQuint, ofxTween::easeOut, 0, -ofGetWidth(), fadeOutDuration, delay);
}

//--------------------------------------------------------------
void ofxHSBasicImage::onShowComplete(int &id)
{
    static ofEventArgs eventArgs;
    ofNotifyEvent(FADE_IN_COMPLETE, eventArgs, this);
}

//--------------------------------------------------------------
void ofxHSBasicImage::onHideComplete(int &id)
{
    static ofEventArgs eventArgs;
    ofNotifyEvent(FADE_OUT_COMPLETE, eventArgs, this);
}
