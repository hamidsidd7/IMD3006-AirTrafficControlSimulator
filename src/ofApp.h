#pragma once
#include "ofMain.h"
#include "GameController.h"

class ofApp : public ofBaseApp
{
private:
    GameController gameController;

public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
};