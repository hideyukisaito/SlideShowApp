//
//  ofxAjaxLoadingCircle.cpp
//  SlideShowApp
//
//  Created by Hideyuki Saito on 11/12/10.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "ofxAjaxLoadingCircle.h"

ofxAjaxLoadingCircle::ofxAjaxLoadingCircle()
{
    ofSetCircleResolution(128);
    
    devides = 12;
    step = TWO_PI / devides;
    angle = 0;
    alpha = 0;
    bFadeIn = false;
    backgroundColor.set(215, 215, 215);
    foregroundColor.set(150, 150, 150);
    
    ofAddListener(ofEvents.update, this, &ofxAjaxLoadingCircle::update);
}

ofxAjaxLoadingCircle::~ofxAjaxLoadingCircle()
{
    ofRemoveListener(ofEvents.update, this, &ofxAjaxLoadingCircle::update);
}

void ofxAjaxLoadingCircle::setup(float w, float h)
{
    width = w;
    height = h;
}

void ofxAjaxLoadingCircle::setBackgroundColor(int r, int g, int b)
{
    backgroundColor.set(r, g, b);
}

void ofxAjaxLoadingCircle::setBackgroundColor(ofColor col)
{
    backgroundColor = col;
}

void ofxAjaxLoadingCircle::setForegroundColor(int r, int g, int b)
{
    foregroundColor.set(r, g, b);
}

void ofxAjaxLoadingCircle::setForegroundColor(ofColor col)
{
    foregroundColor = col;
}

void ofxAjaxLoadingCircle::toggleFade()
{
    bFadeIn = !bFadeIn;
    if (bFadeIn)
    {
        alphaTween.setParameters(1, easingLinear, ofxTween::easeOut, alpha, 255, 1000, 0);
    }
    else
    {
        alphaTween.setParameters(1, easingLinear, ofxTween::easeOut, alpha, 0, 1000, 0);
    }
}

void ofxAjaxLoadingCircle::show()
{
    bFadeIn = true;
    alphaTween.setParameters(1, easingLinear, ofxTween::easeOut, alpha, 255, 1000, 0);
}

void ofxAjaxLoadingCircle::hide()
{
    bFadeIn = false;
    alphaTween.setParameters(1, easingLinear, ofxTween::easeOut, alpha, 0, 1000, 0);
}

void ofxAjaxLoadingCircle::update(ofEventArgs &e)
{
    if (ofGetFrameNum() % (int)(ofGetFrameRate() / 16) == 0)
    {
        angle = TWO_PI > angle ? angle + step : step;
    }
}

void ofxAjaxLoadingCircle::draw(float x, float y)
{
    centerX = x + width * 0.5;
    centerY = y + height * 0.5;
    alpha = alphaTween.update();
    
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofPushStyle();
        ofSetColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, alpha);
        ofFill();
        float bgAngle = TWO_PI / devides;
        for (int i = 0; i < devides; i++)
        {
            ofCircle(centerX + (cos(bgAngle + step * i) * (width * 0.5)), centerY + (sin(bgAngle + step * i) * (height * 0.5)), 10);
        }
    ofPopStyle();
    
    ofPushStyle();
        ofSetColor(foregroundColor.r, foregroundColor.g, foregroundColor.b, alpha);
        ofFill();
        ofCircle(centerX + (cos(angle) * (width * 0.5)), centerY + (sin(angle) * (height * 0.5)), 10);
    
    ofPopStyle();
    ofDisableSmoothing();
    ofDisableAlphaBlending();
}

float ofxAjaxLoadingCircle::getWidth()
{
    return width;
}

float ofxAjaxLoadingCircle::getHeight()
{
    return height;
}
