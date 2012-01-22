//
//  LoadingState.h
//  SlideShowApp
//
//  Created by Hideyuki Saito on 12/01/22.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef SlideShowApp_LoadingState_h
#define SlideShowApp_LoadingState_h

#include "ofxState.h"
#include "HSSharedData.h"
#include "ofxTimer.h"
#include "ofxTween.h"

class LoadingState : public Apex::ofxState<HSSharedData>
{
    public:
        LoadingState();
        ~LoadingState();
        
        void stateEnter();
        void stateExit();
        void update();
        void draw();
        string getName();
    
    private:
        void init();
        void onTimerReached(ofEventArgs &e);
        void onFadeOutComplete(int &id);
        
        ofImage loading;
        int rotation;
        
        ofxTimer timer;
        
        ofxTween alphaTween;
        ofxEasingCirc easingCirc;
};

#endif
