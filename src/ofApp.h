
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
		
		float windowWidth;
		float windowHeight;

		vector<Aircraft> Aircrafts;
		//vector<Aircraft> takeOffAircrafts;

		ofRectangle  boundaryBox;
		
		Runway runway;
		int runwayPosX;
		int runwayPosY;

		Radar radar;
		Model model;

		ofxImGui::Gui gui;
		void windowResized(int w, int h);

		void addAircraft();
		void removeAircraft();
		void handleCollisions();
		
		
};
