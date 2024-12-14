#include "RunwayView.h"
void RunwayView::Draw(const Runway& Runway)
{
    ofPushMatrix();
    // ofTranslate(zoneX, zoneY);
    ofScale(0.2, 0.2);
    //runwayImg.resize(ofGetWindowWidth(), ofGetWindowHeight());
    Runway.runwayImg.draw(0, 0);

    ofPopMatrix();
}
