#include "Runway.h"

void Runway::setup() {
    status = "available";
    id = 0;
    runwayImg.load("runway.png");



    float runwayWidth = runwayImg.getWidth() * 0.2;
    float runwayHeight = runwayImg.getHeight() * 0.2;

    float zoneWidth = runwayWidth + 20;
    float zoneHeight = runwayHeight;

    zoneX = ofGetWindowWidth();
    zoneY = ofGetWindowHeight();

    landingZone.set((ofGetWindowWidth() / 3), ofGetWindowHeight() / 2, zoneWidth, zoneHeight);

    runwaysFree = 6;
}

int Runway::getRunwaysFree()
{
    return runwaysFree;
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
    ofPushMatrix();
    // ofTranslate(zoneX, zoneY);
    ofScale(0.2, 0.2);
    //runwayImg.resize(ofGetWindowWidth(), ofGetWindowHeight());
    runwayImg.draw(0, 0);

    ofPopMatrix();



}