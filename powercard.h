#ifndef _POWERCARD
#define _POWERCARD

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
//#include <random>
//#include <functional>
//#include <time.h>

#include "ofMain.h"
#include "glut.h"

float calDistance(ofPoint p1,ofPoint p2);

class Player
{
private:
	// Player's Attack
	int patk;

	// Player's Defence
	int pdef;

	// Player hit point
	int php;

	// Player status
	bool pAlive;

	// Player turn
	bool pTurn;

	// set hit point
	void setHP(int hp);

public:
	Player();
	Player(int atk,int def,int hp);
	~Player();

	// return Player's Attack
	int atk();

	// return Player's Defence
	int def();

	// return current Player's hit point
	int hp();

	// return Player's status :true if alive,else die
	bool isAlive();

	// check is this player's turn
	bool isTurn();

	// set Player's Attack
	void setATK(int atk);

	// set Player's Defence
	void setDEF(int def);

	// set Player's Turn
	void setTurn(bool play);

	// calculate hit point from damage if dmg>=HP Player will die
	void calculateHP(int dmg);

};

class CalculateDmg
{
private:
	// Attacker's Damage
	int pAtkDmg;

	// Defender's Damage
	int pDefDmg;
public:
	CalculateDmg();
	CalculateDmg(int p1dmg,int p2dmg);
	~CalculateDmg();

	// return Attacker's Damage;
	int paDmg(); 
	
	// return Defender's Damage;
	int pdDmg(); 

	// call function by number
	void cTdef(int num,int p1atk,int p2def);

	// set Attacker's Damage
	void setPAtkDmg(int dmg);

	// set Defender's Damage
	void setPDefDmg(int dmg);

	// Defender got damage as full attack
	void defMiss(int atk);

	// Defender got any damage as attack had decreased by defense
	void defValue(int p1atk,int p2def);
	
	// Both Player got 0 damage
	void defATKMiss(); 
	
	// Defender got damage equal half of attack and return another attack back to attacker
	void defReturn(int p1atk);
};

class Field
{	
	/*
	* 0 = card field
	* 1 = (0.x -a , 0.y +b)
	* 2 = (0.x -a , 0.y)
	* 3 = (0.x -a , 0.y -b)
	* 4 = (0.x +a , 0.y +b)
	* 5 = (0.x +a , 0.y)
	* 6 = (0.x +a , 0.y -b)
	* 7 = (0.x , 0.y -b)
	* 8 = (0.x , 0.y +b)

	|=====|=====|=====|
	|  1  |  7  |  4  |
	|=====|=====|=====|
	|  2  |  0  |  5  |
	|=====|=====|=====|
	|  3  |  8  |  6  |
	|=====|=====|=====|

	*/

	// define data struct myField
	struct myField
	{
		ofPoint fPos;
		int fSetByMarkerID;
	};
private:
	// field slot[9]
	myField field[9];

public:
	Field();
	//Field(int initMarkerID);
	Field(int initMarkerID,ofPoint markerTransInitMarkerID);
	~Field();

	// return position of field[fNo].fPos
	ofPoint getfPos(int fNo);

	// return marker ID as set to card field
	int getMarkerIDsetted(int fNo);

	// check Field slot if empty return true
	bool isEmpty(int fNo);

	// set marker ID to card field slot,return current fNo's mID if fNo not empty
	int setFieldByMarkerID(int fNo,int mID);

	// set -1 to card field[fNo].fSetByMarkerID
	void setFMisEmpty(int fNo);

	// set all data in card field slot into initial value
	void clearAll();

	// calculate position of field while marker move
	void updateCardFieldPosition(ofPoint markerTrans);

	// return index of field position as nearest between marker and all field position
	int findNearestFieldAndMaker(ofPoint pMarker);

	// count marker id in field->fSetByMarkerID
	int countIDMarker(int id);

	// print marker id
	void printMID();


};

class Card{
protected:
	// Character name
	string cName;
	// front card is marker id
	int cMIDFront;
	// back card is marker id
	int cMIDBack;

public:
	Card::Card();
	Card::~Card();

	// draw graphic on marker's front card
	void drawFrontCard();
	// draw graphic on marker's back card
	void drawBackCard();
	// draw grahpic
	void drawEffectCard();
	
	void setCName(string name);
	void setmIDFront(int markerID);
	void setmIDBack(int markerID);
	
	// return card name
	string Cname();
	// return marker id's card front
	int cmIdFront();
	// return marker id's card back
	int cmIdBack();
};

class Character : public Card
{
protected:

	// Character's attack power
	int cATK;
	// Character's defence power
	int cDEF;
	// Character's attack rating
	float cAtkRate[10];
public:
	Character();
	~Character();

	void setATK(int a);
	void setDEF(int d);
	void setAtkRate(float r[]);

	// get card's attack power
	int atk();
	// get card's defence power
	int def();	
	// generate attack rating by random
	float atkRate();
	// get attack rating
	void getAtkRating(float ar[]);
};


#endif