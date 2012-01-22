//
//  TitleImagesState.h
//  SlideShowApp
//
//  Created by Hideyuki Saito on 12/01/22.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef SlideShowApp_TitleImagesState_h
#define SlideShowApp_TitleImagesState_h

#include "ofxState.h"
#include "ofxXmlSettings.h"
#include "HSSharedData.h"
#include "ofxHSBasicImage.h"
#include "ofxTween.h"
#include "ofxTimer.h"

class TitleImagesState : public Apex::ofxState<HSSharedData>
{
    public:
        TitleImagesState();
        ~TitleImagesState();
        
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
        
        bool bFadeIn;
        
        float width;
        float height;
        vector<ofImage> images;
        
        int numImages;
        int index;
        
        ofxTween alphaTween;
        ofxEasingCirc easingCirc;
        
        ofxTimer timer;
};

#endif
