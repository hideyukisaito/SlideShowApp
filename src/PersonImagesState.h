//
//  PersonImagesState.h
//  SlideShowApp
//
//  Created by Hideyuki Saito on 12/01/22.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef SlideShowApp_PersonImagesState_h
#define SlideShowApp_PersonImagesState_h

#include "ofxState.h"
#include "ofxXmlSettings.h"
#include "HSSharedData.h"
#include "ofxTimer.h"
#include "ofxTween.h"

class PersonImagesState : public Apex::ofxState<HSSharedData>
{
    public:
        PersonImagesState();
        ~PersonImagesState();
        
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
        bool isKeyIndex(int index);
        
        void onTimerReached(ofEventArgs &e);
        
        bool bFadeIn;
        bool bMovieLoaded;
        bool bShowMovie;
        
        float width;
        float height;
        ofImage image;
        ofVideoPlayer currentMovie;
        vector<ofVideoPlayer> movies;
        vector<string> imageFilenames;
        
        
        int numImages;
        int numMovies;
        int imageIndex;
        int movieIndex;
        vector<int> keyIndexes;
        
        ofxTween alphaTween;
        ofxEasingCirc easingCirc;
        
        ofxTimer timer;
};

#endif
