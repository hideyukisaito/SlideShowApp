#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    ofBackground(255);
    ofSetFrameRate(60);
    ofEnableSmoothing();
    
    XML.loadFile(ofToDataPath("SlideShowApp.xml"));
    
    control.setup("control panel test", 0, 0, 340, 400);
    control.addPanel("panel 1", 1);
    control.addSlider("rotation", "rot", 100, 0, 360, false);
    
    receiver.setup(PORT);
    
    initImages();
    
    displayMode = DISPLAY_MODE_THUMB_SWITCH;
    
    timer.setup(5000, true);
    ofAddListener(timer.TIMER_REACHED, this, &testApp::onTimerReached);
    titleImage.setDelay(1000);
    titleImage.fadeIn();
}

//--------------------------------------------------------------
void testApp::initImages()
{
    bImageInitialized = bShowMovie = false;
    
    if (XML.loadFile(ofToDataPath("SlideShowApp.xml")) && XML.pushTag("IMAGE"))
    {
        string root = XML.getAttribute("TITLES", "root", "");
        if (XML.pushTag("TITLES"))
        {
            numTitleImages = XML.getNumTags("FILE_NAME");
            for (int i = 0; i < numTitleImages; i++)
            {
                titleImageFileNames.push_back(root + XML.getValue("FILE_NAME", "", i));
            }
            titleImage.load(ofToDataPath(titleImageFileNames[0]));
            titleImage.setFadeDuration(1500, 2500);
            ofAddListener(titleImage.FADE_OUT_COMPLETE, this, &testApp::onTitleImageFadeOutComplete);
            
            XML.popTag();
        }
        
        root = XML.getAttribute("PERSONS", "root", "");
        if (XML.pushTag("PERSONS"))
        {
            numPersonImages = XML.getNumTags("FILE_NAME");
            fileNames.clear();
            for (int i = 0; i < numPersonImages; i++)
            {
                fileNames.push_back(root + XML.getValue("FILE_NAME", "", i));
                cout << "pushed file name: " << fileNames[i] << endl;
            }
            currentImage.load(ofToDataPath(fileNames[0]));
            
            XML.popTag();
        }
        
        root = XML.getAttribute("MOVIES", "root", "");
        if (XML.pushTag("MOVIES"))
        {
            numMovieFiles = XML.getNumTags("FILE_NAME");
            movies.clear();
            
            int baseIndex = numPersonImages / numMovieFiles;
            cout << "baseIndex = " << baseIndex << endl;
            for (int i = 0; i < numMovieFiles; i++)
            {
                ofVideoPlayer movie;
                
                if ( movie.loadMovie(root + XML.getValue("FILE_NAME", "", i)) )
                {
                    movies.push_back(movie);
                }
                movieKeyIndexes.push_back(baseIndex * (i + 1));
            }
            
            currentMovie = movies[0];
            currentMovie.setLoopState(OF_LOOP_NORMAL);
            currentMovie.play();
            
            XML.popTag();
        }
        XML.popTag();
    }
    
    titleImageIndex = personImageIndex = movieIndex = 0;
    bPersonImagesAvailable = bMoviePlayed = bSkipCheckingIndex = false;
    bImageInitialized = true;
}

//--------------------------------------------------------------
void testApp::reload()
{
    timer.stopTimer();
    timer.reset();
    
    overlay.show();
    initImages();
    
    ofAddListener(timer.TIMER_REACHED, this, &testApp::onReloadCompleted);
    timer.setup(8000, false);
}

void testApp::onReloadCompleted(ofEventArgs&)
{
    ofRemoveListener(timer.TIMER_REACHED, this, &testApp::onReloadCompleted);
    
    timer.stopTimer();
    timer.reset();
    overlay.hide();
    timer.setup(5000, true);
    ofAddListener(timer.TIMER_REACHED, this, &testApp::onTimerReached);
    cout << "=== RELOAD COMPLETED ===" << endl;
}

//--------------------------------------------------------------
void testApp::onTitleImageFadeOutComplete(ofEventArgs &e)
{
    titleImage.setDelay(0);
    if (!bPersonImagesAvailable)
    {
        if (numTitleImages - 1 == titleImageIndex)
        {
            ofRemoveListener(titleImage.FADE_OUT_COMPLETE, this, &testApp::onTitleImageFadeOutComplete);
            titleImageIndex = -1;
            
            timer.stopTimer();
            timer.setTimer(5000);
            ofAddListener(currentImage.FADE_OUT_COMPLETE, this, &testApp::onImageFadeOutComplete);
            bPersonImagesAvailable = true;
            currentImage.fadeIn();
            timer.startTimer();
        }
        else
        {
            titleImage.load(ofToDataPath(titleImageFileNames[++titleImageIndex]));
            titleImage.fadeIn();
        }
    }
}

//--------------------------------------------------------------
void testApp::onImageFadeOutComplete(ofEventArgs &e)
{
    cout << "numPersonImages              = " << numPersonImages << endl;
    cout << "personImageIndex             = " << personImageIndex << endl;
    cout << "bSkipCheckingIndex           = " << bSkipCheckingIndex << endl;
    cout << "isKeyIndex(personImageIndex) = " << isKeyIndex(personImageIndex) << endl;
    if (!bSkipCheckingIndex && isKeyIndex(personImageIndex))
    {
        cout << "===== PLAY MOVIE =====" << endl;
        bSkipCheckingIndex = true;
        bShowMovie = true;
        movieAlphaTween.setParameters(100, easingCirc, ofxTween::easeOut, movieAlpha, 255, 1000, 0);
        currentMovie.play();
    }
    else
    {
        cout << "===== LOAD NEXT IMAGE =====" << endl;
        bSkipCheckingIndex = false;
        personImageIndex = numPersonImages - 1 == personImageIndex ? -1 : personImageIndex + 1;
        
        if (0 > personImageIndex)
        {
            ofRemoveListener(currentImage.FADE_OUT_COMPLETE, this, &testApp::onImageFadeOutComplete);
            bPersonImagesAvailable = false;
            personImageIndex = 0;
            currentImage.load(ofToDataPath(fileNames[0]));
            
            ofAddListener(titleImage.FADE_OUT_COMPLETE, this, &testApp::onTitleImageFadeOutComplete);
            
        }
        else
        {
            currentImage.load(ofToDataPath(fileNames[personImageIndex]));
            currentImage.fadeIn();
            cout << "image loaded. index          = " << personImageIndex << endl;
        }
        
    }
}

//--------------------------------------------------------------
void testApp::onMovieFadeOutComplete(int &id)
{
    ofRemoveListener(movieAlphaTween.end_E, this, &testApp::onMovieFadeOutComplete);
    movieIndex = movies.size() - 1 == movieIndex ? 0 : movieIndex + 1;
    currentMovie = movies[movieIndex];
    bShowMovie = false;
    
    static ofEventArgs eventArgs;
    ofNotifyEvent(currentImage.FADE_OUT_COMPLETE, eventArgs, &currentImage);
    
    cout << "movie complete!" << endl;
}

//--------------------------------------------------------------
void testApp::onTimerReached(ofEventArgs &e)
{
    if (!bPersonImagesAvailable)
    {
        titleImage.fadeOut();
    }
    else
    {
        if (bShowMovie == true)
        {
            ofAddListener(movieAlphaTween.end_E, this, &testApp::onMovieFadeOutComplete);
            movieAlphaTween.setParameters(100, easingCirc, ofxTween::easeOut, movieAlpha, 0, 1000, 0);
        }
        else
        {
            currentImage.fadeOut();
        }
    }
    cout << "timer reached" << endl;
}

//--------------------------------------------------------------
void testApp::update()
{
    movieAlpha = movieAlphaTween.update();
    currentMovie.update();
    
    if (receiver.hasWaitingMessages())
    {
        ofxOscMessage msg;
        receiver.getNextMessage(&msg);
        if ("/image/filename" == msg.getAddress())
        {
            string filename = msg.getArgAsString(0);
            cout << "received new file name: " << filename << endl;
            reload();
        }
    }
}

//--------------------------------------------------------------
void testApp::draw()
{
    if (!bPersonImagesAvailable)
    {
        titleImage.draw();
    }
    else
    {
        if (bShowMovie == true)
        {
            ofPushStyle();
                ofEnableAlphaBlending();
                ofSetColor(255, 255, 255, movieAlpha);
                currentMovie.draw(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                ofDisableAlphaBlending();
            ofPopStyle();
        }
        else
        {
            currentImage.draw();
        }
    }
    overlay.draw();
}


//--------------------------------------------------------------
bool testApp::isKeyIndex(int index)
{
    vector<int>::iterator iter = find(movieKeyIndexes.begin(), movieKeyIndexes.end(), personImageIndex);
    
    if (iter != movieKeyIndexes.end()) return true;
    return false;
}

//--------------------------------------------------------------
void testApp::switchThumbnails()
{
    if (ofGetFrameNum() % (int)(ofGetFrameRate() / 4) == 0)
    {
        int lastIndex = currentThumbnailIndex;
        
        do
        {
            currentThumbnailIndex = (int)ofRandom(NUM_THUMBNAILS);
        } while(currentThumbnailIndex == lastIndex);
    }
    
    ofImage img = smallImages[currentThumbnailIndex];
    img.draw(img.width * (currentThumbnailIndex % 4), img.height * (int)(currentThumbnailIndex / 4));
}

//--------------------------------------------------------------
void testApp::tilingThumbnails()
{
    if (ofGetFrameNum() % (int)(ofGetFrameRate() / 4) == 0)
    {
        if (availableThumbIndexes.empty())
        {
            availableThumbIndexes.push_back(currentThumbnailIndex);
        }
        
        if (NUM_THUMBNAILS != availableThumbIndexes.size())
        {
            int index = (int)ofRandom(0, NUM_THUMBNAILS);
            
            bool bValidIndex = false;
            while (!bValidIndex)
            {
                for (int i = 0; i < availableThumbIndexes.size(); i++)
                {
                    if (index == availableThumbIndexes[i])
                    {
                        bValidIndex = false;
                        
                        index = (int)ofRandom(0, NUM_THUMBNAILS);
                        
                        break;
                    }
                    bValidIndex = true;
                }
            }
            
            availableThumbIndexes.push_back(index);
        }
    }
    
    for (int i = 0; i < availableThumbIndexes.size(); i++)
    {
        ofImage* img = &smallImages[i];
        img->draw(img->width * (availableThumbIndexes[i] % 4), img->height * (int)(availableThumbIndexes[i] / 4));
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    currentImage.fadeIn();
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::exit()
{
    titleImageFileNames.clear();
    
    titleImage.clear();
    currentImage.clear();
    currentMovie.close();
    
    for (int i = 0; i < movies.size(); i++)
    {
        movies[i].close();
    }
    
    fileNames.clear();
    
    XML.saveFile();
    cout << "BYE!" << endl;
}