#pragma once
#include "gameObject.h"
#include "Aircraft.h"
class Radar : public gameObject
{
public:
	Aircraft* trackedAircraft;
	
	ofImage radarImg;

	void setup();
	void update();
	void addAircraft(Aircraft* aircraft);
	void removeAircraft(int aircraftId);
	void display();
	void Draw();
	
};

