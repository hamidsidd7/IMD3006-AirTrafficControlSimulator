#pragma once
#include "Aircraft.h"
#include "Runway.h"
#include "ofMain.h"
#include "Radar.h"



class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		Aircraft* AircraftList;
		Runway* runways;
		Radar radar;

		void keyPressed(int key);
		void keyReleased(int key);
		void mousePressed(int x, int y, int button);

		void addAircraft();
		void removeAircraft();
		void handleCollisions();
		void manageRunways();
		
};
