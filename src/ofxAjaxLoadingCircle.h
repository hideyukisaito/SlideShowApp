//
//  ofxAjaxLoadingCircle.h
//  SlideShowApp
//
//  Created by Hideyuki Saito on 11/12/10.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#ifndef SlideShowApp_ofxAjaxLoadingCircle_h
#define SlideShowApp_ofxAjaxLoadingCircle_h

#include "ofMain.h"
#include "ofxTween.h"

class ofxAjaxLoadingCircle
{
public:
    ofxAjaxLoadingCircle();
    ~ofxAjaxLoadingCircle();
    
    void setup(float w, float h);
    void setBackgroundColor(int r, int g, int b);
    void setBackgroundColor(ofColor col);
    void setForegroundColor(int r, int g, int b);
    void setForegroundColor(ofColor col);
    void toggleFade();
    void show();
    void hide();
    void update(ofEventArgs &e);
    void draw(float x, float y);
    
    float getWidth();
    float getHeight();
    
private:
    float width;
    float height;
    ofColor backgroundColor;
    ofColor foregroundColor;
    float devides;
    bool bFadeIn;
    float alpha, centerX, centerY, angle, step;
    
    ofxTween alphaTween;
    ofxEasingLinear easingLinear;
};

#endif
