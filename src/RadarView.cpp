#include "RadarView.h"
void RadarView::Draw(const Radar& Radar)
{
	Radar.radarImg.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
}