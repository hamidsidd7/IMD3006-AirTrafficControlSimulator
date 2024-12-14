#pragma once
#include "Radar.h"
void  Radar::setup()
{
	radarImg.load("radar.png");
}
void  Radar::update()
{

}
void Radar::Draw()
{
	radarImg.resize(ofGetWindowWidth(), ofGetWindowHeight());
	radarImg.draw(0, 0);


}



