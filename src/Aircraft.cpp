#pragma once
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
    colAircraftImg.load("planeCol.png");
    planeID = "Aircraft " + to_string((int)ofRandom(100,999));
    position.set(ofRandom(ofGetWindowWidth() / 2 + 100, ofGetWindowWidth() / 2 - 100),
        ofGetWindowHeight() / 2 - 200);
    directionAngle = ofRandom(0, 360) * DEG_TO_RAD;

    altitude = ofRandom(500, 10000); // Random altitude between 500 and 10,000 feet
    fuelLevel = ofRandom(50, 100);  // Random fuel level

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
    
}

//void Aircraft::updatePosition() {
//    switch (state)
//    {
//    case FLYING:
//        speed = ofRandom(0.2, 0.4); // Random speed when flying
//        break;
//    case TAKEOFF:
//        speed = 0.01;
//        break;
//    case LANDING:
//        speed = 0.03;
//        break;
//    case TAKENOFF:
//        speed = 1;
//        break;
//    default:
//        break;
//    }
//    position.x += speed * cos(directionAngle);
//    position.y += speed * sin(directionAngle);
//        
//        
//
//        float distanceFromCenter = ofDist(position.x, position.y, ofGetWindowWidth()/2, ofGetWindowHeight()/2);
//
//}

void Aircraft::updatePosition() {
    switch (state) {
    case FLYING:
        speed = ofRandom(0.2, 0.4); // Random speed while flying

        break;
    case TAKEOFF:
        speed = 0.03;
        altitude += ofRandom(1, 5); // Gradually increase altitude
     
        break;
    case LANDING:
        speed = 0.03;
        altitude -= ofRandom(1, 5); // Gradually decrease altitude
        if (altitude <= 0) {
            altitude = 0; // Ensure altitude does not go below zero
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

    // Update position
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

void Aircraft::Draw() {

    ofPushMatrix();


    ofTranslate(position.x, position.y);


    ofRotateRad(directionAngle + PI / 2);


    ofScale(0.03, 0.03);
    
    if (state == COLLISION)
    {
        colAircraftImg.draw(-aircraftImg.getWidth() / 2, -aircraftImg.getHeight() / 2);
    }
    else
    {
        
        aircraftImg.draw(-aircraftImg.getWidth() / 2, -aircraftImg.getHeight() / 2);
    }

    if (showCountdown)
    {
        ofSetColor(255, 0, 0);
        ofDrawBitmapStringHighlight("Divert in: " + to_string((int)ceil(divertCountdown)) + "s", position.x - 30, position.y - 50, ofColor(255, 0, 0));
        ofSetColor(255);
    }

    ofPopMatrix();


}
