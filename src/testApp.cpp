#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    ofBackground(255);
    ofSetFrameRate(60);
    ofEnableSmoothing();
    
    drawCount = 0;
    
    //srand(time(NULL));
    
    for (int i = 0; i < NUM_THUMBNAILS; i++)
    {
        std::stringstream path, num;
        path << "images/testimage_";
        num << i + 1;
        path << num.str() << ".jpg";
        
        ofImage lImg;
        //lImg.allocate(SCREEN_WIDTH, SCREEN_HEIGHT, OF_IMAGE_COLOR);
        lImg.loadImage(path.str());
        largeImages.push_back(lImg);
        
        ofImage sImg;
        //sImg.allocate(SCREEN_WIDTH, SCREEN_HEIGHT, OF_IMAGE_COLOR);
        sImg.setFromPixels(lImg.getPixels(), lImg.getWidth(), lImg.getHeight(), OF_IMAGE_COLOR);
        sImg.resize(SCREEN_WIDTH / 8, SCREEN_HEIGHT / 8);
        smallImages.push_back(sImg);
    }
    
    displayMode = DISPLAY_MODE_THUMB_SWITCH;
}

//--------------------------------------------------------------
void testApp::update()
{
    
}

//--------------------------------------------------------------
void testApp::draw()
{
    switch (displayMode)
    {
        case DISPLAY_MODE_THUMB_SWITCH:
            switchThumbnails();
            break;
            
        case DISPLAY_MODE_THUMB_FIX:
            tilingThumbnails();
            break;
            
    }
    
    if (ofGetFrameNum() % (int)ofGetFrameRate() == 0)
    {
        drawCount++;
    }
    
    if (drawCount >= 5)
    {
        displayMode = DISPLAY_MODE_THUMB_FIX;
    }
}

//--------------------------------------------------------------
void testApp::switchThumbnails()
{
    if (ofGetFrameNum() % (int)(ofGetFrameRate() / 16) == 0)
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
    if (ofGetFrameNum() % (int)(ofGetFrameRate() / 16) == 0)
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
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}