#pragma once
#include "gameObject.h"
#include "Aircraft.h"
class Radar : public gameObject
{
private:
	Aircraft* trackedAircraft;
public:
	Radar();
	void addAircraft(Aircraft* aircraft);
	void removeAircraft(int aircraftId);
	void display();
};

