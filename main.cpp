#include "ofMain.h"
#include "testApp.h"
//#include "showAllMarker.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){

	int winselect;
	int screenX;
	int screenY;
	cout<<"###############################################"<<endl;
	cout<<"######### Welcome to POWERCARD Game ###########"<<endl;
	cout<<"Please setup window :"<<endl;
	cout<<"[1] 640 x 480 (4:3)"<<endl;
	cout<<"[2] 800 x 600 (4:3)"<<endl;
	cout<<"[3] 1024 x 768 (4:3)"<<endl;
	cout<<"[4] 1366 x 768 (16:9)"<<endl;
	cout<<"[5] 1280 x 1024 (5:4)"<<endl;
	cout<<"[6] 1920 x 1080 (16:9)"<<endl;
	cout<<"###############################################"<<endl;
	cin>>winselect;

	if(winselect==1){screenX=640;screenY=420;}
	else if(winselect==2){screenX=800;screenY=540;}
	else if(winselect==3){screenX=1024;screenY=708;}
	else if(winselect==4){screenX=1366;screenY=708;}
	else if(winselect==5){screenX=1280;screenY=984;}
	else if(winselect==6){screenX=1920;screenY=1020;}
	else {screenX=800;screenY=540;}

	cout<<"Screen Resolution: "<<screenX<<"x"<<screenY<<endl;
	cout<<"###############################################"<<endl;

	ofAppGlutWindow window;
	// can be OF_WINDOW or OF_FULLSCREEN
	ofSetupOpenGL(&window, screenX, screenY, OF_WINDOW);			// <-------- setup the GL context
	ofRunApp( new testApp(screenX,screenY));
}
