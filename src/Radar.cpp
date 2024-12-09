#pragma once
#include "Radar.h"
void  Radar::setup()
{
	radarImg.load("radar");
}
void  Radar::update()
{

}
void Radar::addAircraft(Aircraft* aircraft)
{

}
void Radar::removeAircraft(int aircraftId)
{

}
void Radar::display()
{
	ofDrawCircle(ofGetWindowWidth() / 2, ofGetWindowHeight(), 50);
}
void Radar::Draw()
{
	radarImg.resize(ofGetWindowWidth(), ofGetWindowHeight());
	radarImg.draw(0, 0);

}



