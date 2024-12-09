#pragma once
#include "Aircraft.h"
#include "Runway.h"
#include "Radar.h"
class Model
{
public:
	Aircraft aircraft;
	Runway runway;
	Radar radar;

	void setup();
	

};

