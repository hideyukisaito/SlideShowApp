#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 1920

#define ENV_RELAESE // uncomment this when release

//========================================================================
int main()
{

    ofAppGlutWindow window;
    #ifdef ENV_RELEASE
        ofSetupOpenGL(&window, SCREEN_WIDTH, SCREEN_HEIGHT, OF_WINDOW);
    #else
        ofSetupOpenGL(&window, SCREEN_WIDTH, SCREEN_HEIGHT, OF_WINDOW);
    #endif
    
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());

}
