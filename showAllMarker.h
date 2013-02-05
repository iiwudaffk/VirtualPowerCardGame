#ifndef _SHOW_ALL_MARKER_
#define _SHOW_ALL_MARKER_

#include "ofxOpenCv.h"
#include "ofxARToolkitPlus.h"
#include "ofVectorMath.h"
#include "ofx3DModelLoader.h"
#include "ofMain.h"

#include "glut.h"

// Uncomment this to use a camera instead of a video file
#define CAMERA_CONNECTED

class showAllMarker : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		
		// draw graphic object static on marker
		void drawAR(int markerIndex);
		
		// draw graphic effect
		void drawEffect(int markerIndex);
		
		// calculate distance between 2 marker
		float calDistance(ofPoint markerIndex1,ofPoint markerIndex2);

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
	
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
		ofx3DModelLoader capModel;
		ofx3DModelLoader squirrelModel;
};

#endif
