#ifndef _TEST_APP
#define _TEST_APP

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "ofxOpenCv.h"
#include "ofxARToolkitPlus.h"
#include "ofVectorMath.h"
#include "ofx3DModelLoader.h"
#include "ofMain.h"

#include "glut.h"
#include <fstream>

// Uncomment this to use a camera instead of a video file
#define CAMERA_CONNECTED

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		
		// draw graphic object static on marker
		void drawAR(int markerIndex);
		
		// draw graphic effect
		void drawEffect(int markerIndex);
		
		// calculate distance between 2 marker
		float calDistance(ofPoint p1,ofPoint p2);

		// calculate position of cards on field while marker move
		void updateCardFieldPosition(ofPoint mTrans);

		// return index of field position as nearest between marker and all field position
		int findNearestFieldAndMaker(ofPoint pMarker);

		void keyPressed  (int key);
		//void keyReleased(int key);
		//void mouseMoved(int x, int y );
		//void mouseDragged(int x, int y, int button);
		//void mousePressed(int x, int y, int button);
		//void mouseReleased(int x, int y, int button);
		//void windowResized(int w, int h);

		//float testApp::findHueInArea(cv::Mat &input, cv::Point input_point, int radius)


		// game state number
		int gameState;
		/* 
		* 0 = open program first time
		* 1 = found field marker
		* 2 = p1 set card done
		* 3 = p2 set card done
		* 4 = p1 and p2 set card done
		* 5 = fighting turn and calculate damage
		* 6 = 
		*/

		// nearest
		int nearIndex;
		
		/*
		* 0 = card field
		* 1 = (0.x -a , 0.y +b)
		* 2 = (0.x -a , 0.y)
		* 3 = (0.x -a , 0.y -b)
		* 4 = (0.x +a , 0.y +b)
		* 5 = (0.x +a , 0.y)
		* 6 = (0.x +a , 0.y -b)

		|=====|=====|=====|
		|  1  |  -  |  4  |
		|=====|=====|=====|
		|  2  |  0  |  5  |
		|=====|=====|=====|
		|  3  |  -  |  6  |
		|=====|=====|=====|

		*/
		// card position reference by card field get from matrix
		ofPoint cardFieldPos[7];
		ofPoint cardFieldCenter;

		//

		// 
		int markerIDdetected[10];
		ofMatrix4x4 mm1;
		ofMatrix4x4 mm2;
		ofVec3f mm3;
		ofVec3f mm4;
		ofPoint matrixTrans[20];
		
		/* Size of the image */
		int width, height;
	
		/* Use either camera or a video file */
		#ifdef CAMERA_CONNECTED
		ofVideoGrabber vidGrabber;
		#else
		ofVideoPlayer vidPlayer;
		#endif

		/* ARToolKitPlus class */	
		ofxARToolkitPlus artk;	
		int threshold;
	
		/* OpenCV images */
		ofxCvColorImage colorImage;
		ofxCvGrayscaleImage grayImage;
		ofxCvGrayscaleImage	grayThres;
	
		/* Image to distort on to the marker */
		ofImage displayImage;

		/* The four corners of the image */
		vector<ofPoint> displayImageCorners;

		/* Load model */
		//ofx3DModelLoader capModel;
		//ofx3DModelLoader squirrelModel;

		// get Matrix4x4 and write to file
		/*void getMatrixToFile(ofMatrix4x4 &m);*/

		// Image back card
		ofImage cardBackImage;

};

#endif
