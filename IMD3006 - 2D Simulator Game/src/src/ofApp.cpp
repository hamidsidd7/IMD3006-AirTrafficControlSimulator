#include "ofApp.h"
#include "ofxOpenCv.h"
#include "Aircraft.h"
//--------------------------------------------------------------
void ofApp::setup()
{
    AircraftList = new Aircraft();
}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(0);
	ofDrawBitmapString("Welcome To our Game", 10, ofGetHeight() /2);

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