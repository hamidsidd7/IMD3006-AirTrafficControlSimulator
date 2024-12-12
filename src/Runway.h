#pragma once
#include "ofMain.h"
#include "gameObject.h"

using namespace std;

class Runway : public gameObject
{
public:
    int id;
    string status; // "available", "occupied", "under maintenance"
    ofImage runwayImg;

    ofRectangle landingZone; 

    int  runwaysFree;
    void setup();
    void setStatus(const string newStatus);
    string getStatus();
    bool isAvailable();
    void Draw();
    int getRunwaysFree();
};
