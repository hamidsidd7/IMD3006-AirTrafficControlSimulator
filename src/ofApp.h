
#include "Aircraft.h"
#include "Runway.h"
#include "ofMain.h"
#include "Radar.h"
#include "Model.h"



class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		vector<Aircraft> Aircrafts;
		Runway runway;
		Radar radar;
		Model model;

		void keyPressed(int key);
		void keyReleased(int key);
		void mousePressed(int x, int y, int button);

		void addAircraft();
		void removeAircraft();
		void handleCollisions();
		void manageRunways();
		
};
