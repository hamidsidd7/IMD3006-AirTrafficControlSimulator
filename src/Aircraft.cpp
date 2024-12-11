#include "ofMain.h"
#include "Aircraft.h"
using namespace::std;

void Aircraft::setup ()
{
    speed = ofRandom(0.2,0.4);
    float initSpeed = 0;
    float initAltitude = 0;
    float initFuel = 0;
    aircraftImg.load("plane.png");
    planeID = "Null";
    position.set(ofRandom(ofGetWindowWidth() / 2 + 100, ofGetWindowWidth() / 2 - 100),
        ofGetWindowHeight() / 2 - 200);
    directionAngle = ofRandom(0, 360) * DEG_TO_RAD;
}
/*void Aircraft::takeoff()
{
    state = FLYING;
}

void Aircraft::land()
{
   
    state = LANDING;
    speed = 0;
}*/

void Aircraft::updatePosition() {
   // if (state == FLYING) 
   // {
    
        position.x += speed * cos(directionAngle);
        position.y += speed * sin(directionAngle);
        
        

        float distanceFromCenter = ofDist(position.x, position.y, ofGetWindowWidth()/2, ofGetWindowHeight()/2);

      

   // }
}

bool Aircraft::checkCollision(const Aircraft& other) 
{
    float distance = position.distance(other.position); 
    return distance < 20; 
}

void Aircraft::setPos(int X, int Y)
{
    position.x = X;
    position.y = Y;
}

void Aircraft::Draw() {

    ofPushMatrix();


    ofTranslate(position.x, position.y);


    ofRotateRad(directionAngle + PI / 2);


    ofScale(0.03, 0.03);


    aircraftImg.draw(-aircraftImg.getWidth() / 2, -aircraftImg.getHeight() / 2);

    ofPopMatrix();
}