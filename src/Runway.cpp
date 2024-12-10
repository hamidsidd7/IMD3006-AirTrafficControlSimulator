#include "Runway.h"

void Runway::setup()
{
	//next = NULL;
	status = "available";
	id = 0;
	runwayImg.load("runway.png");
	landImg.load("land.png");
}

void Runway::setStatus(const string newStatus)
{

}



string Runway::getStatus()
{
	return "NULL";
}
bool Runway::isAvailable()
{
	return true;
}

void Runway::Draw()
{
	ofScale(0.2, 0.2);
	//runwayImg.resize(ofGetWindowWidth(), ofGetWindowHeight());
	runwayImg.draw(ofGetWindowWidth() + 1000, ofGetWindowHeight() + 1000);
	
	
}