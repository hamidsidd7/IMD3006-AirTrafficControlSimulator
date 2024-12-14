#include "AircraftView.h"

void AircraftView::Draw(const Aircraft& plane)
{

    ofPushMatrix();


    ofTranslate(plane.position.x, plane.position.y);


    ofRotateRad(plane.directionAngle + PI / 2);


    ofScale(0.03, 0.03);

    if (plane.showCountdown)
    {
        plane.colAircraftImg.draw(-plane.aircraftImg.getWidth() / 2, -plane.aircraftImg.getHeight() / 2);
        ofSetColor(255, 0, 0);
        ofDrawBitmapStringHighlight("Divert in: " + to_string((int)ceil(plane.divertCountdown)) + "s", plane.position.x - 30, plane.position.y - 50, ofColor(255, 0, 0));
        ofSetColor(255);
    }
    else 
    {
        plane.aircraftImg.draw(-plane.aircraftImg.getWidth() / 2, -plane.aircraftImg.getHeight() / 2);
    }

    

    ofPopMatrix();
    
    if (plane.state == LANDING || plane.state == TAKEOFF)
    {
        ofSetColor(255, 255, 255);
        ofDrawBitmapString(plane.planeID + " is requesting " +
            (plane.state == LANDING ? "to land" : "takeoff"),
            plane.position.x, plane.position.y - 20);
    }

}

