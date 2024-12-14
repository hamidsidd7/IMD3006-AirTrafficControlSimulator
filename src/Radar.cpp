#pragma once
#include "Radar.h"
void  Radar::setup()
{
	radarImg.load("radar.png");
	int width = radarImg.getWidth();
	int height = radarImg.getHeight();
	boundaryBox.set(ofGetWindowWidth() / 2.5, ofGetWindowHeight() / 3, 400, 400);
	boundaryBox.scaleFromCenter(2, 2);
}




