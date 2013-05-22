#ifndef _TEST_APP
#define _TEST_APP

#include "ofxOpenCv.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "ofxARToolkitPlus.h"
#include "ofVectorMath.h"
#include "ofx3DModelLoader.h"
#include "ofMain.h"
#include "glut.h"
#include "powercard.h"
//#include <fstream>
using namespace std;

// Uncomment this to use a camera instead of a video file
#define CAMERA_CONNECTED

class testApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	// draw graphic object static on marker
	void drawAR(int markerIndex,int mrIndex);
	void drawAR(int markerID,int mrIndex,string mname);

	// draw graphic effect
	void drawEffect(int mIndex);

	// find index of first value to match input ,return -1 if no match
	int findIndex (vector<int> series, int v);

	// calculate distance between 2 marker
	//float calDistance(ofPoint p1,ofPoint p2);

	void keyPressed (int key);

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
	//ofx3DModelLoader mAss;

	// use threshold
	bool pict;

	// show detail
	bool dtext;

	// show draw ar
	bool ar;

	// show hp bar
	bool hpbar;

	// depth
	bool dep;

	// field info
	bool fmaker;

	// game state number
	int gameState;
	/* 
	* 0 = open program first time ,found field card => 1
	* 1 = found field marker ,wait: p1 set character back card && p2 set character back card => 2
	* 2 = set character back card done ,wait: p1 flip card to front  && p2 flip card to front => 3
	* 3 = set character card done ,wait: pATK set back attack card && pDEF set back support card => 4
	* 4 = set back support card done ,wait: pATK and pDEF flip card to front => 5
	* 5 = fighting turn and calculate damage ,wait: time delay => 6
	* 6 = show effect and calculate player hp ,wait: if any pHP !=0 => 3 else => 7
	* 7 = got winner and game end
	*/
	
	// create field
	Field f1;
	int d1;

	// nearest marker and field
	int nearField;
	float dm;
	float distanceSet;

	// Image back card
	ofImage cardBackImage;

	// Image field card
	ofImage cardFieldImage;

	ofImage cardCharacter[5];
	ofImage cardDef[4];
	ofImage cardAtk;


	// Player for play
	Player PL;
	Player PR;

	// all character card
	Character c1;
	Character c2;
	Character c3;
	Character c4;
	Character c5;
	vector<Character> clist;

	// model for character card
	ofx3DModelLoader mc1;
	ofx3DModelLoader mc2;
	ofx3DModelLoader mc3;
	ofx3DModelLoader mc4;
	ofx3DModelLoader mc5;
	vector<ofx3DModelLoader> mclist;

	// all support card
	Card sc1;
	Card sc2;
	Card sc3;
	Card sc4;
	vector<Card> sclist;

	// make card list
	//vector<Character> cardlist;
	// make support card list
	//vector<Card> scardlist;

	// Class Calculate Damage
	CalculateDmg CalDmg;

	// markers to use
	int mIDcField;
	int mIDcBack;
	int mIDscBack;
	int mIDcAtkFront;
	vector<int> mIDcFront;
	vector<int> mIDscFront;

	// list of marker id for detected
	vector<int> mID;
	// list of marker translation
	vector<ofPoint> mTrans;

	// wait time
	int wt;
	int it;
	bool runtime;

	// animation effect
	bool effectrun;
	int effecttime;
	int effectx;

	// show damage
	bool effectrun2;
	int effecttime2;
	int effectshow;

	bool showhpdone;
	bool showhpdone2;


	// scale for all marker graphic
	float mw;
	float mh;

	// color for Player's HP bar
	ofColor co0;
	ofColor co1;
	ofColor co2;

	//ofRandom ran;

	// use true type font
	ofTrueTypeFont font[3];


};

#endif
