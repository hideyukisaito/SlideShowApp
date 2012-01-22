//
//  LoadingState.cpp
//  SlideShowApp
//
//  Created by Hideyuki Saito on 12/01/22.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "LoadingState.h"

//--------------------------------------------------------------
LoadingState::LoadingState()
{
    init();
}

//--------------------------------------------------------------
LoadingState::~LoadingState()
{
    
}

//--------------------------------------------------------------
void LoadingState::init()
{
    loading.loadImage(ofToDataPath("loading.png"));
}

//--------------------------------------------------------------
void LoadingState::stateEnter()
{
    alphaTween.setParameters(1, easingCirc, ofxTween::easeOut, 0, 127, 500, 0);
    ofAddListener(timer.TIMER_REACHED, this, &LoadingState::onTimerReached);
    timer.setup(50, true);
    rotation = 0;
}

//--------------------------------------------------------------
void LoadingState::stateExit()
{
    timer.stopTimer();
}

//--------------------------------------------------------------
void LoadingState::update()
{
    
}

//--------------------------------------------------------------
void LoadingState::draw()
{
    int alpha = (int)alphaTween.update();
    
    ofEnableAlphaBlending();
    
    ofPushStyle();
        ofSetColor(0, 0, 0, alpha);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
    ofPopStyle();
    
    ofPushMatrix();
        ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
        ofRotate(rotation);
        ofPushStyle();
        ofSetColor(255, 255, 255, alpha * 2);
        loading.draw(-loading.getWidth() / 2, -loading.getHeight() / 2);
        ofPopStyle();
    ofPopMatrix();
    
    ofDisableAlphaBlending();
}

//--------------------------------------------------------------
void LoadingState::onTimerReached(ofEventArgs &e)
{
    rotation = 360 == rotation ? 45 : rotation + 45;
    
    cout << "timer.count = " << timer.count << endl;
    if (60 == timer.count)
    {
        ofAddListener(alphaTween.end_E, this, &LoadingState::onFadeOutComplete);
        alphaTween.setParameters(1, easingCirc, ofxTween::easeOut, 127, 0, 500, 0);
    }
}

//--------------------------------------------------------------
void LoadingState::onFadeOutComplete(int &id)
{
    ofRemoveListener(alphaTween.end_E, this, &LoadingState::onFadeOutComplete);
    changeState("persons");
}

//--------------------------------------------------------------
string LoadingState::getName()
{
    return "loading";
}