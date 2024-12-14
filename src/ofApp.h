#include "Aircraft.h"
#include "Runway.h"
#include "ofMain.h"
#include "Radar.h"
#include "main.h"




class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		
		float windowWidth;
		float windowHeight;

		vector<Aircraft> Aircrafts;
		
		ofImage startScreen;
		ofImage lossScreen;

		ofSoundPlayer airTrafficSound;
		ofSoundPlayer planeSound;
		ofSoundPlayer emergencySound;

		ofRectangle  boundaryBox;
		
		Runway runway;
		int runwayPosX;
		int runwayPosY;

		Radar radar;

		int planesLanded;
		int planesTakenOff;

		bool won;
		
		bool instructions;
		bool lost;

		ofxImGui::Gui gui;
		void windowResized(int w, int h);

		void addAircraft();
		void handleCollisions();
		void keyPressed(int key);
		void resetGame();
		
		
		
};
