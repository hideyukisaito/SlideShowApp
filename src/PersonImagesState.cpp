//
//  PersonImagesState.cpp
//  SlideShowApp
//
//  Created by Hideyuki Saito on 12/01/22.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "PersonImagesState.h"

//--------------------------------------------------------------
PersonImagesState::PersonImagesState()
{
    init();
}

//--------------------------------------------------------------
PersonImagesState::~PersonImagesState()
{
    
}

//--------------------------------------------------------------
void PersonImagesState::stateEnter()
{
    init();
    
    imageIndex = 1;
    movieIndex = 0;
    bShowMovie = false;
    
    ofAddListener(timer.TIMER_REACHED, this, &PersonImagesState::onTimerReached);
    timer.setup(3000, true);
    timer.startTimer();
    
    initTweensForFadeIn();
}

//--------------------------------------------------------------
void PersonImagesState::stateExit()
{
    ofRemoveListener(timer.TIMER_REACHED, this, &PersonImagesState::onTimerReached);
    timer.stopTimer();
}

//--------------------------------------------------------------
void PersonImagesState::init()
{
    if (config.loadFile(ofToDataPath("SlideShowApp.xml")) && config.pushTag("IMAGE"))
    {
        string root = config.getAttribute("PERSONS", "root", "images/persons/");
        if (config.pushTag("PERSONS"))
        {
            numImages = config.getNumTags("FILE_NAME");
            for (int i = 0; i < numImages; i++)
            {
                imageFilenames.push_back(ofToDataPath(root + config.getValue("FILE_NAME", "FILE_NAME", i)));
            }
            
            image.loadImage(imageFilenames[0]);
            imageIndex = 0;
            width = image.getWidth();
            height = image.getHeight();
            
            config.popTag();
        }
        
        root = config.getAttribute("MOVIES", "root", "movies/");
        if (config.pushTag("MOVIES"))
        {
            numMovies = config.getNumTags("FILE_NAME");
            int baseIndex = numImages / numMovies;
            
            for (int i = 0; i < numMovies; i++)
            {
                ofVideoPlayer movie;
                if ( movie.loadMovie(ofToDataPath(root + config.getValue("FILE_NAME", "FILE_NAME", i))) )
                {
                    movies.push_back(movie);
                }
                keyIndexes.push_back(baseIndex * (i + 1));
            }
            
            movieIndex = 0;
            currentMovie = movies[0];
            currentMovie.setLoopState(OF_LOOP_NORMAL);
            currentMovie.play();
            
            config.popTag();
        }
        
        config.popTag();
    }
}

//--------------------------------------------------------------
void PersonImagesState::initTweensForFadeIn()
{
    bFadeIn = true;
    alphaTween.setParameters(easingCirc, ofxTween::easeOut, 0, 255, 1000, 0);
}

//--------------------------------------------------------------
void PersonImagesState::initTweensForFadeOut()
{
    bFadeIn = false;
    alphaTween.setParameters(easingCirc, ofxTween::easeOut, 255, 0, 1000, 0);
}

//--------------------------------------------------------------
bool PersonImagesState::isKeyIndex(int index)
{
    vector<int>::iterator iter = find(keyIndexes.begin(), keyIndexes.end(), imageIndex);
    
    if (iter != keyIndexes.end()) return true;
    return false;
}

//--------------------------------------------------------------
void PersonImagesState::update()
{
    if (currentMovie.isPlaying()) currentMovie.update();
}

//--------------------------------------------------------------
void PersonImagesState::draw()
{
    ofPushStyle();
        ofEnableAlphaBlending();
        ofSetColor(255, 255, 255, (int)alphaTween.update());
        if (bShowMovie)
        {
            currentMovie.draw(0, 0, width, height);
        }
        else
        {
            image.draw(0, 0, width, height);
        }
        ofDisableAlphaBlending();
    ofPopStyle();
}



//--------------------------------------------------------------
void PersonImagesState::onTimerReached(ofEventArgs &e)
{
    if (bFadeIn)
    {
        initTweensForFadeOut();
    }
    else
    {
        if (numImages == imageIndex && numMovies == movieIndex)
        {
            changeState("glass");
        }
        else
        {
            if (!bShowMovie && isKeyIndex(imageIndex))
            {
                bShowMovie = true;
                currentMovie = movies[movieIndex];
                currentMovie.play();
                ++movieIndex;
                initTweensForFadeIn();
            }
            else
            {
                bShowMovie = false;
                image.loadImage(imageFilenames[imageIndex]);
                ++imageIndex;
                initTweensForFadeIn();
            }
        }
    }
}



//--------------------------------------------------------------
string PersonImagesState::getName()
{
    return "persons";
}