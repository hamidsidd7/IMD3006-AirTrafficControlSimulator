#include "Runway.h"

void Runway::setup() {
    status = "available";
    id = 0;
    runwayImg.load("runway.png");
   
    

    float runwayWidth = runwayImg.getWidth() * 0.2; 
    float runwayHeight = runwayImg.getHeight() * 0.2;

    float zoneWidth = runwayWidth + 20;
    float zoneHeight = runwayHeight;

    float zoneX = ofGetWindowWidth() / 2 - 120;
    float zoneY = ofGetWindowHeight() / 2 - 20;

    

    landingZone.set(zoneX, zoneY, zoneWidth, zoneHeight);
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