#include "ofMain.h"
#include "testApp.h"
//#include "showAllMarker.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){

	ofAppGlutWindow window;
	// can be OF_WINDOW or OF_FULLSCREEN
	ofSetupOpenGL(&window, 800, 600, OF_WINDOW);			// <-------- setup the GL context
	ofRunApp( new testApp());


	//char menu;
	//cout<<" +++++ Select Menu +++++ "<<endl;
	//cout<<" [ 1 ] Full Program "<<endl;
	//cout<<" [ 2 ] Show Graphic on All Marker"<<endl;
	//cin>>menu;

	//if(menu=='1')
	//{ofRunApp( new testApp55());}
	//else
	//{ofRunApp( new showAllMarker());}

	
	//{ofRunApp( new testApp());}


}
