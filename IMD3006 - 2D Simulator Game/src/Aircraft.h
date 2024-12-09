#pragma once
#include "gameObject.h"
#include "ofMain.h"
using namespace::std;



class Aircraft : public gameObject
{
public:
	ofVec2f position;
	float speed;
	float altitude;
	float fuelLevel;
	string planeID;
	
	Aircraft* next = NULL;
	ofImage aircraftImg;
	void setup();
	void takeoff();
	void land();
	void setPos(int X, int Y);
	void updatePosition();
	bool checkCollision(const Aircraft& other);
	void draw() const;
};

