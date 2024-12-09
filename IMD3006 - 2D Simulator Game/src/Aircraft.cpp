#include "ofMain.h"
#include "Aircraft.h"
using namespace::std;

void Aircraft::setup ()
{
    speed = ofRandom(1,3);
    float initSpeed = 0;
    float initAltitude = 0;
    float initFuel = 0;
    aircraftImg.load("plane");
    planeID = "Null";
    position.set(0, 0);
    
}
void Aircraft::takeoff()
{
    
}

void Aircraft::land()
{
    
}

void Aircraft::updatePosition() {
    
    position.x += speed;

    if (position.x > ofGetWindowWidth() || position.x < 0) {
        speed = -speed; 
    }

}

bool Aircraft::checkCollision(const Aircraft& other)
{
    return false;
}

void Aircraft::setPos(int X, int Y)
{
    position.x = X;
    position.y = Y;
}

void Aircraft::draw() const {
    ofSetColor(255, 0, 0);
    ofDrawCircle(position.x, position.y, 10);
    ofSetColor(255);
}