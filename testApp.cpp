#include "testApp.h"

int markerIDArray[10] = {0,1,2,3,4,5,6,7,8,9};
//int markerIDArray[10] = {10,11,12,13,14,15,16,17,18,19};
//int markerIDArray[10] = {20,21,22,23,24,25,26,27,28,29};
//int markerIDArray[10] = {22,23,24,25,26,27,28,29,30,31};

//--------------------------------------------------------------
void testApp::setup(){
	width = 800;
	height = 600;

	gameState = 0; // ready to game start
	//glutInitDisplayMode(GLUT_DEPTH);
	vidGrabber.setVerbose(1); // ทับซ้อนกันได้

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
	
	//// Load the image we are going to distort
	//displayImage.loadImage("of.jpg");
	//// Load the corners of the image into the vector
	//int displayImageHalfWidth = displayImage.width / 2;
	//int displayImageHalfHeight = displayImage.height / 2;	
	//displayImageCorners.push_back(ofPoint(0, 0));
	//displayImageCorners.push_back(ofPoint(displayImage.width, 0));
	//displayImageCorners.push_back(ofPoint(displayImage.width, displayImage.height));
	//displayImageCorners.push_back(ofPoint(0, displayImage.height));


	// Load image card backing
	cardBackImage.loadImage("card/336px-BackVG-DOR.png");
	cardBackImage.mirror(1,0); //rotate x
	
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
		//colorImage.mirror(0,1);
		#else
		colorImage.setFromPixels(vidPlayer.getPixels(), width, height);
		#endif
		
		//colorImage.mirror(0,1);
		// convert our camera image to grayscale
		grayImage = colorImage;
		
		// apply a threshold so we can see what is going on
		grayThres = grayImage;
		grayThres.threshold(threshold);
		
		// Pass in the new image pixels to artk
		artk.update(grayImage.getPixels());
		//artk.update(vidGrabber.getPixels());
		
	}
	

	
}

//float testApp::findHueInArea(cv::i &input, ofPoint input_point, int radius)
//{
//        cv::Rect roi_rect = cv::Rect((input_point.x-radius,input_point.x+radius), (input_point.y-radius,input_point.y+radius), radius, radius);
//        cv::Mat temp = input(roi_rect);
//        std::vector<cv::Mat> imgHSV;
//        cv::split(temp, imgHSV);
//        float meanHue = cv::mean(imgHSV[0])[0];
//
//        return meanHue;
//}


//--------------------------------------------------------------
void testApp::draw(){
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glEnable (GL_DEPTH_TEST);

	// Main image
	//ofSetColor(255,255,255);
	//grayImage.draw(0, 0);
	//colorImage.draw(0, 0);
	//ofSetColor(102,102,102);	
	
	// Threshold image
	ofSetColor(255,255,255);
	//grayThres.draw(640, 0);
	//grayThres.mirror(0,1);
	grayThres.draw(0, 0);
	//cardBackImage.draw(0,500,70,100);

	//ofEnableAlphaBlending();    // turn on alpha blending
	ofSetColor(255,0,0);
	ofDrawBitmapString(ofToString(artk.getNumDetectedMarkers()) + " marker(s) found", 10, 20);
	ofDrawBitmapString("Game State: " + ofToString(gameState), 500, 20);
	ofDrawBitmapString("Threshold: " + ofToString(threshold), 10, 40);
	ofDrawBitmapString("Use the Up/Down keys to adjust the threshold", 250, 40);
	ofDrawBitmapString("Near" + ofToString(nearIndex), 10, 60);

	//ofFill();
	//ofEnableAlphaBlending();    // turn on alpha blending
	//ofSetColor(255,0,0,127);    // red, 50% transparent
	//ofRect(20,20,100,100);      // draws the rect with alpha
	//ofDisableAlphaBlending();   // turn off alpha
	//ofRect(120,20,100,100); // draws the rect without alpha

	// ARTK draw
	// An easy was to see what is going on
	// Draws the marker location and id number
	artk.draw(0,0);
	
	// ARTK 2D stuff
	// See if marker ID '0' was detected
	// and draw blue corners on that marker only
	//int myIndex = artk.getMarkerIndex(36);
	//if(myIndex >= 0) {	
	//	// Get the corners
	//	vector<ofPoint> corners;
	//	//artk.getDetectedMarkerBorderCorners(myIndex, corners);
	//	// Can also get the center like this:
	//	//ofPoint center = artk.getDetectedMarkerCenter(myIndex);
	//	ofSetColor(0,0,255);
	//	for(int i=0;i<corners.size();i++) 
	//	{
	//		ofCircle(corners[i].x, corners[i].y, 10);
	//	}
	//}
	
	//// Homography
	//// Here we feed in the corners of an image and get back a homography matrix
	//ofMatrix4x4 homo = artk.getHomography(myIndex, displayImageCorners);
	//// We apply the matrix and then can draw the image distorted on to the marker
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
	int ID;
	int mIndex;


	
	if(gameState==0)
	{
		//cout<<" Start gameState 0 "<<endl;
		for(int i=0; i<numDetected; i++)
		{
			//cout<<"i = "<<i<<endl;
			ID = artk.getMarkerID(i); // get [MarkerID] from current [MakerIndex] for identify each Maker
			mIndex = artk.getMarkerIndex(ID); // get [MakerIndex] from current [MarkerID] for draw graphic on MarkerIndex
			//cout<<"ID = "<<ID<<endl;
			artk.applyModelMatrix(mIndex); // input = marker index as want to draw graphic **not markerID**
			//cout<<"Center = "<<artk.getDetectedMarkerCenter(mIndex); // show center of marker
			drawAR(ID); // draw object on marker

			mm1 = artk.getMatrix(mIndex);
			mm2 = artk.getGLMatrix(mIndex);
			matrixTrans[ID] = artk.getTranslation(mIndex);
			cardFieldCenter = matrixTrans[0];
			updateCardFieldPosition(matrixTrans[0]);

			// if found [Card Field]'s marker then display drawing field object
			if(artk.getMarkerID(i)==markerIDArray[0])
			{					
				// change game state
				gameState = 1;
				cout<<" gameState = 1 : found card field marker"<<endl;
			}
		}
	}
	else if(gameState==1)
	{
		//cout<<" Start gameState 1 "<<endl;
		for(int i=0; i<numDetected; i++)
		{
			//cout<<"i = "<<i<<endl;
			ID = artk.getMarkerID(i); // get [MarkerID] from current [MakerIndex] for identify each Maker
			mIndex = artk.getMarkerIndex(ID); // get [MakerIndex] from current [MarkerID] for draw graphic on MarkerIndex
			//cout<<"ID = "<<ID<<endl;
			artk.applyModelMatrix(mIndex); // input = marker index as want to draw graphic **not markerID**
			//cout<<"Center = "<<artk.getDetectedMarkerCenter(mIndex); // show center of marker
			drawAR(ID); // draw object on marker
	
			mm1 = artk.getMatrix(mIndex);
			mm2 = artk.getGLMatrix(mIndex);
			matrixTrans[ID] = artk.getTranslation(mIndex);
			cardFieldCenter = matrixTrans[0];
			updateCardFieldPosition(matrixTrans[0]);

			if(ID!=0)
			{
				cout<<endl<<ofToString(this->calDistance(this->cardFieldPos[1],this->matrixTrans[ID]))<<endl;
				nearIndex = this->findNearestFieldAndMaker(artk.getTranslation(mIndex));
			}

			// if player 1 set card done
			if(artk.getMarkerID(i)==markerIDArray[1])
			{
				// change game state
				gameState = 2;
				cout<<" gameState = 2 : player 1 set card done"<<endl;
			}
		}
	}
	else if(gameState==2)
	{
		//cout<<" Start gameState 2 "<<endl;
		for(int i=0; i<numDetected; i++)
		{
			//cout<<"i = "<<i<<endl;
			ID = artk.getMarkerID(i); // get [MarkerID] from current [MakerIndex] for identify each Maker
			mIndex = artk.getMarkerIndex(ID); // get [MakerIndex] from current [MarkerID] for draw graphic on MarkerIndex
			//cout<<"ID = "<<ID<<endl;
			artk.applyModelMatrix(mIndex); // input = marker index as want to draw graphic **not markerID**
			//cout<<"Center = "<<artk.getDetectedMarkerCenter(mIndex)<<endl; // show center of marker
			drawAR(ID); // draw object on marker

			mm1 = artk.getMatrix(mIndex);
			mm2 = artk.getGLMatrix(mIndex);
			matrixTrans[ID] = artk.getTranslation(mIndex);
			cardFieldCenter = matrixTrans[0];
			updateCardFieldPosition(matrixTrans[0]);

			if(ID!=0)
			{
				cout<<endl<<ofToString(this->calDistance(this->cardFieldPos[1],this->matrixTrans[ID]))<<endl;
				nearIndex = this->findNearestFieldAndMaker(artk.getTranslation(mIndex));
			}

			// if player 2 set card done
			//if(artk.getMarkerID(i)==markerIDArray[2])
			//{
			//	// change game state
			//	gameState = 3;
			//	cout<<" gameState = 3 : player 3 set card done"<<endl;
			//}
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
	if(key == 'h') {
		//getMatrixToFile(mm1);
		cout<<"Matrix = "<<endl<<mm1<<endl;
	}
	if(key == 'g'){
		cout<<"MatrixGL = "<<endl<<mm2<<endl;
	}
	if(key == 'z'){
		cout<<"cardFieldPos = "<<endl<<cardFieldPos[0]<<endl;
	}
	if(key == 'q'){
		cout<<"mm3 = "<<endl<<mm3<<endl;
	}
	if(key == 'w'){
		cout<<"mm4 = "<<endl<<mm4<<endl;
	}
	if(key == 'x'){
		cout<<"matrixTrans = "<<endl<<matrixTrans[0]<<endl;
	}
	if(key == 'c'){
		cout<<"cardFieldCenter = "<<endl<<cardFieldCenter<<endl;
	}
}

/* //--------------------------------------------------------------
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

} */


//--------------------- draw graphic on marker -----------------
void testApp::drawAR(int markerID){
	if(markerID==markerIDArray[0])
	{
		glPushMatrix();
			ofSetLineWidth(5);
			ofNoFill();		
			ofEnableSmoothing();
			ofEnableAlphaBlending();    // turn on alpha blending
			ofSetColor(255,0,255,127);    // pink, 50% transparent
			ofRect(-75, -75, 150, 150);

			ofSetColor(255, 0, 0, 127);
			ofRect(25, -75, 50, 50);
			ofSetColor(0, 255, 0, 127);
			ofRect(25, -25, 50, 50);
			ofSetColor(0, 0, 255, 127);
			ofRect(25, 25, 50, 50);
			
			ofSetColor(255, 0, 0, 127);
			ofRect(-75, -75, 50, 50);
			ofSetColor(0, 255, 0, 127);
			ofRect(-75, -25, 50, 50);
			ofSetColor(0, 0, 255, 127);
			ofRect(-75, 25, 50, 50);
			ofDisableAlphaBlending();   // turn off alpha

			ofSetColor(255, 255, 255);
			cardBackImage.draw(-25,-25,50,50);	
			glPushMatrix();
				ofSetColor(255, 0, 255);
				glScalef(0.5,0.5,0.5);
				glTranslatef(-40,10,0);
				glRotatef(180 ,1 ,0 ,0 );
				ofDrawBitmapString("Card Field",0 , 0);
			glPopMatrix();
			//glTranslatef(75,75,0);
			
		glPopMatrix();		
	}
	else if(markerID==markerIDArray[1])
	{
		glPushMatrix();	
			ofSetLineWidth(5);
			ofNoFill();
			ofSetColor(255, 255, 255);
			//glTranslatef(0,0,50);
			cardBackImage.draw(-25,-25,50,50);
			ofSetColor(255, 0, 0);
			glPushMatrix();
				glScalef(0.5,0.5,0.5);
				glTranslatef(-40,10,0);
				glRotatef(180 ,1 ,0 ,0 );
				ofDrawBitmapString("Card No.1\nCard Back",0 , 0);
			glPopMatrix();
		glPopMatrix();
	}	
	else if(markerID==markerIDArray[2])
	{
		glPushMatrix();
			ofSetLineWidth(5);
			ofNoFill();
			ofSetColor(255, 0, 0);
			glScalef(0.5,0.5,0.5);
			glTranslatef(-40,10,0);
			glRotatef(180 ,1 ,0 ,0 );
			ofDrawBitmapString("Card No.2",0 , 0);
		glPopMatrix();
	}
	/*
	else if(markerID==markerIDArray[3])
	{
		
	}
	else if(markerID==markerIDArray[4])
	{
		
	}
	else if(markerID==markerIDArray[5])
	{
		
	}
	else if(markerID==markerIDArray[6])
	{
		
	}
	else if(markerID==markerIDArray[7])
	{
		
	}
	else if(markerID==markerIDArray[8])
	{
		
	}
	else if(markerID==markerIDArray[9])
	{
		
	}
	*/

	// draw marker's matrix
	glPushMatrix();
		ofSetLineWidth(4);
		ofNoFill();
		ofSetColor(100, 100, 100);
		glScalef(0.4,0.4,0.4);
		glTranslatef(-20,0,0);
		glRotatef(180 ,1 ,0 ,0 );
		ofDrawBitmapString(ofToString(matrixTrans[markerID][0]) + "\n" + ofToString(matrixTrans[markerID][1]) + "\n" + ofToString(matrixTrans[markerID][2]),0 , 0);
	glPopMatrix();
}

//--------------------------------------------------------------
float testApp::calDistance(ofPoint p1,ofPoint p2){

	return abs((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

//--------------------------------------------------------------
void testApp::updateCardFieldPosition(ofPoint mTrans){
	cardFieldPos[0] = mTrans;
	
	cardFieldPos[2] = ofPoint(cardFieldPos[0].x-50,cardFieldPos[0].y,cardFieldPos[0].z);
	cardFieldPos[1] = ofPoint(cardFieldPos[0].x-50,cardFieldPos[0].y-50,cardFieldPos[0].z);
	cardFieldPos[3] = ofPoint(cardFieldPos[0].x-50,cardFieldPos[0].y+50,cardFieldPos[0].z);

	cardFieldPos[5] = ofPoint(cardFieldPos[0].x+50,cardFieldPos[0].y,cardFieldPos[0].z);
	cardFieldPos[4] = ofPoint(cardFieldPos[0].x+50,cardFieldPos[0].y-50,cardFieldPos[0].z);
	cardFieldPos[6] = ofPoint(cardFieldPos[0].x+50,cardFieldPos[0].y+50,cardFieldPos[0].z);
}

//--------------------------------------------------------------
int testApp::findNearestFieldAndMaker(ofPoint pMarker){

	float nearest1 = 9999999;
	float nearest2 = 0;
	int index = 0;

	for(int i=0;i<7;i++)
	{
		nearest2 = calDistance(cardFieldPos[i],pMarker);
		if(nearest2<nearest1)
		{
			nearest1 = nearest2;
			index = i;
		}
	}

	return index;
}