#pragma once
#include "ofMain.h"
#include "Aircraft.h"
#include "Runway.h"
#include "RunwayView.h"
#include "Radar.h"
#include "RadarView.h"
#include "AircraftView.h"
#include "UI.h"

class GameController 
{
public:
    vector<Aircraft> Aircrafts;
    Aircraft plane;
    Runway runway;
    Radar radar;

    RunwayView runwayV;
    RadarView radarV;
    AircraftView aircraftView;
    UI ui; // GameController will now handle UI

    bool won;
    
    bool lost;


    void setup();
    void update();
    void draw();
    void handleKeyPress(int key);
    void resetGame();
};
