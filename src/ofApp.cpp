#include "ofApp.h"
#include "ofxOpenCv.h"
#include "Aircraft.h"
//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);
    
    
    for (int i = 0; i < 5; i++)
    {
        radar.radarImg.load("radar.png");
        
        Aircraft plane;
        plane.setup();
        plane.planeID = "Aircraft" + to_string(i + 1);
        plane.setPos(ofRandom(100, 900), ofRandom(100, 700));
        
        Aircrafts.push_back(plane);
        
    }
    
}

//--------------------------------------------------------------
void ofApp::update()
{
    for (auto& plane : Aircrafts)
    {
        plane.updatePosition();
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
	//ofBackground(157);
	ofDrawBitmapString("Welcome To our Game", 10, ofGetHeight() /2);
    radar.Draw();

    for (const auto &plane : Aircrafts)
    {
        plane.draw();

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