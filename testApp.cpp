#include "testApp.h"
//GLfloat lightOnePosition[] = {40.0, 40, 100.0, 0.0};
//GLfloat lightOneColor[] = {0.99, 0.99, 0.99, 1.0};
//
//GLfloat lightTwoPosition[] = {-40.0, 40, 100.0, 0.0};
//GLfloat lightTwoColor[] = {0.99, 0.99, 0.99, 1.0};

//--------------------------------------------------------------
void testApp::setup(){
	pict = false; 
	hpbar = dtext = true;
	ar = dep = true;
	wt = 0;
	it = 999;
	runtime = false;
	mIDcField = 0;
	mIDcBack = mIDscBack = 1;
	mIDcAtkFront = 9;
	mw = mh = 75.0;
	effectrun = false;
	effecttime = 999;
	effectx = 0;

	gameState = 0; // ready to game start

	//PL.setTurn(0);
	//PR.setTurn(0);

	// setup hp bar
	//plDis.setFromCenter(ofPoint(0 + 100.0/2.0,height - 100.0/2.0),100.0,100.0);
	//prDis.setFromCenter(ofPoint(width - 100.0/2.0,height - 100.0/2.0),100.0,100.0);
	
	// setup all character cards
	c1.setCName("Dark Magician");
	c1.setmIDBack(1);
	c1.setmIDFront(2);
	c1.setATK(40,60);
	c1.setDEF(15);
	//float r1[10] = {0.5, 0.5, 0.5, 1.0, 1.0, 1.0, 1.0, 1.5, 1.5, 2.0};
	//c1.setAtkRate(r1);

	c2.setCName("Twinhead Dragon");
	c2.setmIDBack(1);
	c2.setmIDFront(3);
	c2.setATK(35,65);
	c2.setDEF(25);
	//float r2[10] = {0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.5, 1.5, 2.0};
	//c2.setAtkRate(r2);

	c3.setCName("Dragon Knight");
	c3.setmIDBack(1);
	c3.setmIDFront(4);
	c3.setATK(30,45);
	c3.setDEF(40);
	//float r3[10] = {0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.5, 1.5, 1.5, 2.0};
	//c3.setAtkRate(r3);

	c4.setCName("Elf of Light");
	c4.setmIDBack(1);
	c4.setmIDFront(5);
	c4.setATK(20,80);
	c4.setDEF(20);
	//float r4[10] = {0.5, 1.0, 1.0, 1.5, 1.5, 1.5, 1.5, 2.0, 2.0, 2.0};
	//c4.setAtkRate(r4);

	c5.setCName("Skull Devil");
	c5.setmIDBack(1);
	c5.setmIDFront(6);
	c5.setATK(50,55);
	c5.setDEF(10);
	//float r5[10] = {0.5, 0.5, 0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.5, 2.0};
	//c5.setAtkRate(r5);

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

	//delete r1,r2,r3,r4,r5;

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
	//ofBackground(127,127,127);

	// Load image card backing
	cardBackImage.loadImage("card/336px-BackVG-DOR.png");
	cardBackImage.mirror(1,0); //rotate x
	cardFieldImage.loadImage("card/331px-Back-Anime-ZX-2.png");
	cardFieldImage.mirror(1,0); //rotate x

	cardCharacter[0].loadImage("card/cc01.jpg");
	cardCharacter[0].mirror(1,0); //rotate x
	cardCharacter[1].loadImage("card/cc02.jpg");
	cardCharacter[1].mirror(1,0); //rotate x
	cardCharacter[2].loadImage("card/cc03.png");
	cardCharacter[2].mirror(1,0); //rotate x
	cardCharacter[3].loadImage("card/cc04.jpg");
	cardCharacter[3].mirror(1,0); //rotate x
	cardCharacter[4].loadImage("card/cc05.jpg");
	cardCharacter[4].mirror(1,0); //rotate x

	cardDef[0].loadImage("card/cd01.jpg");
	cardDef[0].mirror(1,0); //rotate x
	cardDef[1].loadImage("card/cd02.jpg");
	cardDef[1].mirror(1,0); //rotate x
	cardDef[2].loadImage("card/cd03.jpg");
	cardDef[2].mirror(1,0); //rotate x
	cardDef[3].loadImage("card/cd04.jpg");
	cardDef[3].mirror(1,0); //rotate x

	cardAtk.loadImage("card/ca02.jpg");
	cardAtk.mirror(1,0); //rotate x


	// Load true type font
	font[0].loadFont("comic.ttf",20);
	font[1].loadFont("COPRGTB.TTF",20);
	font[2].loadFont("HATTEN.TTF",20);


	/* ================================== Load ModeL ================================= */
	ofEnableAlphaBlending();    // turn on alpha blending
	ofBackground(255,255,255,50);
	ofDisableAlphaBlending();    // turn off alpha blending
	
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
    //glColorMaterial (GL_FRONT_AND_BACK, GL_DIFFUSE);
    //glEnable (GL_COLOR_MATERIAL);

	mc1.loadModel("squirrel/Altair Model/altair.3ds",0.8);
	mc1.setPosition(0.0, 0.0, 0.0);
	mc1.setRotation(1,90,1,0,0);

	mc2.loadModel("squirrel/goku.3DS",0.75);

	mc3.loadModel("squirrel/goku.3DS",0.75);

	mc4.loadModel("squirrel/goku.3DS",0.75);

	mc5.loadModel("squirrel/goku_nofloor2.3DS",0.75);
	
	//glPolygonMode(GL_FRONT, GL_FILL);//else glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_BACK, GL_LINE);

	
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

		// convert our camera image to grayscale
		grayImage = colorImage;
		
		// apply a threshold so we can see what is going on
		grayThres = grayImage;
		grayThres.threshold(threshold);
		
		// Pass in the new image pixels to artk
		artk.update(grayImage.getPixels());
		//tex1.loadData(grayThres.getPixelsRef());
	}


	
	if(runtime)
	{wt++;}
	if(wt>=it)
	{runtime=false;wt=0;it=999;}

	if(effectrun)
	{effectx+=5;}
	//if(effectx>=effecttime)
	//{effectrun=false;effectx=0;effecttime=999;}

	f1.setWH(mw,mh);
	
}

//--------------------------------------------------------------
void testApp::draw(){
	/*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);*/
   	
	//if(!dep){glDisable(GL_DEPTH_TEST);}
	
	//glPushMatrix();
	//ofEnableAlphaBlending();    // turn on alpha blending
	if(pict) // toggle show color image or threshold image
	{
		// Threshold image
		ofSetColor(255,255,255,50);
		grayThres.draw(0, 0);
	}else
	{
		// Main image
		ofSetColor(255,255,255,50);
		//grayImage.draw(0, 0);
		//colorImage.draw(0, 0);
		//tex1.draw(0,0);
	}
	ofDisableAlphaBlending();    // turn off alpha blending
	//ofEnableAlphaBlending();    // turn on alpha blending

	if(dtext) // toggle show field detail
	{
	ofSetColor(255,0,0);
	ofDrawBitmapString(ofToString(artk.getNumDetectedMarkers()) + " marker(s) found", 10, 20);
	ofDrawBitmapString("Game State: " + ofToString(gameState), 690, 20);
	ofDrawBitmapString("Threshold: " + ofToString(threshold), 10, 40);
	ofDrawBitmapString("Use the Up/Down keys to adjust the threshold", 420, 40);
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
	ofDrawBitmapString("effect time : " + ofToString(effecttime), 10, 320);
	ofDrawBitmapString("effect x : " + ofToString(effectx), 10, 340);
	ofDrawBitmapString("effect run : " + ofToString(effectrun), 10, 360);
	ofDrawBitmapString("distance : " + ofToString(dm), 10, 380);
	}

	if(hpbar) // toggle show player detail
	{
	ofSetColor(255,0,0);
	ofDrawBitmapString("P1 HP : " + ofToString(PL.hp()), 120, height - 80);
	ofDrawBitmapString("P1 Life : " + ofToString(PL.isAlive()), 120, height - 60);
	ofDrawBitmapString("P1 Turn : " + ofToString(PL.isTurn()), 120, height - 40);

	ofDrawBitmapString("P2 HP : " + ofToString(PR.hp()), (width - 200), height - 80);
	ofDrawBitmapString("P2 Life : " + ofToString(PR.isAlive()), (width - 200), height - 60);
	ofDrawBitmapString("P2 Turn : " + ofToString(PR.isTurn()), (width - 200), height - 40);
	

	
	ofEnableAlphaBlending();    // turn on alpha blending
	ofFill();	
	if(gameState==4 || gameState==5 || gameState==6)
	{
		if(PL.isTurn())
		{
			glPushMatrix();
			ofSetColor(255, 0, 0,127);
			font[1].drawString("ATK",20, height - 60);
			ofSetColor(0, 0, 255,127);
			font[1].drawString("DEF",width - 80, height - 60);
			glPopMatrix();
		}
		else if(PR.isTurn())
		{
			glPushMatrix();
			ofSetColor(255, 0, 0,127);
			font[1].drawString("ATK",width - 80, height - 60);
			ofSetColor(0, 0, 255,127);
			font[1].drawString("DEF",20, height - 60);
			glPopMatrix();
		}
	}

	ofSetLineWidth(5);
	ofNoFill();	
	ofEnableAlphaBlending();    // turn on alpha blending
	ofSetColor(255, 0, 0, 235);
	ofRect(ofPoint(0,height - 100),100,100);
	ofSetColor(0, 0, 255, 235);
	ofRect(ofPoint(width - 100,height - 100),100,100);
	
	// set empty hp bar color
	co0.set(255,0,0,190); // set red color RGB format

	// set current hp bar color
	co1.set(0,255,0,190); // set green color RGB format
	co1.setHue(85 - 85 + PL.hp()*0.85); // change hue value range 0-85 calculate from player hp
	co2.set(0,255,0,190); // set green color RGB format
	co2.setHue(85 - 85 + PR.hp()*0.85); // change hue value range 0-85 calculate from player hp

	// draw hp bar
	ofSetLineWidth(1);
	ofFill(); // enable fill color
	glBegin(GL_POLYGON); // start draw polygon
	ofSetColor(co0, 190); // set red color for empty hp
	glVertex3f(100,height - 20,0); // top-left point
	glVertex3f(100,height,0); // bottom-left point
	ofSetColor(co1, 190); // set current color calculate from hp
	glVertex3f((width/2.0) - (width/2.0 - 100) + PL.hp()*0.01*(width/2.0 - 100) - 2,height,0); // top-right point
	glVertex3f((width/2.0) - (width/2.0 - 100) + PL.hp()*0.01*(width/2.0 - 100) - 2,height - 20,0); // bottom-right point
	glEnd();

	glBegin(GL_POLYGON);
	ofFill();
	ofSetColor(co0, 190);
	glVertex3f(width - 100,height - 20,0);
	glVertex3f(width - 100,height,0);
	ofSetColor(co2, 190);
	glVertex3f((width/2.0) + (width/2.0 - 100) - PR.hp()*0.01*(width/2.0 - 100) + 2,height,0);
	glVertex3f((width/2.0) + (width/2.0 - 100) - PR.hp()*0.01*(width/2.0 - 100) + 2,height - 20,0);
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
	}
	
	
	//glPopMatrix();
	//glLoadIdentity();
	//glEnable(GL_DEPTH_TEST);
	if(ar){
	// ARTK draw
	// An easy was to see what is going on
	// Draws the marker location and id number
	artk.draw(0,0);
	}
	
	// ARTK 3D stuff
	// This is another way of drawing objects aligned with the marker
	// First apply the projection matrix once
	artk.applyProjectionMatrix();
	
	// Find out how many markers have been detected
	int numDetected = artk.getNumDetectedMarkers();
	//if(dep){glLoadIdentity();}
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
			
			drawAR(mID[i],i); // draw object on marker
			if(mID[i]==mIDcBack)
			{
				nearField = f1.findNearestFieldAndMaker(mTrans[i]); // find near field and marker
				dm = calDistance(f1.getfPos(nearField),mTrans[i]);
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
			drawAR(mID[i],i); // draw object on marker
			
			// check [markerID] is in [markerIDcardFront] and in field must set by mIDcBack only
			if((findIndex(this->mIDcFront,mID[i])!=-1)/*&&(f1.getMarkerIDsetted(2)==mIDcBack)&&(f1.getMarkerIDsetted(5)==mIDcBack)*/)
			{
				nearField = f1.findNearestFieldAndMaker(mTrans[i]); // find near field and marker
				dm = calDistance(f1.getfPos(nearField),mTrans[i]);
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
			drawAR(mID[i],i); // draw object on marker

			if(mID[i]==mIDscBack)
			{
				nearField = f1.findNearestFieldAndMaker(mTrans[i]); // find near field and marker
				dm = calDistance(f1.getfPos(nearField),mTrans[i]);
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
			drawAR(mID[i],i); // draw object on marker

			// if p1 attack
			if(PL.isTurn())
			{
				nearField = f1.findNearestFieldAndMaker(mTrans[i]); // find near field and marker
				dm = calDistance(f1.getfPos(nearField),mTrans[i]);
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
				nearField = f1.findNearestFieldAndMaker(mTrans[i]); // find near field and marker
				dm = calDistance(f1.getfPos(nearField),mTrans[i]);
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
			//int atk = floor((clist[ica].atk() * clist[ica].atkRate())+0.5); // get total attack
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
			//PL.calculateHP(CalDmg.paDmg());
			//PR.calculateHP(CalDmg.pdDmg());
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
			//int atk = floor((clist[ica].atk() * clist[ica].atkRate())+0.5); // get total attack
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

		effectrun = true;
		for(int i=0; i<mID.size(); i++)
		{
			if(mID[i]==mIDcField){f1.updateCardFieldPosition(mTrans[i]);}; // update position of field card
			nearField = f1.findNearestFieldAndMaker(mTrans[i]); // find near field and marker
			dm = calDistance(f1.getfPos(nearField),mTrans[i]);
			drawAR(mID[i],i); // draw object on marker
		
			if(PL.isTurn() && mID[i]==f1.getMarkerIDsetted(2))
			{
				effecttime = floor(fabs(f1.getfPos(2).x - f1.getfPos(5).x) + 0.5) - 20;
				drawEffect(i);
				//if(effectx>=effecttime)
				//{effectrun=false;effectx=0;effecttime=999;}
			}
			else if(PR.isTurn() && mID[i]==f1.getMarkerIDsetted(5))
			{
				effecttime = floor(fabs(f1.getfPos(2).x - f1.getfPos(5).x) + 0.5) - 20;
				drawEffect(i);
				//if(effectx>=effecttime)
				//{effectrun=false;effectx=0;effecttime=999;}
			}
		}

		if(effectx>=effecttime)
		{
			effectrun=false;effectx=0;effecttime=999;
			
			// update HP
			if(PL.isTurn())
			{
				PL.calculateHP(CalDmg.paDmg());
				PR.calculateHP(CalDmg.pdDmg());
			}
			else if(PR.isTurn())
			{
				PR.calculateHP(CalDmg.paDmg());
				PL.calculateHP(CalDmg.pdDmg());
			}
		}

		if(PL.isAlive() && PR.isAlive() && effectrun!=true)
		{	
			gameState = 3;	f1.setFMisEmpty(1);	f1.setFMisEmpty(3);	f1.setFMisEmpty(4);	f1.setFMisEmpty(6);
			cout<<"Change gameState = 3 : Calculate damage completed and ending this turn"<<endl;
		}else if(effectrun!=true)
		{	
			gameState = 7;
			if(PL.isAlive()){
				cout<<"Change gameState = 7 : Game Over!! Player 1 Wins!!"<<endl;
			}
			else if(PR.isAlive()){
				cout<<"Change gameState = 7 : Game Over!! Player 2 Wins!!"<<endl;
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
			//nearField = f1.findNearestFieldAndMaker(mTrans[i]); // find near field and marker
			drawAR(mID[i],i); // draw object on marker
		}
	}


	//glDisable (GL_DEPTH_TEST);
	glFlush();
	glutSwapBuffers();
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
	else if(key == 'd'){
		dtext=!dtext;
	}
	else if(key == 'a'){
		ar=!ar;
	}
	else if(key == 'h'){
		hpbar=!hpbar;
	}
	else if(key == 'z'){
		dep=!dep;
	}
	else if(key == 'r'){
		gameState = 0;
		f1.clearAll();
		PL.~Player();
		PL.calculateHP(-100);
		PR.~Player();
		PR.calculateHP(-100);
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

	
	if(markerID==mIDcBack)// check if is card backing
	{	
		glPushMatrix();	
			ofSetLineWidth(5);
			ofNoFill();
			ofSetColor(255, 255, 255);
			//glTranslatef(0,0,50);
			cardBackImage.draw(-20,-29,40,58); // draw card backing image
		glPopMatrix();
	}	
	else if(markerID==mIDscBack)// check if is card backing
	{	
		glPushMatrix();	
			ofSetLineWidth(5);
			ofNoFill();
			ofSetColor(255, 255, 255);
			//glTranslatef(0,0,50);
			cardBackImage.draw(-20,-29,40,58); // draw card backing image
		glPopMatrix();
	}	
	else if(markerID==mIDcFront[0]) // Dark Magician
	{
		glPushMatrix();
			mc1.setScale(1.0 + (mw - 75)*0.025,1.0 + (mw - 75)*0.025,1.0 + (mw - 75)*0.025);
			mc1.setPosition(0,0,50.0 + (mw - 75)*1.5);
			ofFill();
			glRotatef(180,0,0,1);
			mc1.draw();
		glPopMatrix();

		glPushMatrix();
			ofSetLineWidth(5);
			ofNoFill();
			ofSetColor(255, 0, 0);
			glScalef(0.5,0.5,0.5);
			glTranslatef(-40,10,0);
			glRotatef(180 ,1 ,0 ,0 );
			//ofDrawBitmapString("Card No."+ofToString(markerID),0 , 0);
		glPopMatrix();
		glPushMatrix();
			ofNoFill();
			ofSetColor(255, 255, 255);
			cardCharacter[0].draw(-20,-29,40,58); // draw card
		glPopMatrix();		
	}
	else if(markerID==mIDcFront[1])
	{
		glPushMatrix();
		glRotatef(180,0,0,1);
		mc2.setScale(0.5,0.5,0.5);
		mc2.setRotation(1,90,1,0,0);
		mc2.setPosition(0,0,70);
		
		mc2.draw();
		glPopMatrix();

		glPushMatrix();
			ofSetLineWidth(5);
			ofNoFill();
			ofSetColor(255, 0, 0);
			glScalef(0.5,0.5,0.5);
			glTranslatef(-40,10,0);
			glRotatef(180 ,1 ,0 ,0 );
			//ofDrawBitmapString("Card No."+ofToString(markerID),0 , 0);
		glPopMatrix();
		
		glPushMatrix();
			ofNoFill();
			ofSetColor(255, 255, 255);
			cardCharacter[1].draw(-20,-29,40,58); // draw card
		glPopMatrix();	
	}
	else if(markerID==mIDcFront[2])
	{
		glPushMatrix();
		glRotatef(180,0,0,1);
		mc2.setScale(0.5,0.5,0.5);
		mc2.setRotation(1,90,1,0,0);
		mc2.setPosition(0,0,70);
		mc2.draw();
		glPopMatrix();

		glPushMatrix();
			ofSetLineWidth(5);
			ofNoFill();
			ofSetColor(255, 0, 0);
			glScalef(0.5,0.5,0.5);
			glTranslatef(-40,10,0);
			glRotatef(180 ,1 ,0 ,0 );
			//ofDrawBitmapString("Card No."+ofToString(markerID),0 , 0);
		glPopMatrix();

	//glTranslatef(0.0,0.0,40.0);
	//glRotatef(-90.0, 0.0, 0.0, 1.0);
	//glRotatef(90.0, 1.0, 0.0, 0.0);
	//glScalef(4.0,4.0,4.0);
	//glPushMatrix();
	//	// Draw Head
	//	glPushMatrix();
	//	glTranslatef(0.0,15.0,0.0);
	//	glRotatef(90.0, 1.0, 0.0, 0.0);
	//	glutSolidSphere(2.0,10.0,10.0);
	//	glPopMatrix();

	//	// Draw body
	//	glPushMatrix();
	//	glTranslatef(0.0,9.0,0.0);
	//	glScalef(1.0,3.0,2.0);
	//	glColor3f(1.0,0.0,1.0);
	//	glutSolidCube(3.0);
	//	glPopMatrix();

	//	// Draw Right arm
	//	glPushMatrix();
	//	glTranslatef(0.0,13.0,-4.0);
	//	glRotatef(5.0, 1.0, 0.0, 0.0); // angle
	//	glTranslatef(0.0,-4.0,0.0);
	//	glColor3f(0.0,1.0,0.0);
	//	glScalef(1.0,4.0,1.0);

	//	glutSolidCube(2.0);
	//	glPopMatrix();

	//	// Draw Left arm
	//	glPushMatrix();
	//	glTranslatef(0.0,13.0,4.0);
	//	glRotatef(-5.0, 1.0, 0.0, 0.0); // angle
	//	glTranslatef(0.0,-4.0,0.0);
	//	glColor3f(0.0,1.0,0.0);
	//	glScalef(1.0,4.0,1.0);
	//	glutSolidCube(2.0);
	//	glPopMatrix();



	//	// Draw Right down part
	//	glPushMatrix();
	//	glTranslatef(0.0,5.0,-1.5);
	//	glRotatef(0, 0.0, 0.0, 1.0); // Rotate all right leg
	//	glTranslatef(0.0,-5.0,1.5);

	//	// Draw Right leg
	//	glPushMatrix();	
	//	//glRotatef(-5.0, 1.0, 0.0, 0.0); // angle
	//	glTranslatef(0.0,2.0,-1.5);
	//	glScalef(1.0,3.0,1.0);
	//	glColor3f(1.0,0.0,0.0);
	//	glutSolidCube(2.0);
	//	glPopMatrix();

	//	glRotatef(30, 0.0, 0.0, 1.0);
	//	// Draw Right down leg
	//	glPushMatrix();

	//	//glRotatef(-5.0, 1.0, 0.0, 0.0); // angle
	//	glTranslatef(0.0,-4.0,-1.5);
	//	glScalef(1.0,3.0,1.0);
	//	glColor3f(0.0,0.0,1.0);
	//	glutSolidCube(2.0);
	//	glPopMatrix();

	//	// Draw Right foot
	//	glPushMatrix();
	//	//glRotatef(-5.0, 1.0, 0.0, 0.0); // angle
	//	glTranslatef(-1.0,-8.0,-1.5);
	//	glScalef(2.0,1.0,1.0);
	//	glColor3f(1.0,0.0,0.0);
	//	glutSolidCube(2.0);
	//	glPopMatrix();
	//	glPopMatrix(); // End Right down part

	//	// Draw Left down part
	//	//glPushMatrix();


	//	// Draw Left leg
	//	glPushMatrix();

	//	//glRotatef(-5.0, 1.0, 0.0, 0.0); // angle
	//	glTranslatef(0.0,2.0,1.5);
	//	glScalef(1.0,3.0,1.0);
	//	glColor3f(1.0,0.0,0.0);
	//	glutSolidCube(2.0);
	//	glPopMatrix();

	//	// Draw Left down leg
	//	glPushMatrix();

	//	//glRotatef(-5.0, 1.0, 0.0, 0.0); // angle
	//	glTranslatef(0.0,-4.0,1.5);
	//	glScalef(1.0,3.0,1.0);
	//	glColor3f(0.0,0.0,1.0);
	//	glutSolidCube(2.0);
	//	glPopMatrix();

	//	// Draw Left foot
	//	glPushMatrix();

	//	//glRotatef(-5.0, 1.0, 0.0, 0.0); // angle
	//	glTranslatef(-1.0,-8.0,1.5);
	//	glScalef(2.0,1.0,1.0);
	//	glColor3f(1.0,0.0,0.0);
	//	glutSolidCube(2.0);
	//	glPopMatrix();
	//glPopMatrix(); // End Left down part
		if(hpbar){
		glPushMatrix();
			ofNoFill();
			ofSetColor(255, 255, 255);
			cardCharacter[2].draw(-20,-29,40,58); // draw card
		glPopMatrix();	
		}
	}
	else if(markerID==mIDcFront[3])
	{
		//glPushMatrix();
		//glRotatef(180,0,0,1);
		//mc2.setScale(0.5,0.5,0.5);
		//mc2.setRotation(1,90,1,0,0);
		//mc2.setPosition(0,0,70);
		//
		//mc2.draw();
		//glPopMatrix();

		glPushMatrix();
			ofSetLineWidth(5);
			ofNoFill();
			ofSetColor(255, 0, 0);
			glScalef(0.5,0.5,0.5);
			glTranslatef(-40,10,0);
			glRotatef(180 ,1 ,0 ,0 );
			//ofDrawBitmapString("Card No."+ofToString(markerID),0 , 0);
		glPopMatrix();
			glPushMatrix();
			ofNoFill();
			ofSetColor(255, 255, 255);
			cardCharacter[3].draw(-20,-29,40,58); // draw card
		glPopMatrix();	
	}
	else if(markerID==mIDcFront[4])
	{
		//glPushMatrix();
		//glRotatef(180,0,0,1);
		//mc2.setScale(0.5,0.5,0.5);
		//mc2.setRotation(1,90,1,0,0);
		//mc2.setPosition(0,0,70);
		//
		//mc2.draw();
		//glPopMatrix();

		glPushMatrix();
			ofSetLineWidth(5);
			ofNoFill();
			ofSetColor(255, 0, 0);
			glScalef(0.5,0.5,0.5);
			glTranslatef(-40,10,0);
			glRotatef(180 ,1 ,0 ,0 );
			//ofDrawBitmapString("Card No."+ofToString(markerID),0 , 0);
		glPopMatrix();
		glPushMatrix();
			ofNoFill();
			ofSetColor(255, 255, 255);
			cardCharacter[4].draw(-20,-29,40,58); // draw card
		glPopMatrix();	
	}

	// draw attack front card
	else if(markerID==mIDcAtkFront)
	{

		glPushMatrix();
			ofSetLineWidth(5);
			ofNoFill();
			ofSetColor(255, 0, 0);
			glScalef(0.5,0.5,0.5);
			glTranslatef(-40,10,0);
			glRotatef(180 ,1 ,0 ,0 );
			//ofDrawBitmapString("Card No."+ofToString(markerID),0 , 0);
		glPopMatrix();
		glPushMatrix();
			ofNoFill();
			ofSetColor(255, 255, 255);
			cardAtk.draw(-20,-29,40,58); // draw card
		glPopMatrix();	
	}

	// draw suppor card
	else if(markerID==mIDscFront[0]) 
	{
		glPushMatrix();
			ofSetLineWidth(5);
			ofNoFill();
			ofSetColor(255, 0, 0);
			glScalef(0.5,0.5,0.5);
			glTranslatef(-40,10,0);
			glRotatef(180 ,1 ,0 ,0 );
			//ofDrawBitmapString("Card No."+ofToString(markerID),0 , 0);
		glPopMatrix();
		glPushMatrix();
			ofNoFill();
			ofSetColor(255, 255, 255);
			cardDef[0].draw(-20,-29,40,58); // draw card
		glPopMatrix();		
	}
		else if(markerID==mIDscFront[1]) 
	{
		glPushMatrix();
			ofSetLineWidth(5);
			ofNoFill();
			ofSetColor(255, 0, 0);
			glScalef(0.5,0.5,0.5);
			glTranslatef(-40,10,0);
			glRotatef(180 ,1 ,0 ,0 );
			//ofDrawBitmapString("Card No."+ofToString(markerID),0 , 0);
		glPopMatrix();
		glPushMatrix();
			ofNoFill();
			ofSetColor(255, 255, 255);
			cardDef[1].draw(-20,-29,40,58); // draw card
		glPopMatrix();		
	}
		else if(markerID==mIDscFront[2]) 
	{
		glPushMatrix();
			ofSetLineWidth(5);
			ofNoFill();
			ofSetColor(255, 0, 0);
			glScalef(0.5,0.5,0.5);
			glTranslatef(-40,10,0);
			glRotatef(180 ,1 ,0 ,0 );
			//ofDrawBitmapString("Card No."+ofToString(markerID),0 , 0);
		glPopMatrix();
		glPushMatrix();
			ofNoFill();
			ofSetColor(255, 255, 255);
			cardDef[2].draw(-20,-29,40,58); // draw card
		glPopMatrix();		
	}
	else if(markerID==mIDscFront[3]) 
	{
		glPushMatrix();
			ofSetLineWidth(5);
			ofNoFill();
			ofSetColor(255, 0, 0);
			glScalef(0.5,0.5,0.5);
			glTranslatef(-40,10,0);
			glRotatef(180 ,1 ,0 ,0 );
			//ofDrawBitmapString("Card No."+ofToString(markerID),0 , 0);
		glPopMatrix();
		glPushMatrix();
			ofNoFill();
			ofSetColor(255, 255, 255);
			cardDef[3].draw(-20,-29,40,58); // draw card
		glPopMatrix();		
	}

	// draw marker's vector of translation
	glPushMatrix();
		ofSetLineWidth(3);
		ofNoFill();
		//ofEnableAlphaBlending();    // turn on alpha blending
		ofSetColor(255, 0, 0);
		//ofRect(ofPoint(0 - 50/2.0,0 - 50/2.0), 50, 50);
		//ofDisableAlphaBlending();    // turn on alpha blending

		//vector<ofPoint> conner;
		//artk.getDetectedMarkerBorderCorners(mrIndex,conner);

		//ofSetLineWidth(3); // add by iiwudaffk
		//ofNoFill();
		//ofSetColor(255, 0, 0 );		
		//ofBeginShape();
		//ofVertex(conner[0].x, conner[0].y);
		//ofVertex(conner[1].x, conner[1].y);
		//ofVertex(conner[2].x, conner[2].y);
		//ofVertex(conner[3].x, conner[3].y);
		//ofEndShape(true);
		//

		/*
		glScalef(0.5,0.5,0.5);
		glTranslatef(-20,0,0);
		glRotatef(180 ,1 ,0 ,0 );
		*/

		//ofDrawBitmapString("Card No:"+ofToString(markerID)+"\nDetected :"+ofToString(mrIndex),-20 , -30);
		/*ofDrawBitmapString(ofToString(mTrans[mrIndex][0]) + 
		"\n" + ofToString(mTrans[mrIndex][1]) + 
		"\n" + ofToString(mTrans[mrIndex][2]),-10 , 0);*/
	glPopMatrix();

	// check if is [field card]
	if(markerID==mIDcField)
	{
		glPushMatrix();
			ofSetLineWidth(5);
			ofNoFill();		
			ofEnableSmoothing();
			ofEnableAlphaBlending();    // turn on alpha blending
			f1.drawField(); // call function draw field
			ofDisableAlphaBlending();   // turn off alpha
			ofNoFill();	

			glPushMatrix();
				ofSetColor(255, 0, 255);
				glScalef(0.5,0.5,0.5);
				glTranslatef(-40,10,0);
				glRotatef(180 ,1 ,0 ,0 );
				//ofDrawBitmapString("Card Field",0 , 0);
				if(gameState==1 && runtime)
				{
					it = 100;
					ofSetColor(255,0,0);
					glScalef(2,2,0);
					ofDrawBitmapString("Found Field Card", -50, -75.0 - (mw - 75)*1.5);
					ofDrawBitmapString("State Change to:" + ofToString(gameState), -50, 75.0 + (mw - 75)*1.5);
				}
				if(gameState==2 && runtime)
				{
					it = 100;
					ofSetColor(255,0,0);
					glScalef(2,2,0);
					ofDrawBitmapString("Set Character Card Done!!", -80, -75.0 - (mw - 75)*1.5);
					ofDrawBitmapString("State Change to:" + ofToString(gameState), -50, 75.0 + (mw - 75)*1.5);
				}
				if(gameState==3 && runtime)
				{
					it = 100;
					ofSetColor(255,0,0);
					glScalef(2,2,0);
					ofDrawBitmapString("Found Character Card!!", -70, -75.0 - (mw - 75)*1.5);
					ofDrawBitmapString("State Change to:" + ofToString(gameState), -50, 75.0 + (mw - 75)*1.5);
				}
				if(gameState==4 && runtime)
				{
					it = 100;
					ofSetColor(255,0,0);
					glScalef(2,2,0);
					ofDrawBitmapString("Set Support Card Done!!", -80, -75.0 - (mw - 75)*1.5);
					ofDrawBitmapString("State Change to:" + ofToString(gameState), -50, 75.0 + (mw - 75)*1.5);
				}
				if(gameState==5 && runtime)
				{
					it = 100;
					ofSetColor(255,0,0);
					glScalef(2,2,0);
					ofDrawBitmapString("Calculate Damage!!", -50, -75.0 - (mw - 75)*1.5);
					ofDrawBitmapString("State Change to:" + ofToString(gameState), -50, 75.0 + (mw - 75)*1.5);
				}
				if(gameState==6 && runtime)
				{
					it = 100;
					ofSetColor(255,0,0);
					glScalef(2,2,0);
					ofDrawBitmapString("Show Fighting !!", -50, -75.0 - (mw - 75)*1.5);
					ofDrawBitmapString("State Change to:" + ofToString(gameState), -50, 75.0 + (mw - 75)*1.5);
				}
				if(gameState==7 /*&& runtime*/)
				{
					//it = 100;
					ofSetColor(255,0,0);
					glScalef(2,2,0);
					ofDrawBitmapString("Game Over!!", -50, -75.0 - (mw - 75)*1.5);
					ofDrawBitmapString("State Change to:" + ofToString(gameState), -50, 75.0 + (mw - 75)*1.5);
				}
			glPopMatrix();	
		glPopMatrix();		
	}

	glPopMatrix();

}

//--------------------------------------------------------------
void testApp::drawEffect(int mIndex){
	artk.applyModelMatrix(mIndex);	
	glPushMatrix();
		ofSetLineWidth(1);
		ofEnableSmoothing();
		ofNoFill();
		ofEnableAlphaBlending();    // turn on alpha blending
		ofSetColor(255,238,98,230);
		glTranslatef(0,30 + effectx,70);
		glutSolidSphere(10,10,10);
		ofDisableAlphaBlending();    // turn off alpha blending
	glPopMatrix();
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
