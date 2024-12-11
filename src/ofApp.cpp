#include "ofApp.h"
#include "ofxOpenCv.h"
#include "Aircraft.h"
//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);
    //ofToggleFullscreen();
    runway.setup();
    radar.setup();

    runwayPosX = runway.runwayImg.getWidth() / 2;
    runwayPosY = runway.runwayImg.getHeight() / 2;
    for (int i = 0; i < 10; i++)
    {
        //radar.radarImg.load("radar.png");
        
        Aircraft plane;
        plane.setup();
        plane.planeID = "Aircraft" + to_string(i + 1);
        plane.setPos(ofRandom(100, 900), ofRandom(100, 700));
        
        Aircrafts.push_back(plane);

       if (plane.y < runwayPosY + 150 || plane.x < runwayPosX + 150)
        {
            plane.state =  LANDING;
        }
        
    }
    
}

//--------------------------------------------------------------
void ofApp::update()
{
    
    auto currPlane = Aircrafts.begin();
    while (currPlane != Aircrafts.end())
    {
       
        currPlane->updatePosition();

      
        if (currPlane->position.y < ofGetWindowHeight() - 668 || currPlane->position.y > ofGetWindowHeight() - 150 ||
            currPlane->position.x < (ofGetWindowWidth() / 2) - 200 || currPlane->position.x >(ofGetWindowWidth() / 2) + 170)
        {
            currPlane = Aircrafts.erase(currPlane); 
        }
        else
        {
            ++currPlane; 
        }
    }
        if (Aircrafts.size() < 10) {
            Aircraft newPlane;
            newPlane.setup();
            Aircrafts.push_back(newPlane);
        }
    
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(157);
	ofDrawBitmapString("Welcome To our Game", 10, ofGetHeight() /2);
    radar.Draw();
    ofPushMatrix();
    runway.Draw();
    ofPopMatrix();

    for (auto &plane : Aircrafts)
    {
        int Speed = (int)plane.speed;
        cout << Speed;
        plane.Draw();

    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::addAircraft()
{
    //use linked lists to add new aircrafts
}

//--------------------------------------------------------------
void ofApp::removeAircraft()
{
    //use linked lists to remove aircrafts

}

//--------------------------------------------------------------
void ofApp::handleCollisions() 
{
    //logic to handle collisions between planes
}

//--------------------------------------------------------------
void ofApp::manageRunways() 
{
   //logic to handle runways
}

