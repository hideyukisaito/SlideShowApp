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
}

//--------------------------------------------------------------
void testApp::initImages()
{
    bImageInitialized = false;
    
    if (XML.pushTag("IMAGE"))
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
            for (int i = 0; i < numPersonImages; i++)
            {
                fileNames.push_back(root + XML.getValue("FILE_NAME", "", i));
                cout << fileNames[i] << endl;
            }
            
            currentImage.load(ofToDataPath(fileNames[0]));
            
            XML.popTag();
        }
        XML.popTag();
    }
    
    titleImageIndex = 0;
    
    bPersonImagesAvailable = false;
    personImageIndex = 0;
    
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
    timer.setup(5000, false);
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
    if (!bPersonImagesAvailable)
    {
        ++titleImageIndex;
        if (numTitleImages == titleImageIndex)
        {
            ofRemoveListener(titleImage.FADE_OUT_COMPLETE, this, &testApp::onTitleImageFadeOutComplete);
            titleImageIndex = 0;
            
            timer.stopTimer();
            timer.setTimer(3000);
            ofAddListener(currentImage.FADE_OUT_COMPLETE, this, &testApp::onFadeOutComplete);
            bPersonImagesAvailable = true;
            currentImage.fadeIn();
            timer.startTimer();
        }
        else
        {
            titleImage.load(ofToDataPath(titleImageFileNames[titleImageIndex]));
            titleImage.fadeIn();
        }
    }
}

//--------------------------------------------------------------
void testApp::onFadeOutComplete(ofEventArgs &e)
{
    currentImage.load(ofToDataPath(fileNames[++personImageIndex]));
    if (numPersonImages - 1 == personImageIndex) personImageIndex = 0;
    currentImage.fadeIn();
    std::printf("fade out complete!\n");
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
        currentImage.fadeOut();
    }
    cout << "timer reached" << endl;
}

//--------------------------------------------------------------
void testApp::update()
{
    if (receiver.hasWaitingMessages())
    {
        ofxOscMessage msg;
        receiver.getNextMessage(&msg);
        if ("/image/filename" == msg.getAddress())
        {
            string filename = msg.getArgAsString(0);
            if (XML.pushTag("IMAGE"))
            {
                if (XML.pushTag("PERSONS"))
                {
                    numPersonImages = XML.getNumTags("FILE_NAME");
                    XML.popTag();
                }
                XML.popTag();
                
            }
            reload();
            cout << "message from testApp: " + filename << endl;
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
        currentImage.draw();
    }
    overlay.draw();
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