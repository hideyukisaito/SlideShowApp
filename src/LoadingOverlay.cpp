//
//  LoadingOverlay.cpp
//  SlideShowApp
//
//  Created by Hideyuki Saito on 11/12/10.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "LoadingOverlay.h"

LoadingOverlay::LoadingOverlay()
{
    width = ofGetWidth();
    height = ofGetHeight();
    xpos = 0;
    ypos = ofGetHeight();
    color.set(0, 0, 0);
    bShow = false;
    
    circle.setup(170, 170);
    
    yposTween.setParameters(1, easing, ofxTween::easeOut, ypos, ofGetHeight(), 1000, 0);
}

LoadingOverlay::~LoadingOverlay()
{
    
}

void LoadingOverlay::setup(float w, float h)
{
    width = w;
    height = h;
}

void LoadingOverlay::setColor(ofColor col)
{
    color = col;
}

void LoadingOverlay::toggle()
{
    bShow = !bShow;
    circle.toggleFade();
    if (bShow)
    {
        yposTween.setParameters(1, easing, ofxTween::easeOut, ypos, 0, 1000, 0);
    }
    else
    {
        yposTween.setParameters(1, easing, ofxTween::easeOut, ypos, ofGetHeight(), 1000, 0);
    }
}

void LoadingOverlay::show()
{
    bShow = true;
    yposTween.setParameters(1, easing, ofxTween::easeOut, ypos, 0, 1000, 0);
    circle.show();
}

void LoadingOverlay::hide()
{
    bShow = false;
    yposTween.setParameters(1, easing, ofxTween::easeOut, ypos, ofGetHeight(), 1000, 0);
    circle.hide();
}

void LoadingOverlay::draw()
{
    ypos = yposTween.update();
    ofPushStyle();
        ofSetColor(color);
        ofFill();
        ofRect(xpos, ypos, width, height);
    ofPopStyle();
    
    circle.draw(xpos + (width - circle.getWidth()) * 0.5, ypos + (height - circle.getHeight()) * 0.6);
}
