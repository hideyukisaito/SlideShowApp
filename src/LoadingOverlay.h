//
//  LoadingOverlay.h
//  SlideShowApp
//
//  Created by Hideyuki Saito on 11/12/10.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#ifndef SlideShowApp_LoadingOverlay_h
#define SlideShowApp_LoadingOverlay_h

#include "ofMain.h"
#include "ofxTween.h"
#include "ofxAjaxLoadingCircle.h"

class LoadingOverlay
{
public:
    LoadingOverlay();
    ~LoadingOverlay();
    
    void setup(float w, float h);
    void setColor(ofColor col);
    void setPosition(float x, float y);
    void toggle();
    void show();
    void hide();
    void draw();
    
private:
    float width;
    float height;
    float xpos;
    float ypos;
    ofColor color;
    
    ofxAjaxLoadingCircle circle;
    
    bool bShow;
    
    ofxTween yposTween;
    ofxEasingQuart easing;
};

#endif
