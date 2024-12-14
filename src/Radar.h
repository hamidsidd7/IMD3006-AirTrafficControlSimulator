#pragma once
#include "gameObject.h"
#include "Aircraft.h"
class Radar : public gameObject
{
public:
	
	
	ofImage radarImg;

	void setup();
	void update();
	void Draw();
	
};

