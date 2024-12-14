#pragma once
#include "ofxImGui.h"
#include "Aircraft.h"
#include "Runway.h"

class UI
{
public:
    void setup();
    void draw(vector<Aircraft>& Aircrafts, Runway& runway, int planesTakenOff, int planesLanded, bool& lost, bool& instructions, bool& won);
    void handleInstructionsScreen(bool& instructions, ofImage& startScreen);
    void handleLossScreen(bool& lost, bool& won, ofImage& lossScreen, ofImage& winScreen);
    void handleGameUI(vector<Aircraft>& Aircrafts, Runway& runway, int planesTakenOff, int planesLanded, bool& lost);
    void drawPlaneManagementUI(vector<Aircraft>& Aircrafts, Runway& runway);

    ofSoundPlayer airTrafficSound;
    ofSoundPlayer planeSound;
    ofSoundPlayer emergencySound;

    ofImage startScreen;
    ofImage winScreen;
    ofImage lossScreen;
    
    bool instructions;
    bool retry;

    int planesTakenOff;
    int planesLanded;

    ofxImGui::Gui gui;
};
