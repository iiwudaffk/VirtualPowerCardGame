#include "ofMain.h"
#include "testApp.h"
//#include "showAllMarker.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){

	ofAppGlutWindow window;
	// can be OF_WINDOW or OF_FULLSCREEN
	ofSetupOpenGL(&window, 1280, 800, OF_WINDOW);			// <-------- setup the GL context
	ofRunApp( new testApp());
}
