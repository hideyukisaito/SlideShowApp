#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    ofBackground(255);
    ofSetFrameRate(60);
    ofEnableSmoothing();
    
    for (int i = 0; i < NUM_IMAGES; i++)
    {
        std::stringstream path, num;
        path << "images/testimage_";
        num << i + 1;
        path << num.str() << ".jpg";
        cout << path.str() << endl;
        
        ofImage lImg;
        lImg.allocate(SCREEN_WIDTH, SCREEN_HEIGHT, OF_IMAGE_COLOR);
        lImg.loadImage(path.str());
        largeImages.push_back(lImg);
        
        ofImage sImg;
        sImg.allocate(SCREEN_WIDTH, SCREEN_HEIGHT, OF_IMAGE_COLOR);
        sImg.setFromPixels(lImg.getPixels(), lImg.getWidth(), lImg.getHeight(), OF_IMAGE_COLOR);
        sImg.resize(SCREEN_WIDTH / 8, SCREEN_HEIGHT / 8);
        smallImages.push_back(sImg);
    }
}

//--------------------------------------------------------------
void testApp::update()
{
    if (ofGetFrameNum() % (int)(ofGetFrameRate() / 8) == 0)
    {
        int lastIndex = currentImageIndex;
        do
        {
            currentImageIndex = (int)ofRandom(NUM_IMAGES);
        } while(currentImageIndex == lastIndex);
    }
}

//--------------------------------------------------------------
void testApp::draw()
{
    ofImage img = smallImages[currentImageIndex];
    img.draw(img.width * (currentImageIndex % 4), img.height * (int)(currentImageIndex / 4));
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