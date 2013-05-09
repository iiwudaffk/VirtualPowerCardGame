#include "powercard.h"

float calDistance(ofPoint p1,ofPoint p2){

	return abs((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

////////////////////////////////////////////
// Class Player
////////////////////////////////////////////
Player::Player(){
	setATK(0);
	setDEF(0);
	setHP(100);
}

Player::Player(int atk,int def,int hp){
	setATK(atk);
	setDEF(def);
	setHP(hp);
	pAlive = true;
}

Player::~Player(){
	setATK(0);
	setDEF(0);
	setHP(0);
	pAlive = false;
}

int Player::atk(){return this->patk;}
int Player::def(){return this->pdef;}
int Player::hp(){return this->php;}
bool Player::isAlive(){return this->pAlive;}
bool Player::isTurn(){return this->pTurn;}
void Player::setATK(int atk){this->patk = atk;}
void Player::setDEF(int def){this->pdef = def;}
void Player::setHP(int hp){this->php = hp;}
void Player::setTurn(bool play){this->pTurn = play;}

void Player::calculateHP(int dmg){
	if(php<=dmg)
	{	
		setHP(0);
		pAlive = false;	
	}else
	{	
		setHP(php - dmg);
		pAlive = true; 
	}
}
//////////////////////////////////////////

////////////////////////////////////////////
// Class CalculateDmg
////////////////////////////////////////////
CalculateDmg::CalculateDmg(){
	CalculateDmg(0,0);
}

CalculateDmg::CalculateDmg(int p1dmg,int p2dmg){
	setPAtkDmg(p1dmg);
	setPDefDmg(p2dmg);
}

CalculateDmg::~CalculateDmg(){
	CalculateDmg(0,0);
}

void CalculateDmg::setPAtkDmg(int dmg){
	this->pAtkDmg = dmg;
}

void CalculateDmg::setPDefDmg(int dmg){
	this->pDefDmg = dmg;
}

int CalculateDmg::paDmg(){
	return this->pAtkDmg;
}

int CalculateDmg::pdDmg(){
	return this->pDefDmg;
}

void CalculateDmg::cTdef(int num,int p1atk,int p2def){
	if(num==11){defMiss(p1atk);}
	if(num==12){defValue(p1atk,p2def);}
	if(num==13){defATKMiss();}
	if(num==14){defReturn(p1atk);}
}

void CalculateDmg::defMiss(int atk){
	this->setPAtkDmg(0);
	this->setPDefDmg(atk);
}

void CalculateDmg::defValue(int p1atk,int p2def){
	if(p2def>p1atk)
	{	this->setPAtkDmg(p2def-p1atk);	
		this->setPDefDmg(0);	}
	else
	{	this->setPAtkDmg(0);
		this->setPDefDmg(p1atk-p2def);	}
}

void CalculateDmg::defATKMiss(){
	this->setPAtkDmg(0);
	this->setPDefDmg(0);
}

void CalculateDmg::defReturn(int p1atk){
	this->setPAtkDmg(floor((p1atk/2.0)+0.5));
	this->setPDefDmg(floor((p1atk/2.0)+0.5));
}
//////////////////////////////////////////

////////////////////////////////////////////
// Class Field
////////////////////////////////////////////
Field::Field(){
	this->clearAll();
}

//Field::Field(int initMarkerID){
//	Field::Field(initMarkerID,ofPoint(0,0,0));
//}

Field::Field(int initMarkerID,ofPoint markerTransInitMarkerID){
	field[0].fSetByMarkerID = initMarkerID;
	for(int i=1;i<9;i++)
	{
		field[i].fSetByMarkerID = (-1);
	}
	Field::updateCardFieldPosition(markerTransInitMarkerID);
}

Field::~Field(){
	
	for(int i=0;i<9;i++)
	{
		field[i].fPos = ofPoint(-1,-1,-1);
		field[i].fSetByMarkerID = -1;
	}
};

ofPoint Field::getfPos(int fNo){
	return this->field[fNo].fPos;
}

int Field::getMarkerIDsetted(int fNo){
	return this->field[fNo].fSetByMarkerID;
}

bool Field::isEmpty(int fNo){
	return (field[fNo].fSetByMarkerID == -1)? true:false;
}

int Field::setFieldByMarkerID(int fNo,int mID){
	if(isEmpty(fNo))
	{
		field[fNo].fSetByMarkerID = mID;
		//cout<<"set card "<<mID<<", to Field "<<fNo<<" done"<<endl;
		return -1;
	}
	else
	{
		//cout<<"cannot set card "<<mID<<", to Field "<<fNo<<endl;
		return field[fNo].fSetByMarkerID;
	}
}

void Field::setFMisEmpty(int fNo){
	if(!isEmpty(fNo)) 
	{field[fNo].fSetByMarkerID=-1;}
}

void Field::clearAll(){
	this->~Field();
}

void Field::updateCardFieldPosition(ofPoint markerTrans){
	this->field[0].fPos = markerTrans;

	this->field[1].fPos = ofPoint(markerTrans.x-50,markerTrans.y-50,markerTrans.z);
	this->field[2].fPos = ofPoint(markerTrans.x-50,markerTrans.y,markerTrans.z);
	this->field[3].fPos = ofPoint(markerTrans.x-50,markerTrans.y+50,markerTrans.z);

	this->field[4].fPos = ofPoint(markerTrans.x+50,markerTrans.y-50,markerTrans.z);
	this->field[5].fPos = ofPoint(markerTrans.x+50,markerTrans.y,markerTrans.z);
	this->field[6].fPos = ofPoint(markerTrans.x+50,markerTrans.y+50,markerTrans.z);

	this->field[7].fPos = ofPoint(markerTrans.x,markerTrans.y-50,markerTrans.z);
	this->field[8].fPos = ofPoint(markerTrans.x,markerTrans.y+50,markerTrans.z);
}

int Field::findNearestFieldAndMaker(ofPoint pMarker){
	float nearest1 = 9999999;
	float nearest2 = 0;
	int index = 0;

	for(int i=1;i<9;i++)
	{
		nearest2 = calDistance(this->field[i].fPos,pMarker);
		//cout<<"near f["<<i<<"] : "<<nearest2<<endl;
		if(nearest2<nearest1)
		{
			nearest1 = nearest2;
			index = i;
		}
	}
	
	return index;
}

int Field::countIDMarker(int markerID){
	int c = 0;
	int s = sizeof(field)/sizeof(field[0]);
	cout<<"-------------------"<<endl;
	cout<<"sizeof(arr) : "<<sizeof(field)<<endl;
	cout<<"sizeof(*arr) : "<<sizeof(*field)<<endl;
	cout<<"sizeof(arr[0]) : "<<sizeof(field[0])<<endl;
	cout<<"sizeof(&arr) : "<<sizeof(&field)<<endl;
	cout<<"sizeof(arr) : "<<s<<endl;
	
	for (int i=0; i<(s); i++)
	{
		if(field[i].fSetByMarkerID == markerID) c++;
		cout<<"i : "<<i<<", ID : "<<field[i].fSetByMarkerID<<endl;
	}
	cout<<"-------------------"<<endl;
	return c;
}

void Field::printMID(){

	cout<<"---------fSetByMarkerID----------"<<endl;
	for (int i=0; i<9; i++)
	{
		cout<<"i : "<<i<<", ID : "<<field[i].fSetByMarkerID<<endl;
	}
	cout<<"---------fSetByMarkerID----------"<<endl;
}
////////////////////////////////////////////

////////////////////////////////////////////
// Class Card
////////////////////////////////////////////
Card::Card(){}
Card::~Card(){}
void Card::setCName(string name){this->cName = name;}
void Card::setmIDFront(int markerID){this->cMIDFront = markerID;}
void Card::setmIDBack(int markerID){this->cMIDBack = markerID;}
string Card::Cname(){return this->cName;}
int Card::cmIdFront(){return this->cMIDFront;}
int Card::cmIdBack(){return this->cMIDBack;}
void Card::drawFrontCard(){}
void Card::drawBackCard(){}
void Card::drawEffectCard(){}
////////////////////////////////////////////

////////////////////////////////////////////
// Class Character extend
////////////////////////////////////////////
Character::Character(){

}

Character::~Character(){

}

void Character::setATK(int a){this->cATK = a;}
void Character::setDEF(int d){this->cDEF = d;}
void Character::setAtkRate(float r[]){memcpy(this->cAtkRate,r,10);}
int Character::atk(){return this->cATK;}
int Character::def(){return this->cDEF;}
void Character::getAtkRating(float ar[]){memcpy(ar,this->cAtkRate,10);}
float Character::atkRate(){ 
	int a = floor(ofRandom(11));
	return this->cAtkRate[a];
}

	
////////////////////////////////////////////


