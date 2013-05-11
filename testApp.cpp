#include "testApp.h"
GLfloat lightOnePosition[] = {40.0, 40, 100.0, 0.0};
GLfloat lightOneColor[] = {0.99, 0.99, 0.99, 1.0};

GLfloat lightTwoPosition[] = {-40.0, 40, 100.0, 0.0};
GLfloat lightTwoColor[] = {0.99, 0.99, 0.99, 1.0};

//--------------------------------------------------------------
void testApp::setup(){
	pict=true;
	wt = 0;
	it = 999;
	runtime = false;
	mIDcField = 0;
	mIDcBack = mIDscBack = 1;
	mIDcAtkFront = 9;
	mw = mh = 50.0;

	gameState = 0; // ready to game start

	//PL.setTurn(1); // first play
	//PR.setTurn(0); // second play

	// setup hp bar
	plDis.setFromCenter(ofPoint(0 + 100.0/2.0,height - 100.0/2.0),100.0,100.0);
	prDis.setFromCenter(ofPoint(width - 100.0/2.0,height - 100.0/2.0),100.0,100.0);
	
	// setup all character cards
	c1.setCName("Dark Magician");
	c1.setmIDBack(1);
	c1.setmIDFront(2);
	c1.setATK(40);
	c1.setDEF(20);
	float r1[10] = {0.5, 0.5, 0.5, 1.0, 1.0, 1.0, 1.0, 1.5, 1.5, 2.0};
	c1.setAtkRate(r1);

	c2.setCName("Twinhead Dragon");
	c2.setmIDBack(3);
	c2.setmIDFront(4);
	c2.setATK(35);
	c2.setDEF(25);
	float r2[10] = {0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.5, 1.5, 2.0};
	c2.setAtkRate(r2);

	c3.setCName("Dragon Knight");
	c3.setmIDBack(5);
	c3.setmIDFront(6);
	c3.setATK(30);
	c3.setDEF(40);
	float r3[10] = {0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.5, 1.5, 1.5, 2.0};
	c3.setAtkRate(r3);

	c4.setCName("Elf of Light");
	c4.setmIDBack(1);
	c4.setmIDFront(7);
	c4.setATK(20);
	c4.setDEF(30);
	float r4[10] = {0.5, 1.0, 1.0, 1.5, 1.5, 1.5, 1.5, 2.0, 2.0, 2.0};
	c4.setAtkRate(r4);

	c5.setCName("Skull Devil");
	c5.setmIDBack(1);
	c5.setmIDFront(8);
	c5.setATK(50);
	c5.setDEF(10);
	float r5[10] = {0.5, 0.5, 0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.5, 2.0};
	c5.setAtkRate(r5);

	mIDcFront.push_back(c1.cmIdFront());
	mIDcFront.push_back(c2.cmIdFront());
	mIDcFront.push_back(c3.cmIdFront());
	mIDcFront.push_back(c4.cmIdFront());
	mIDcFront.push_back(c5.cmIdFront());

	clist.push_back(c1);
	clist.push_back(c2);
	clist.push_back(c3);
	clist.push_back(c4);
	clist.push_back(c5);
	
	// setup all support cards
	sc1.setCName("Defence Fail");
	sc1.setmIDBack(1);
	sc1.setmIDFront(11);

	sc2.setCName("Defence Full Power");
	sc2.setmIDBack(1);
	sc2.setmIDFront(12);

	sc3.setCName("Dodge");
	sc3.setmIDBack(1);
	sc3.setmIDFront(13);

	sc4.setCName("Return Attack");
	sc4.setmIDBack(1);
	sc4.setmIDFront(14);

	sclist.push_back(sc1);
	sclist.push_back(sc2);
	sclist.push_back(sc3);
	sclist.push_back(sc4);

	mIDscFront.push_back(sc1.cmIdFront());
	mIDscFront.push_back(sc2.cmIdFront());
	mIDscFront.push_back(sc3.cmIdFront());
	mIDscFront.push_back(sc4.cmIdFront());

	delete r1,r2,r3,r4,r5;

	width = 800;	height = 600;

	//glutInitDisplayMode(GLUT_DEPTH);
	vidGrabber.setVerbose(true); // ทับซ้อนกันได้

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
	
	// Load image card backing
	cardBackImage.loadImage("card/336px-BackVG-DOR.png");
	cardBackImage.mirror(1,0); //rotate x
	cardFieldImage.loadImage("card/331px-Back-Anime-ZX-2.png");
	cardFieldImage.mirror(1,0); //rotate x

	// Load true type font
	//myFont.loadFont();
	
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
	threshold = 85; // normal=85, lightless=40, dark=0
	artk.setThreshold(threshold);

	ofBackground(127,127,127);

	
	/* ================================== Load ModeL ================================= */
	
	ofBackground(255,255,255);
		
	ofSetVerticalSync(true);

    //some model / light stuff
    glEnable (GL_DEPTH_TEST);
    glShadeModel (GL_SMOOTH);

    /* initialize lighting */
    //glLightfv (GL_LIGHT0, GL_POSITION, lightOnePosition);
    //glLightfv (GL_LIGHT0, GL_DIFFUSE, lightOneColor);
    //glEnable (GL_LIGHT0);
    //glLightfv (GL_LIGHT1, GL_POSITION, lightTwoPosition);
    //glLightfv (GL_LIGHT1, GL_DIFFUSE, lightTwoColor);
    //glEnable (GL_LIGHT1);
    //glEnable (GL_LIGHTING);
    glColorMaterial (GL_FRONT_AND_BACK, GL_DIFFUSE);
    glEnable (GL_COLOR_MATERIAL);

	mAss.loadModel("squirrel/Altair Model/altair.3ds",0.8);
	mAss.setPosition(0.0, 0.0, 0.0);
	mAss.setRotation(1,90,1,0,0);
	mAss.setPosition(0.0, 0.0, 50.0);
	
}

//--------------------------------------------------------------
void testApp::update(){
	#ifdef CAMERA_CONNECTED
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
	
	if(runtime)
	{wt++;}
	
	if(wt>=it)
	{runtime=false;wt=0;it=999;}
}

//--------------------------------------------------------------
void testApp::draw(){
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glEnable (GL_DEPTH_TEST);

	if(pict)
	{
		// Threshold image
		ofSetColor(255,255,255);
		grayThres.draw(0, 0);
	}else
	{
		// Main image
		ofSetColor(255,255,255);
		//grayImage.draw(0, 0);
		colorImage.draw(0, 0);
	}
	
	//ofEnableAlphaBlending();    // turn on alpha blending
	ofSetColor(255,0,0);
	ofDrawBitmapString(ofToString(artk.getNumDetectedMarkers()) + " marker(s) found", 10, 20);
	ofDrawBitmapString("Game State: " + ofToString(gameState), 500, 20);
	ofDrawBitmapString("Threshold: " + ofToString(threshold), 10, 40);
	ofDrawBitmapString("Use the Up/Down keys to adjust the threshold", 250, 40);
	ofDrawBitmapString("Near : " + ofToString(nearField), 10, 60);
	ofDrawBitmapString("Field 0 : " + ofToString(f1.getMarkerIDsetted(0)), 10, 80);
	ofDrawBitmapString("Field 1 : " + ofToString(f1.getMarkerIDsetted(1)), 10, 100);
	ofDrawBitmapString("Field 2 : " + ofToString(f1.getMarkerIDsetted(2)), 10, 120);
	ofDrawBitmapString("Field 3 : " + ofToString(f1.getMarkerIDsetted(3)), 10, 140);
	ofDrawBitmapString("Field 4 : " + ofToString(f1.getMarkerIDsetted(4)), 10, 160);
	ofDrawBitmapString("Field 5 : " + ofToString(f1.getMarkerIDsetted(5)), 10, 180);
	ofDrawBitmapString("Field 6 : " + ofToString(f1.getMarkerIDsetted(6)), 10, 200);
	ofDrawBitmapString("Field 7 : " + ofToString(f1.getMarkerIDsetted(7)), 10, 220);
	ofDrawBitmapString("Field 8 : " + ofToString(f1.getMarkerIDsetted(8)), 10, 240);
	ofDrawBitmapString("Wait Time : " + ofToString(wt), 10, 260);
	ofDrawBitmapString("input Time : " + ofToString(it), 10, 280);
	ofDrawBitmapString("Run Time : " + ofToString(runtime), 10, 300);

	ofDrawBitmapString("P1 HP : " + ofToString(PL.hp()), 700, 20);
	ofDrawBitmapString("P1 Life : " + ofToString(PL.isAlive()), 700, 40);
	ofDrawBitmapString("P1 Turn : " + ofToString(PL.isTurn()), 700, 60);

	ofDrawBitmapString("P2 HP : " + ofToString(PR.hp()), 700, 100);
	ofDrawBitmapString("P2 Life : " + ofToString(PR.isAlive()), 700, 120);
	ofDrawBitmapString("P2 Turn : " + ofToString(PR.isTurn()), 700, 140);

	ofSetLineWidth(5);
	ofNoFill();	
	ofEnableAlphaBlending();    // turn on alpha blending
	ofSetColor(255, 0, 0, 235);
	ofRect(ofPoint(0,500),100,100);
	ofSetColor(0, 0, 255, 235);
	ofRect(ofPoint(700,500),100,100);

	// draw hp bar
	ofSetLineWidth(1);
	ofFill();
	glBegin(GL_POLYGON);
	ofSetColor(255, 0, 0, 190);
	glVertex3f(100,height - 20,0);
	ofSetColor(255, 0, 0, 190);
	glVertex3f(100,width,0);
	ofSetColor(0, 255, 0, 190);
	glVertex3f(width/2.0,width,0);
	ofSetColor(0, 255, 0, 190);
	glVertex3f(width/2.0,height - 20,0);
	glEnd();

	glBegin(GL_POLYGON);
	ofFill();
	ofSetColor(255, 0, 0, 190);
	glVertex3f(width - 100,height - 20,0);
	ofSetColor(255, 0, 0, 190);
	glVertex3f(width - 100,width,0);
	ofSetColor(0, 255, 0, 190);
	glVertex3f(width/2.0,width,0);
	ofSetColor(0, 255, 0, 190);
	glVertex3f(width/2.0,height - 20,0);
	glEnd();

	// draw hp slot
	ofSetLineWidth(3);
	ofNoFill();
	glBegin(GL_LINE_LOOP);
	ofSetColor(255, 0, 0, 235);
	glVertex3f(100,height - 20,0);
	glVertex3f(100,width - 2,0);
	glVertex3f(width/2.0 - 1,width - 2,0);
	glVertex3f(width/2.0 - 1,height - 20,0);
	glVertex3f(100,580,0);
	glEnd();

	glBegin(GL_LINE_LOOP);
	ofNoFill();
	ofSetColor(0, 0, 255, 235);
	glVertex3f(width - 100,height - 20,0);
	glVertex3f(width - 100,width - 2,0);
	glVertex3f(width/2.0 + 1,width - 2,0);
	glVertex3f(width/2.0 + 1,height - 20,0);
	glVertex3f(width - 100,height - 20,0);
	glEnd();
	
	ofDisableAlphaBlending();   // turn off alpha


	
	

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
	
	// 0 = open program first time ,
	// wait: found field card => 1
	if(gameState==0)
	{
		mID.clear();
		mTrans.clear();
		for(int i=0; i<numDetected; i++)
		{
			// get [MarkerID] from current [MakerIndex[i]] for identify each Maker
			mID.push_back(artk.getMarkerID(i));
			// get [Marker Translation] from current [MakerIndex[i]]
			mTrans.push_back(artk.getTranslation(i));
		}
		for(int i=0; i<mID.size(); i++)
		{
			drawAR(mID[i],i); // draw object on marker

			// if found [Card Field]'s marker then display drawing field object
			if(mID[i]==mIDcField)
			{	
				f1.updateCardFieldPosition(mTrans[i]); // update position of initial field card
				f1.setFieldByMarkerID(mIDcField,mID[i]); // set Field by MarkerID ,now this field not empty
				gameState = 1; // change game state
				cout<<"Change gameState = 1 : found card field marker"<<endl;
				runtime = true;
			}
		
		}
	}
	// found field marker ,
	// wait: p1 set character back card && p2 set character back card => 2
	else if(gameState==1)
	{
		mID.clear();
		mTrans.clear();
		for(int i=0; i<numDetected; i++)
		{
			// get [MarkerID] from current [MakerIndex[i]] for identify each Maker
			mID.push_back(artk.getMarkerID(i));
			// get [Marker Translation] from current [MakerIndex[i]]
			mTrans.push_back(artk.getTranslation(i));
		}

		for(int i=0; i<mID.size(); i++)
		{
			if(mID[i]==mIDcField){f1.updateCardFieldPosition(mTrans[i]);}// update position of initial field card
			nearField = f1.findNearestFieldAndMaker(mTrans[i]); // find near field and marker
			drawAR(mID[i],i); // draw object on marker

			if(mID[i]==mIDcBack)
			{
				if((nearField==2 || nearField==5) && calDistance(f1.getfPos(nearField),mTrans[i])<100)
				{
					d1 = f1.setFieldByMarkerID(nearField,mID[i]); // set card field by marker id
				}
			}

			if(f1.getMarkerIDsetted(2)==mIDcBack && f1.getMarkerIDsetted(5)==mIDcBack)
			{	
				gameState = 2; // change game state
				cout<<"Change gameState = 2 : All player set back character card done"<<endl;
				runtime = true;
			}
		}
	}
	// set character back card done ,
	// wait: p1 flip card to front  && p2 flip card to front => 3
	else if(gameState==2)
	{
		mID.clear();
		mTrans.clear();
		for(int i=0; i<numDetected; i++)
		{
			// get [MarkerID] from current [MakerIndex[i]] for identify each Maker
			mID.push_back(artk.getMarkerID(i));
			// get [Marker Translation] from current [MakerIndex[i]]
			mTrans.push_back(artk.getTranslation(i));
		}
		for(int i=0; i<mID.size(); i++)
		{
			if(mID[i]==mIDcField){f1.updateCardFieldPosition(mTrans[i]);}// update position of field card
			nearField = f1.findNearestFieldAndMaker(mTrans[i]); // find near field and marker
			drawAR(mID[i],i); // draw object on marker
		
			// check [markerID] is in [markerIDcardFront] and in field must set by mIDcBack only
			if((findIndex(this->mIDcFront,mID[i])!=-1)/*&&(f1.getMarkerIDsetted(2)==mIDcBack)&&(f1.getMarkerIDsetted(5)==mIDcBack)*/)
			{
				// if distance<100 set card to field
				if((nearField==2 || nearField==5) && calDistance(f1.getfPos(nearField),mTrans[i])<100)
				{
					f1.setFMisEmpty(nearField);
					d1 = f1.setFieldByMarkerID(nearField,mID[i]); // set card field by marker id
				}
			}
			// check f1.[2] and f1.[5] is contain in mIDcFront
			if(findIndex(mIDcFront,f1.getMarkerIDsetted(2))!=-1 && findIndex(mIDcFront,f1.getMarkerIDsetted(5))!=-1)
			{	
				gameState = 3; // change game state
				cout<<"Change gameState = 3 : All player flip character card done"<<endl;
				runtime = true;
			}
		}
	}
	// set character card done ,
	// wait: pATK set back attack card && pDEF set back support card => 4
	else if(gameState==3)
	{
		CalDmg.~CalculateDmg(); // clear all damage
		mID.clear();
		mTrans.clear();
		for(int i=0; i<numDetected; i++)
		{
			// get [MarkerID] from current [MakerIndex[i]] for identify each Maker
			mID.push_back(artk.getMarkerID(i));
			// get [Marker Translation] from current [MakerIndex[i]]
			mTrans.push_back(artk.getTranslation(i));
		}

		for(int i=0; i<mID.size(); i++)
		{
			if(mID[i]==mIDcField){f1.updateCardFieldPosition(mTrans[i]);} // update position of field card
			nearField = f1.findNearestFieldAndMaker(mTrans[i]); // find near field and marker
			drawAR(mID[i],i); // draw object on marker

			if(mID[i]==mIDscBack)
			{
				// if p1 attack and p2 defend
				if(((nearField==1 || nearField==4) && calDistance(f1.getfPos(nearField),mTrans[i])<100))
				{
					f1.setFMisEmpty(nearField); // clear field 1 to set atk card
					f1.setFMisEmpty(3); // clear field 3 cause not be defender
					f1.setFMisEmpty(6); // clear field 6 cause not be attack
					d1 = f1.setFieldByMarkerID(nearField,mID[i]); // set card field by marker id
					if(f1.getMarkerIDsetted(nearField)==mIDscBack){PL.setTurn(1);PR.setTurn(0);} // set play turn
				}
				// if p2 attack and p1 defend
				else if((nearField==3 || nearField==6) && calDistance(f1.getfPos(nearField),mTrans[i])<100)
				{
					f1.setFMisEmpty(nearField); // clear field 6 to set atk card
					f1.setFMisEmpty(4); // clear field 4 cause not be defender
					f1.setFMisEmpty(1); // clear field 1 cause not be attack
					d1 = f1.setFieldByMarkerID(nearField,mID[i]); // set card field by marker id
					if(f1.getMarkerIDsetted(nearField)==mIDscBack){PL.setTurn(0);PR.setTurn(1);} // set play turn
				}
			}			
		
			// check player turn and flip card, detect first card flip
			if((PL.isTurn() && f1.getMarkerIDsetted(1)==mIDscBack && f1.getMarkerIDsetted(4)==mIDscBack) ||
				(PR.isTurn() && f1.getMarkerIDsetted(6)==mIDscBack && f1.getMarkerIDsetted(3)==mIDscBack))
			{	
				gameState = 4; // change game state
				cout<<"Change gameState = 4 : All player set support card done and ready to fight"<<endl;
				runtime = true;
			}
		}

	
	}
	// set back support card done ,
	// wait: pATK and pDEF flip card to front => 5
	else if(gameState==4)
	{
		mID.clear();
		mTrans.clear();
		for(int i=0; i<numDetected; i++)
		{
			// get [MarkerID] from current [MakerIndex[i]] for identify each Maker
			mID.push_back(artk.getMarkerID(i));
			// get [Marker Translation] from current [MakerIndex[i]]
			mTrans.push_back(artk.getTranslation(i));
		}
		for(int i=0; i<mID.size(); i++)
		{
			if(mID[i]==mIDcField){f1.updateCardFieldPosition(mTrans[i]);}; // update position of field card
			nearField = f1.findNearestFieldAndMaker(mTrans[i]); // find near field and marker
			drawAR(mID[i],i); // draw object on marker

			//// check mID is contain in mIDscFront
			//if(findIndex(mIDscFront,mID[i])!=-1)
			//{
			//	nearField = f1.findNearestFieldAndMaker(mTrans[i]);
			//	if(PL.isTurn() && nearField==4 && calDistance(f1.getfPos(nearField),mTrans[i])<100)
			//	{
			//		f1.setFMisEmpty(nearField); // clear slot for set new card
			//		d1 = f1.setFieldByMarkerID(nearField,mID[i]); // set card field by marker id
			//	}
			//	else if(PR.isTurn() && nearField==3 && calDistance(f1.getfPos(nearField),mTrans[i])<100)
			//	{
			//		f1.setFMisEmpty(nearField); // clear slot for set new card
			//		d1 = f1.setFieldByMarkerID(nearField,mID[i]); // set card field by marker id
			//	}
			//}

			//// check mID is mIDcAtkFront
			//if(mID[i]==mIDcAtkFront)
			//{
			//	nearField = f1.findNearestFieldAndMaker(mTrans[i]);
			//	if(PL.isTurn() && nearField==1 && calDistance(f1.getfPos(nearField),mTrans[i])<100)
			//	{
			//		f1.setFMisEmpty(nearField); // clear slot for set new card
			//		d1 = f1.setFieldByMarkerID(nearField,mID[i]); // set card field by marker id
			//	}
			//	else if(PR.isTurn() && nearField==6 && calDistance(f1.getfPos(nearField),mTrans[i])<100)
			//	{
			//		f1.setFMisEmpty(nearField); // clear slot for set new card
			//		d1 = f1.setFieldByMarkerID(nearField,mID[i]); // set card field by marker id
			//	}
			//}

			// if p1 attack
			if(PL.isTurn())
			{
				// check field slot is set by mIDscBack
				if(mIDcAtkFront==mID[i] && nearField==1 && calDistance(f1.getfPos(nearField),mTrans[i])<100 && f1.getMarkerIDsetted(1)==mIDscBack)
				{
					f1.setFMisEmpty(nearField); // clear slot for set new card
					d1 = f1.setFieldByMarkerID(nearField,mID[i]); // set card field by marker id
				}
				// check field slot is set by mIDscBack, check card flip is support card
				if(findIndex(mIDscFront,mID[i])!=-1 && nearField==4 && calDistance(f1.getfPos(nearField),mTrans[i])<100 && f1.getMarkerIDsetted(4)==mIDscBack)
				{
					f1.setFMisEmpty(nearField); // clear slot for set new card
					d1 = f1.setFieldByMarkerID(nearField,mID[i]); // set card field by marker id
				}
			}
			// if p1 attack
			else if(PR.isTurn())
			{
				// check field slot is set by mIDscBack
				if(mIDcAtkFront==mID[i] && nearField==6 && calDistance(f1.getfPos(nearField),mTrans[i])<100 && f1.getMarkerIDsetted(6)==mIDscBack)
				{
					f1.setFMisEmpty(nearField); // clear slot for set new card
					d1 = f1.setFieldByMarkerID(nearField,mID[i]); // set card field by marker id
				}
				// check field slot is set by mIDscBack, check card flip is support card
				if(findIndex(mIDscFront,mID[i])!=-1 && nearField==3 && calDistance(f1.getfPos(nearField),mTrans[i])<100 && f1.getMarkerIDsetted(3)==mIDscBack)
				{
					f1.setFMisEmpty(nearField); // clear slot for set new card
					d1 = f1.setFieldByMarkerID(nearField,mID[i]); // set card field by marker id
				}
			}
		}
		// 
		if((PL.isTurn() && findIndex(mIDscFront,f1.getMarkerIDsetted(4))!=-1) && f1.getMarkerIDsetted(1)==mIDcAtkFront || 
			(PR.isTurn() && findIndex(mIDscFront,f1.getMarkerIDsetted(3))!=-1) && f1.getMarkerIDsetted(6)==mIDcAtkFront)
		{	
			gameState = 5; // change game state
			cout<<"Change gameState = 5 : All player flip support card, The Fighting is begin !!"<<endl;
			runtime = true;
		}
	}
	// fighting turn and calculate damage ,
	// wait: time delay  => 6 
	else if(gameState==5)
	{
		mID.clear();
		mTrans.clear();
		for(int i=0; i<numDetected; i++)
		{
			// get [MarkerID] from current [MakerIndex[i]] for identify each Maker
			mID.push_back(artk.getMarkerID(i));
			// get [Marker Translation] from current [MakerIndex[i]]
			mTrans.push_back(artk.getTranslation(i));
		}


		if(PL.isTurn())
		{
			int ia=f1.getMarkerIDsetted(2); // id of atk character front card as set in field slot
			int id=f1.getMarkerIDsetted(5); // id of def character front card as set in field slot
			int idt=f1.getMarkerIDsetted(4); // id of type defence front card as set in field slot
			int ica=0; // marker id of attack character
			int icd=0; // marker id of defence character
			int icdt=0; // marker id of defence type

			for(int j=0;j<clist.size();j++)
			{
				if(ia == clist[j].cmIdFront())
				{	ica = j;	}
			}
			int atk = floor((clist[ica].atk() * clist[ica].atkRate())+0.5); // get total attack
			int atk2 = clist[ica].atk();

			for(int j=0;j<clist.size();j++)
			{
				if(id == clist[j].cmIdFront())
				{	icd = j;	}
			}
			int def = clist[icd].def(); //get defence

			for(int j=0;j<sclist.size();j++)
			{
				if(idt == sclist[j].cmIdFront())
				{	icdt = j;	}
			}


			CalDmg.cTdef(idt,atk2,def);
			PL.calculateHP(CalDmg.paDmg());
			PR.calculateHP(CalDmg.pdDmg());
			cout<<"=========== PL turn ==========="<<icdt<<endl;
			cout<<clist[ica].Cname()<<" is Attacker"<<", has attack power ["<<atk2<<"]"<<endl;
			cout<<clist[icd].Cname()<<" is Defender"<<", has defence power ["<<def<<"]"<<endl;
			cout<<clist[icd].Cname()<<" is Defender"<<", has ["<<sclist[icdt].Cname()<<"]"<<endl;
			//cout<<"p1 atk rate "<<clist[ica].atkRate()<<" : "<<atk<<endl;
			cout<<"Attacker got damage: "<<CalDmg.paDmg()<<endl;
			cout<<"Defender got damage: "<<CalDmg.pdDmg()<<endl;
		}
		else if(PR.isTurn())
		{
			int ia=f1.getMarkerIDsetted(5); // id of atk character front card as set in field slot
			int id=f1.getMarkerIDsetted(2); // id of def character front card as set in field slot
			int idt=f1.getMarkerIDsetted(3); // id of type defence front card as set in field slot
			int ica=0; // marker id of attack character
			int icd=0; // marker id of defence character
			int icdt=0; // marker id of defence type

			for(int j=0;j<clist.size();j++)
			{
				if(ia == clist[j].cmIdFront())
				{	ica = j;	}
			}
			int atk = floor((clist[ica].atk() * clist[ica].atkRate())+0.5); // get total attack
			int atk2 = clist[ica].atk();

			for(int j=0;j<clist.size();j++)
			{
				if(id == clist[j].cmIdFront())
				{	icd = j;	}
			}
			int def = clist[icd].def(); //get defence
			
			for(int j=0;j<sclist.size();j++)
			{
				if(idt == sclist[j].cmIdFront())
				{	icdt = j;	}
			}

			CalDmg.cTdef(idt,atk2,def);
			PR.calculateHP(CalDmg.paDmg());
			PL.calculateHP(CalDmg.pdDmg());
			cout<<"=========== PR turn ==========="<<icdt<<endl;
			cout<<clist[ica].Cname()<<" is Attacker"<<", has attack power ["<<atk2<<"]"<<endl;
			cout<<clist[icd].Cname()<<" is Defender"<<", has defence power ["<<def<<"]"<<endl;
			cout<<clist[icd].Cname()<<" is Defender"<<", has ["<<sclist[icdt].Cname()<<"]"<<endl;
			//cout<<"p1 atk rate "<<clist[ica].atkRate()<<" : "<<atk<<endl;
			cout<<"Attacker got damage: "<<CalDmg.paDmg()<<endl;
			cout<<"Defender got damage: "<<CalDmg.pdDmg()<<endl;
		}


		for(int i=0; i<mID.size(); i++)
		{
			if(mID[i]==mIDcField){f1.updateCardFieldPosition(mTrans[i]);}; // update position of field card
			nearField = f1.findNearestFieldAndMaker(mTrans[i]); // find near field and marker
			drawAR(mID[i],i); // draw object on marker
			gameState = 6;
			cout<<"Change gameState = 6 : Calculate damage completed and ending this turn"<<endl;
		}
	}
	// show effect and calculate player hp ,
	// wait: if any pHP !=0 => 3 else => 7
	else if(gameState==6)
	{
		mID.clear();
		mTrans.clear();
		for(int i=0; i<numDetected; i++)
		{
			// get [MarkerID] from current [MakerIndex[i]] for identify each Maker
			mID.push_back(artk.getMarkerID(i));
			// get [Marker Translation] from current [MakerIndex[i]]
			mTrans.push_back(artk.getTranslation(i));
		}

		for(int i=0; i<mID.size(); i++)
		{
			if(mID[i]==mIDcField){f1.updateCardFieldPosition(mTrans[i]);}; // update position of field card
			nearField = f1.findNearestFieldAndMaker(mTrans[i]); // find near field and marker
			drawAR(mID[i],i); // draw object on marker
			
			if(PL.isAlive() && PR.isAlive())
			{	
				gameState = 3;	f1.setFMisEmpty(1);	f1.setFMisEmpty(3);	f1.setFMisEmpty(4);	f1.setFMisEmpty(6);
				cout<<"Change gameState = 3 : Calculate damage completed and ending this turn"<<endl;
			}else
			{	
				gameState = 7;
				if(PL.isAlive()){}
				cout<<"Change gameState = 7 : Player"<<endl;
			}
		}
	}
	// got winner and game end
	else if(gameState==7)
	{
		mID.clear();
		mTrans.clear();
		for(int i=0; i<numDetected; i++)
		{
			// get [MarkerID] from current [MakerIndex[i]] for identify each Maker
			mID.push_back(artk.getMarkerID(i));
			// get [Marker Translation] from current [MakerIndex[i]]
			mTrans.push_back(artk.getTranslation(i));
		}
		for(int i=0; i<mID.size(); i++)
		{
			if(mID[i]==mIDcField){f1.updateCardFieldPosition(mTrans[i]);}; // update position of field card
			nearField = f1.findNearestFieldAndMaker(mTrans[i]); // find near field and marker
			drawAR(mID[i],i); // draw object on marker
		}
	}


	glDisable (GL_DEPTH_TEST);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == OF_KEY_UP) {
		artk.setThreshold(++threshold);
	} else if(key == OF_KEY_DOWN) {
		artk.setThreshold(--threshold);		
	} else if(key == 't' || key == 'T'){
		pict = !pict;
	}
	else if(key == '0'){
		gameState = 0;
		runtime = true;
	}
	else if(key == '1'){
		gameState = 1;
		runtime = true;
	}
	else if(key == '2'){
		gameState = 2;
		runtime = true;
	}
	else if(key == '3'){
		gameState = 3;
		runtime = true;
	}
	else if(key == '4'){
		gameState = 4;
		runtime = true;
	}
	else if(key == '5'){
		gameState = 5;
		runtime = true;
	}
	else if(key == '6'){
		gameState = 6;
		runtime = true;
	}
	else if(key == 'o'){
		mw += 5.0;
		mh += 5.0;
		f1.setWH(mw,mh);
		cout<<"mw mh : "<<mw<<" "<<mh<<endl;
	}
	else if(key == 'p'){
		mw -= 5.0;
		mh -= 5.0;
		f1.setWH(mw,mh);
		cout<<"mw mh : "<<mw<<" "<<mh<<endl;
	}
	#ifdef CAMERA_CONNECTED
	if(key == 's' || key == 'S') {
		vidGrabber.videoSettings();
	}
	#endif

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
void testApp::drawAR(int markerID,int mrIndex){
	this->drawAR(markerID,mrIndex,"");
}
void testApp::drawAR(int markerID,int mrIndex,string mname){
	artk.applyModelMatrix(mrIndex); //input = [marker index] as want to draw graphic **not markerID**
	glPushMatrix();

	if(markerID==mIDcField)// check if is [field card]
	{
		glPushMatrix();
			ofSetLineWidth(5);
			ofNoFill();		
			ofEnableSmoothing();
			ofEnableAlphaBlending();    // turn on alpha blending
			f1.drawField(); // call function draw field
			ofDisableAlphaBlending();   // turn off alpha
			mAss.setScale(1.0 + (mw - 50)*0.025,1.0 + (mw - 50)*0.025,1.0 + (mw - 50)*0.025);
			mAss.setPosition(0,0,50.0 + (mw - 50)*1.5);
			ofFill();	
			mAss.draw();
			
			ofNoFill();	
			ofSetColor(255, 255, 255);
			//cardFieldImage.draw(-25,-25,50,50);	// draw image
			glPushMatrix();
				ofSetColor(255, 0, 255);
				glScalef(0.5,0.5,0.5);
				glTranslatef(-40,10,0);
				glRotatef(180 ,1 ,0 ,0 );
				ofDrawBitmapString("Card Field",0 , 0);
				if(gameState==1 && runtime)
				{
					it = 100;
					ofSetColor(255,0,0);
					glScalef(2,2,0);
					ofDrawBitmapString("Found Field Card", -50, -50);
					ofDrawBitmapString("State Change to:" + ofToString(gameState), -50, 50);
				}
				if(gameState==2 && runtime)
				{
					it = 100;
					ofSetColor(255,0,0);
					glScalef(2,2,0);
					ofDrawBitmapString("Set Card Done!!", -50, -50);
					ofDrawBitmapString("State Change to:" + ofToString(gameState), -50, 50);
				}
				if(gameState==3 && runtime)
				{
					it = 100;
					ofSetColor(255,0,0);
					glScalef(2,2,0);
					//ofDrawBitmapString("Set Card Done!!", -50, -50);
					ofDrawBitmapString("State Change to:" + ofToString(gameState), -50, 50);
				}
				if(gameState==4 && runtime)
				{
					it = 100;
					ofSetColor(255,0,0);
					glScalef(2,2,0);
					//ofDrawBitmapString("Set Card Done!!", -50, -50);
					ofDrawBitmapString("State Change to:" + ofToString(gameState), -50, 50);
				}
				if(gameState==5 && runtime)
				{
					it = 100;
					ofSetColor(255,0,0);
					glScalef(2,2,0);
					//ofDrawBitmapString("Set Card Done!!", -50, -50);
					ofDrawBitmapString("State Change to:" + ofToString(gameState), -50, 50);
				}
				if(gameState==6 && runtime)
				{
					it = 100;
					ofSetColor(255,0,0);
					glScalef(2,2,0);
					//ofDrawBitmapString("Set Card Done!!", -50, -50);
					ofDrawBitmapString("State Change to:" + ofToString(gameState), -50, 50);
				}
			glPopMatrix();	
		glPopMatrix();		
	}
	else if(markerID==mIDcBack)// check if is card backing
	{	
		glPushMatrix();	
			ofSetLineWidth(5);
			ofNoFill();
			ofSetColor(255, 255, 255);
			//glTranslatef(0,0,50);
			cardBackImage.draw(-25,-25,50,50); // draw card backing image
		glPopMatrix();
	}	
	//else if(markerID==mID[2])
	//{
	//	glPushMatrix();
	//		ofSetLineWidth(5);
	//		ofNoFill();
	//		ofSetColor(255, 0, 0);
	//		glScalef(0.5,0.5,0.5);
	//		glTranslatef(-40,10,0);
	//		glRotatef(180 ,1 ,0 ,0 );
	//		ofDrawBitmapString("Card No.2",0 , 0);
	//	glPopMatrix();
	//}
	
	else if(markerID==mID[3])
	{
		glPushMatrix();
			ofSetLineWidth(5);
			ofNoFill();
			ofSetColor(255, 0, 0);
			glScalef(0.5,0.5,0.5);
			glTranslatef(-40,10,0);
			glRotatef(180 ,1 ,0 ,0 );
			ofDrawBitmapString("Card No."+ofToString(markerID),0 , 0);
		glPopMatrix();
	}
	else if(markerID==mID[4])
	{
		glPushMatrix();
			ofSetLineWidth(5);
			ofNoFill();
			ofSetColor(255, 0, 0);
			glScalef(0.5,0.5,0.5);
			glTranslatef(-40,10,0);
			glRotatef(180 ,1 ,0 ,0 );
			ofDrawBitmapString("Card No."+ofToString(markerID),0 , 0);
		glPopMatrix();
	}/*
	else if(markerID==mID[5])
	{
		
	}
	else if(markerID==mID[6])
	{
		
	}
	else if(markerID==mID[7])
	{
		
	}
	else if(markerID==mID[8])
	{
		
	}
	else if(markerID==mID[9])
	{
		
	}
	*/

	// draw marker's vector of translation
	glPushMatrix();
		ofSetLineWidth(5);
		ofNoFill();
		ofSetColor(255, 100, 100);
		glScalef(0.5,0.5,0.5);
		glTranslatef(-20,0,0);
		glRotatef(180 ,1 ,0 ,0 );
		ofDrawBitmapString("Card No:"+ofToString(markerID)+"\nDetected :"+ofToString(mrIndex),-20 , -30);
		/*ofDrawBitmapString(ofToString(mTrans[mrIndex][0]) + 
		"\n" + ofToString(mTrans[mrIndex][1]) + 
		"\n" + ofToString(mTrans[mrIndex][2]),-10 , 0);*/
	glPopMatrix();

	glPopMatrix();
}

//--------------------------------------------------------------
void testApp::drawEffect(int mIndex){

}

//--------------------------------------------------------------
int testApp::findIndex (vector<int> series, int v)
{
	for (int i=0; i<series.size(); i++)
	{
		if (series[i] == (v))
		{
			return(i);  /* it was found */
		}
	}
	return(-1);  /* if it was not found */
}



////--------------------------------------------------------------
//float testApp::calDistance(ofPoint p1,ofPoint p2){
//
//	return abs((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
//}

////--------------------------------------------------------------
//int testApp::findIndexArray (int arr[], int v)
//{
//	for (int i=0; i<(sizeof(arr)/sizeof(*arr)); i++)
//	{
//		if(arr[i] == v) return(i);
//	}
//	return(-1);
//}
