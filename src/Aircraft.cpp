#pragma once
#include "ofMain.h"
#include "Aircraft.h"

using namespace::std;

void Aircraft::setup ()
{
    state = FLYING;
    float initSpeed = 0;
    float initAltitude = 0;
    aircraftImg.load("plane.png");
    colAircraftImg.load("planeCol.png");
    planeID = "Aircraft " + to_string((int)ofRandom(100,999));
    position.set(ofRandom(ofGetWindowWidth() / 2 + 100, ofGetWindowWidth() / 2 - 100),
        ofGetWindowHeight() / 2 - 200);
    directionAngle = ofRandom(0, 360) * DEG_TO_RAD;

    altitude = ofRandom(500, 10000); 


    landing = false;
    deniedLanding = false;
    deniedTakeOff = false;
    runway.setup();
    diverted = false;
    color = false;

    horizontalDistance = 0.0f;
    altitudeDifference = 0.0f;


    proximityThreshold = 80.0f;
    altitudeThreshold = 500.0f;
    divertCountdown = 0;
    showCountdown = false;

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
    runway.runwaysFree++;
    
}

void Aircraft::addAircraft(vector<Aircraft>& Aircrafts)
{


    Aircraft newPlane;
    newPlane.setup();


    int x = ofRandom(runway.landingZone.getX(), runway.landingZone.getX() + runway.landingZone.getWidth());
    int y = ofRandom(runway.landingZone.getY(), runway.landingZone.getY() + runway.landingZone.getHeight());
    newPlane.position.set(x, y);
    newPlane.updatePosition();

    newPlane.state = TAKEOFF;



    Aircrafts.push_back(newPlane);
}

void Aircraft::updatePosition() 
{
    switch (state) 
    {
    case FLYING:
        speed = ofRandom(0.2, 0.4); 

        break;
    case TAKEOFF:
        speed = 0.03;
        altitude += ofRandom(1, 5); 
     
        break;
    case LANDING:
        speed = 0.03;
        altitude -= ofRandom(1, 5);
        if (altitude <= 0)
        {
            altitude = 0; 
        }

       
        break;
    case TAKENOFF:
        speed = 1.0;
        
        break;
    case COLLISION:
        speed = 0.01;
        showCountdown = true;
        break;
    default:
        showCountdown = false;
        break;
    }

    position.x += speed * cos(directionAngle);
    position.y += speed * sin(directionAngle);
}

bool Aircraft::checkCollision(const Aircraft& other) 
{
       horizontalDistance = position.distance(other.position);
       altitudeDifference = abs(altitude - other.altitude);


       proximityThreshold = 80.0f;
       altitudeThreshold = 300.0f;

        return horizontalDistance < proximityThreshold && altitudeDifference < altitudeThreshold;
}

void Aircraft::setPos(int X, int Y)
{
    position.x = X;
    position.y = Y;
}


