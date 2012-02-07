//
//  GlassImagesState.cpp
//  SlideShowApp
//
//  Created by Hideyuki Saito on 12/01/22.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "GlassImagesState.h"

//--------------------------------------------------------------
GlassImagesState::GlassImagesState()
{
    init();
}

//--------------------------------------------------------------
GlassImagesState::~GlassImagesState()
{
    
}

//--------------------------------------------------------------
void GlassImagesState::stateEnter()
{
    startIndex = 0;
    
    ofAddListener(timer.TIMER_REACHED, this, &GlassImagesState::onTimerReached);
    timer.setup(sharedData->fadeInMillisecond, true);
    timer.startTimer();
    
    initTweensForFadeIn();
}

//--------------------------------------------------------------
void GlassImagesState::stateExit()
{
    ofRemoveListener(timer.TIMER_REACHED, this, &GlassImagesState::onTimerReached);
    timer.stopTimer();
}

//--------------------------------------------------------------
void GlassImagesState::init()
{
    config.loadFile(ofToDataPath("SlideShowApp.xml"));
    
    if (config.pushTag("IMAGE"))
    {
        string root = config.getAttribute("GLASSES", "root", "");
        for (int i = 0; i < NUM_GLASS_IMAGES; i++)
        {
            ofImage image;
            image.loadImage(ofToDataPath(root + ofToString(i + 1) + ".jpg"));
            images.push_back(image);
        }
        config.popTag();
    }
    
    startIndex = 0;
    imageWidth = images[0].getWidth();
    imageHeight = images[0].getHeight();
}

//--------------------------------------------------------------
void GlassImagesState::initTweensForFadeIn()
{
    bFadeIn = true;
    tween_1.setParameters(easing_1, ofxTween::easeOut, 0, 255, sharedData->fadeInDuration, 0);
    tween_2.setParameters(easing_2, ofxTween::easeOut, 0, 255, sharedData->fadeInDuration, 250);
    tween_3.setParameters(easing_3, ofxTween::easeOut, 0, 255, sharedData->fadeInDuration, 500);
    tween_4.setParameters(easing_4, ofxTween::easeOut, 0, 255, sharedData->fadeInDuration, 750);
}

//--------------------------------------------------------------
void GlassImagesState::initTweensForFadeOut()
{
    bFadeIn = false;
    tween_1.setParameters(easing_1, ofxTween::easeIn, 255, 0, sharedData->fadeOutDuration, 0);
    tween_2.setParameters(easing_2, ofxTween::easeIn, 255, 0, sharedData->fadeOutDuration, 250);
    tween_3.setParameters(easing_3, ofxTween::easeIn, 255, 0, sharedData->fadeOutDuration, 500);
    tween_4.setParameters(easing_4, ofxTween::easeIn, 255, 0, sharedData->fadeOutDuration, 750);
}

//--------------------------------------------------------------
void GlassImagesState::update()
{
    
}

//--------------------------------------------------------------
void GlassImagesState::draw()
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            ofPushStyle();
                ofEnableAlphaBlending();
                switch ((i + j) % 4)
                {
                    case 0:
                        ofSetColor(255, 255, 255, tween_1.update());
                        break;
                    case 1:
                        ofSetColor(255, 255, 255, tween_2.update());
                        break;
                    case 2:
                        ofSetColor(255, 255, 255, tween_3.update());
                        break;
                    case 3:
                        ofSetColor(255, 255, 255, tween_4.update());
                        break;
                }
                
                images[startIndex + (i + j)].draw(imageWidth * (i % 2), imageHeight * (j % 2));
                ofDisableAlphaBlending();
            ofPopStyle();
        }
    }
}



//--------------------------------------------------------------
void GlassImagesState::onTimerReached(ofEventArgs &e)
{
    if (bFadeIn)
    {
        timer.setTimer(sharedData->fadeOutMillisecond);
        initTweensForFadeOut();
    }
    else
    {
        timer.setTimer(sharedData->fadeInMillisecond);
        startIndex += 4;
        if (NUM_GLASS_IMAGES == startIndex)
        {
            startIndex = 0;
            changeState("title");
        }
        else
        {
            initTweensForFadeIn();
        }
    }
}



//--------------------------------------------------------------
string GlassImagesState::getName()
{
    return "glass";
}