#include "testApp.h"

//GLfloat lightOnePosition[] = {40.0, 40, 100.0, 0.0};
//GLfloat lightOneColor[] = {0.99, 0.99, 0.99, 1.0};
//
//GLfloat lightTwoPosition[] = {-40.0, 40, 100.0, 0.0};
//GLfloat lightTwoColor[] = {0.99, 0.99, 0.99, 1.0};

//--------------------------------------------------------------
void testApp::setup(){
	width = 640;
	height = 480;

	gameState = 0; // ready to game start
	vidGrabber.setVerbose(true); // �Ѻ��͹�ѹ��

	// Print the markers from the "AllBchThinMarkers.png" file in the data folder
	#ifdef CAMERA_CONNECTED
	vidGrabber.initGrabber(width, height);
	#else
	vidPlayer.loadMovie("marker.mov");
	vidPlayer.play();	
	#endif
	
	colorImage.allocate(width, height); // RGB video
	grayImage.allocate(width, height); // gray video
	grayThres.allocate(width, height); // threshold video
	
	// Load the image we are going to distort
	displayImage.loadImage("of.jpg");
	// Load the corners of the image into the vector
	int displayImageHalfWidth = displayImage.width / 2;
	int displayImageHalfHeight = displayImage.height / 2;	
	displayImageCorners.push_back(ofPoint(0, 0));
	displayImageCorners.push_back(ofPoint(displayImage.width, 0));
	displayImageCorners.push_back(ofPoint(displayImage.width, displayImage.height));
	displayImageCorners.push_back(ofPoint(0, displayImage.height));	
	
	// This uses the default camera calibration and marker file
	artk.setup(width, height);

	// The camera calibration file can be created using GML:
	// http://graphics.cs.msu.ru/en/science/research/calibration/cpp
	// and these instructions:
	// http://studierstube.icg.tu-graz.ac.at/doc/pdf/Stb_CamCal.pdf
	// This only needs to be done once and will aid with detection
	// for the specific camera you are using
	// Put that file in the data folder and then call setup like so:
	// artk.setup(width, height, "myCamParamFile.cal", "markerboard_480-499.cfg");
	
	// Set the threshold
	// ARTK+ does the thresholding for us
	// We also do it in OpenCV so we can see what it looks like for debugging
	threshold = 85;
	artk.setThreshold(threshold);

	ofBackground(127,127,127);

	
	/* ================================== Load ModeL ================================= */
	
	
	//ofSetVerticalSync(true);
	
	//some model / light stuff
    //glEnable (GL_DEPTH_TEST);
    //glShadeModel (GL_SMOOTH);

    /* initialize lighting */
    //glLightfv (GL_LIGHT0, GL_POSITION, lightOnePosition);
    //glLightfv (GL_LIGHT0, GL_DIFFUSE, lightOneColor);
    //glEnable (GL_LIGHT0);
    //glLightfv (GL_LIGHT1, GL_POSITION, lightTwoPosition);
    //glLightfv (GL_LIGHT1, GL_DIFFUSE, lightTwoColor);
    //glEnable (GL_LIGHT1);
    //glEnable (GL_LIGHTING);
    //glColorMaterial (GL_FRONT_AND_BACK, GL_DIFFUSE);
    //glEnable (GL_COLOR_MATERIAL);
	
    //load the squirrel model - the 3ds and the texture file need to be in the same folder
	//squirrelModel.loadModel("squirrel/NewSquirrel.3ds", 5);
	//capModel.loadModel("squirrel/cap22.3ds", 5);

    //you can create as many rotations as you want
    //choose which axis you want it to effect
    //you can update these rotations later on
	//squirrelModel.setScale(0.9, 0.9, 0.9);
    
	//squirrelModel.setRotation(1, 270, 0, 1, 0);
	//squirrelModel.setPosition(0.0, 0.0, 0.0);
	//capModel.setPosition(0.0, 0.0, 0.0);

}

//--------------------------------------------------------------
void testApp::update(){
	#ifdef CAMERA_CONNECTED
	//vidGrabber.initGrabber(width, height);
	vidGrabber.grabFrame();
	bool bNewFrame = vidGrabber.isFrameNew();
	#else
	vidPlayer.idleMovie();
	bool bNewFrame = vidPlayer.isFrameNew();
	#endif
	
	if(bNewFrame) {
		
		#ifdef CAMERA_CONNECTED
		colorImage.setFromPixels(vidGrabber.getPixels(), width, height);
		#else
		colorImage.setFromPixels(vidPlayer.getPixels(), width, height);
		#endif
		
		// convert our camera image to grayscale
		grayImage = colorImage;
		
		// apply a threshold so we can see what is going on
		grayThres = grayImage;
		grayThres.threshold(threshold);
		
		// Pass in the new image pixels to artk
		artk.update(grayImage.getPixels());
		artk.update(vidGrabber.getPixels());
		
	}
	

	
}

//--------------------------------------------------------------
void testApp::drawAR(int markerID){
	if(markerID==10)
	{
		glPushMatrix();
			ofSetLineWidth(5);
			ofNoFill();
			ofEnableSmoothing();
			ofSetColor(255, 0, 255);
			glPushMatrix();
				glTranslatef(-20,10,0);
				glRotatef(180 ,1 ,0 ,0 );
				ofDrawBitmapString("Card Field",0 , 0);
			glPopMatrix();
			glTranslatef(75,75,0);
			ofRect(-150, -150, 150, 150);
		glPopMatrix();		
	}
	else if(markerID==11)
	{
		glPushMatrix();	
			ofSetLineWidth(5);
			ofNoFill();
			ofSetColor(255, 0, 0);
			glPushMatrix();
				glTranslatef(-20,10,0);
				glRotatef(180 ,1 ,0 ,0 );
				ofDrawBitmapString("Card No.1",0 , 0);
			glPopMatrix();
		glPopMatrix();
	}	
	else if(markerID==12)
	{
		glPushMatrix();
			ofSetLineWidth(5);
			ofNoFill();
			ofSetColor(255, 0, 0);
			glTranslatef(-20,10,0);
			glRotatef(180 ,1 ,0 ,0 );
			ofDrawBitmapString("Card No.2",0 , 0);
		glPopMatrix();
	}
	/*
	else if(markerID==3)
	{
		
	}
	else if(markerID==4)
	{
		
	}
	else if(markerID==5)
	{
		
	}
	else if(markerID==6)
	{
		
	}
	else if(markerID==7)
	{
		
	}
	else if(markerID==8)
	{
		
	}
	else if(markerID==9)
	{
		
	}
	*/
}

//--------------------------------------------------------------
void testApp::draw(){

	//glEnable (GL_DEPTH_TEST);

	// Main image
	ofSetColor(255,255,255);
	//grayImage.draw(0, 0);
	colorImage.draw(0, 0);
	ofSetColor(102,102,102);	
	ofDrawBitmapString(ofToString(artk.getNumDetectedMarkers()) + " marker(s) found", 10, 20);

	// Threshold image
	ofSetColor(255,255,255);
	grayThres.draw(640, 0);
	ofSetColor(102,102,102);	
	ofDrawBitmapString("Threshold: " + ofToString(threshold), 650, 20);
	ofDrawBitmapString("Use the Up/Down keys to adjust the threshold", 650, 40);
	


	// ARTK draw
	// An easy was to see what is going on
	// Draws the marker location and id number
	artk.draw(640,0);
	
	// ARTK 2D stuff
	// See if marker ID '0' was detected
	// and draw blue corners on that marker only
	int myIndex = artk.getMarkerIndex(36);
	if(myIndex >= 0) {	
		// Get the corners
		vector<ofPoint> corners;
		//artk.getDetectedMarkerBorderCorners(myIndex, corners);
		// Can also get the center like this:
		//ofPoint center = artk.getDetectedMarkerCenter(myIndex);
		ofSetColor(0,0,255);
		for(int i=0;i<corners.size();i++) 
		{
			ofCircle(corners[i].x, corners[i].y, 10);
		}
	}
	
	// Homography
	// Here we feed in the corners of an image and get back a homography matrix
	//ofMatrix4x4 homo = artk.getHomography(myIndex, displayImageCorners);

	// We apply the matrix and then can draw the image distorted on to the marker
	//ofPushMatrix();
	//	glMultMatrixf(homo.getPtr());
	//	ofSetColor(255,255,255);
	//	displayImage.draw(0, 0);
	//ofPopMatrix();
	
	
	// ARTK 3D stuff
	// This is another way of drawing objects aligned with the marker
	// First apply the projection matrix once
	artk.applyProjectionMatrix();

	// Find out how many markers have been detected
	int numDetected = artk.getNumDetectedMarkers();
	//ofFill();
	//ofEnableAlphaBlending();    // turn on alpha blending
	//ofSetColor(255,0,0,127);    // red, 50% transparent
	//ofRect(20,20,100,100);      // draws the rect with alpha
	//ofDisableAlphaBlending();   // turn off alpha
	//ofRect(120,20,100,100); // draws the rect without alpha
	
	if(gameState==0)
	{
		for(int i=0; i<numDetected; i++)
		{
			// if found [Card Field]'s marker then display drawing field object
			if(artk.getMarkerID(i)==10)
			{
				// draw object on marker
				drawAR(10);
								
				// change game state
				gameState = 1;
				cout<<" gameState = 1 : found card field marker"<<endl;
			}
		}
	}
	else if(gameState==1)
	{
		for(int i=0; i<numDetected; i++)
		{
			// if found [Card Field]'s marker then display drawing field object
			if(artk.getMarkerID(i)==10)
			{
				// draw object on marker
				drawAR(10);

			}
			
			// if player 1 set card done
			if(artk.getMarkerID(i)==11)
			{
				// draw object on marker
				drawAR(11);
				
				// change game state
				gameState = 2;
				cout<<" gameState = 2 : player 1 set card done"<<endl;
			}
		}
	}
	else if(gameState==2)
	{
		for(int i=0; i<numDetected; i++)
		{
			//// if found [Card Field]'s marker then display drawing field object
			//if(artk.getMarkerID(i)==0)
			//{
			//	// draw object on marker
			//	drawAR(i);

			//}

			//// if player 2 set card done
			//if(artk.getMarkerID(i)==1)
			//{
			//	// draw object on marker
			//	drawAR(i);

			//	// change game state
			//	//gameState = 3;
			//	//cout<<" gameState = 3 : player 3 set card done"<<endl;
			//}
			drawAR(i);

		}
	}

	/*
	else if(gameState==3)
	{
		for(int i=0; i<numDetected; i++)
		{
			
		}
	}
	*/

	
	
	
	
	
	
	
	
	
	
	
	/*

	// Draw for each marker discovered
	for(int i=0; i<numDetected; i++) 
	{
		// Set the matrix to the perspective of this marker
		// The origin is in the middle of the marker	
		artk.applyModelMatrix(i);

		
			// Draw a line from the center out
			ofNoFill();
			ofSetLineWidth(5);
			ofSetColor(255,0,0); // red
			glBegin(GL_LINES);
				glVertex3f(0, 0, 0); 
				glVertex3f(0, 0, 50);
			glEnd();




		

		
		// Draw a stack of rectangles by offseting on the z axis
		//ofNoFill();
		//ofEnableSmoothing();
		//ofSetColor(255, 255, 0, 50);	
		//for(int i=0; i<5; i++) 
		//{		
		//	ofRect(-25, -25, 50, 50);
		//	ofTranslate(0, 0, i*1);
		//}

	}
*/
	//glDisable (GL_DEPTH_TEST);
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == OF_KEY_UP) {
		artk.setThreshold(++threshold);
		
	} else if(key == OF_KEY_DOWN) {
		artk.setThreshold(--threshold);		
	}
	#ifdef CAMERA_CONNECTED
	if(key == 's') {
		vidGrabber.videoSettings();
	}
	#endif
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



