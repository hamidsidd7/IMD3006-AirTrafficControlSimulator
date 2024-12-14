#include "ofApp.h"

void ofApp::setup()
{
    gameController.setup();

}

void ofApp::update()
{
    gameController.update();
}

void ofApp::draw()
{
    gameController.draw();
}

void ofApp::keyPressed(int key)
{
    gameController.handleKeyPress(key);
}