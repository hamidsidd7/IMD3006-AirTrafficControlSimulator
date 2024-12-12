#pragma once
#include "gameObject.h"
#include "ofMain.h"
#include "Runway.h"
using namespace::std;



class Aircraft : public gameObject
{
public:
	ofVec2f position;
	float speed;
	float altitude;
	float fuelLevel;
	float directionAngle;
	string planeID;
	
	bool landing;
	bool deniedLanding;
	bool deniedTakeOff;

	Runway runway;
	
	AircraftState state;
	ofImage aircraftImg;
	void setup();
	void takeoff();
	void land();
	void setPos(int X, int Y);
	void updatePosition();
	bool checkCollision(const Aircraft& other);
	void Draw();
};

