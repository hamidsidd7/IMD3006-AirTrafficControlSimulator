#include "ofMain.h"
#include "Aircraft.h"
using namespace::std;

void Aircraft::setup ()
{
    state = FLYING;
    float initSpeed = 0;
    float initAltitude = 0;
    float initFuel = 0;
    aircraftImg.load("plane.png");
    planeID = "Aircraft " + to_string((int)ofRandom(100,999));
    position.set(ofRandom(ofGetWindowWidth() / 2 + 100, ofGetWindowWidth() / 2 - 100),
        ofGetWindowHeight() / 2 - 200);
    directionAngle = ofRandom(0, 360) * DEG_TO_RAD;

    landing = false;
    deniedLanding = false;
    deniedTakeOff = false;
    runway.setup();
}
void Aircraft::takeoff()
{
    deniedTakeOff = false;
    state = TAKENOFF;
    runway.runwaysFree--;
}

void Aircraft::land()
{
    landing = true;
    state = LANDING;
    
}

void Aircraft::updatePosition() {
    switch (state)
    {
    case FLYING:
        speed = ofRandom(0.2, 0.4); // Random speed when flying
        break;
    case TAKEOFF:
        speed = 0.01;
        break;
    case LANDING:
        speed = 0.03;
        break;
    case TAKENOFF:
        speed = 1;
        break;
    default:
        break;
    }
    position.x += speed * cos(directionAngle);
    position.y += speed * sin(directionAngle);
        
        

        float distanceFromCenter = ofDist(position.x, position.y, ofGetWindowWidth()/2, ofGetWindowHeight()/2);

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
