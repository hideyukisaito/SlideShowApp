//
//  GlassImagesState.h
//  SlideShowApp
//
//  Created by Hideyuki Saito on 12/01/22.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef SlideShowApp_GlassImagesState_h
#define SlideShowApp_GlassImagesState_h

#include "ofxState.h"
#include "ofxXmlSettings.h"
#include "ofxTween.h"
#include "ofxTimer.h"
#include "HSSharedData.h"

#define NUM_GLASS_IMAGES 32


class GlassImagesState : public Apex::ofxState<HSSharedData>
{
    public:
        GlassImagesState();
        ~GlassImagesState();
        
        void stateEnter();
        void stateExit();
        void update();
        void draw();
        string getName();
    
    private:
        ofxXmlSettings config;
        
        void init();
        void initTweensForFadeIn();
        void initTweensForFadeOut();
        
        void onTimerReached(ofEventArgs &e);
        
        int startIndex;
        int imageWidth;
        int imageHeight;
        
        bool bFadeIn;
        
        vector<ofImage> images;
        vector<ofxTween> tweens;
        
        ofxTween tween_1;
        ofxTween tween_2;
        ofxTween tween_3;
        ofxTween tween_4;
        ofxEasingCirc easing_1;
        ofxEasingCirc easing_2;
        ofxEasingCirc easing_3;
        ofxEasingCirc easing_4;
    
        ofxTimer timer;
};

#endif
