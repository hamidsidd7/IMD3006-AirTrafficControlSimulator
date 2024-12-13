
#include "Aircraft.h"
#include "Runway.h"
#include "ofMain.h"
#include "Radar.h"
#include "Model.h"
#include "ofxImGui.h"



class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		vector<Aircraft> Aircrafts;
		//vector<Aircraft> takeOffAircrafts;
		
		Runway runway;
		int runwayPosX;
		int runwayPosY;

		Radar radar;
		Model model;

		ofxImGui::Gui gui;
		void keyPressed(int key);
		void keyReleased(int key);
		void mousePressed(int x, int y, int button);

		void addAircraft();
		void removeAircraft();
		void handleCollisions();
		void manageRunways();
		
};
