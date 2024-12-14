#pragma once
#include "gameObject.h"
#include "Aircraft.h"
class Radar : public gameObject
{
public:
	
	ofRectangle boundaryBox;
	ofImage radarImg;

	void setup();
	
};

