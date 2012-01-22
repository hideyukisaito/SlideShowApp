//
//  TitleImagesState.cpp
//  SlideShowApp
//
//  Created by Hideyuki Saito on 12/01/22.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "TitleImagesState.h"

//--------------------------------------------------------------
TitleImagesState::TitleImagesState()
{
    init();
}

//--------------------------------------------------------------
TitleImagesState::~TitleImagesState()
{
    
}

//--------------------------------------------------------------
void TitleImagesState::stateEnter()
{
    index = 0;
    
    ofAddListener(timer.TIMER_REACHED, this, &TitleImagesState::onTimerReached);
    timer.setup(3000, true);
    timer.startTimer();
    
    initTweensForFadeIn();
}

//--------------------------------------------------------------
void TitleImagesState::stateExit()
{
    ofRemoveListener(timer.TIMER_REACHED, this, &TitleImagesState::onTimerReached);
    timer.stopTimer();
}

//--------------------------------------------------------------
void TitleImagesState::init()
{
    if (config.loadFile(ofToDataPath("SlideShowApp.xml")) && config.pushTag("IMAGE"))
    {
        string root = config.getAttribute("TITLES", "root", "");
        if (config.pushTag("TITLES"))
        {
            numImages = config.getNumTags("FILE_NAME");
            cout << "numImages = " << ofToString(numImages) << endl;
            for (int i = 0; i < numImages; i++)
            {
                ofImage image;
                if ( image.loadImage(ofToDataPath(root + config.getValue("FILE_NAME", "", i))) )
                    images.push_back(image);
            }
            
            index = 0;
            width = images[0].getWidth();
            height = images[0].getHeight();
            
            config.popTag();
        }
        config.popTag();
    }
}

//--------------------------------------------------------------
void TitleImagesState::initTweensForFadeIn()
{
    bFadeIn = true;
    alphaTween.setParameters(easingCirc, ofxTween::easeIn, 0, 255, 1000, 0);
}

//--------------------------------------------------------------
void TitleImagesState::initTweensForFadeOut()
{
    bFadeIn = false;
    alphaTween.setParameters(easingCirc, ofxTween::easeOut, 255, 0, 1000, 0);
}

//--------------------------------------------------------------
void TitleImagesState::update()
{
    
}

//--------------------------------------------------------------
void TitleImagesState::draw()
{
    ofPushStyle();
        ofEnableAlphaBlending();
        ofSetColor(255, 255, 255, (int)alphaTween.update());
        images[index].draw(0, 0, width, height);
        ofDisableAlphaBlending();
    ofPopStyle();
}



//--------------------------------------------------------------
void TitleImagesState::onTimerReached(ofEventArgs &e)
{
    if (bFadeIn)
    {
        initTweensForFadeOut();
    }
    else
    {
        ++index;
        if (numImages == index)
        {
            index = 0;
            changeState("persons");
        }
        else
        {
            initTweensForFadeIn();
        }
    }
}



//--------------------------------------------------------------
string TitleImagesState::getName()
{
    return "title";
}
