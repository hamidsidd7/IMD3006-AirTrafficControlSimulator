#include "ofApp.h"
#include "ofxOpenCv.h"
#include "Aircraft.h"
//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);
    //ofToggleFullscreen();
    gui.setup();
    runway.setup();
    radar.setup();


    runwayPosX = runway.runwayImg.getWidth() / 2;
    runwayPosY = runway.runwayImg.getHeight() / 2;
    for (int i = 0; i < 10; i++)
    {
        //radar.radarImg.load("radar.png");
        Aircraft plane;
        plane.setup();
        plane.position.set(ofRandom(100, 900), ofRandom(1000, 1200));
        if (runway.landingZone.inside(plane.position) && plane.state != TAKENOFF)
        {
            plane.state = TAKEOFF;
        }
        Aircrafts.push_back(plane);

    }


    if (runway.getRunwaysFree() < 6)
    {


        Aircraft plane;
        plane.setup();


        int x = ofRandom(runway.landingZone.getX(), runway.landingZone.getX() + runway.landingZone.getWidth());
        int y = ofRandom(runway.landingZone.getY(), runway.landingZone.getY() + runway.landingZone.getHeight());
        plane.position.set(x, y);

        plane.state = FLYING;
        Aircrafts.push_back(plane);


    }
}

//--------------------------------------------------------------
void ofApp::update()
{
    auto currPlane = Aircrafts.begin();
    while (currPlane != Aircrafts.end())
    {
        currPlane->updatePosition();

        if (runway.landingZone.inside(currPlane->position))
        {
            if (currPlane->state != TAKEOFF && currPlane->state != TAKENOFF)
            {
                currPlane->state = LANDING;
            }
        }
        else if (!runway.landingZone.inside(currPlane->position))
        {
            currPlane->state = FLYING;
        }


        if ((currPlane->position.y < ofGetWindowHeight() - 668 || currPlane->position.y > ofGetWindowHeight() - 150 ||
            currPlane->position.x < (ofGetWindowWidth() / 2) - 200 || currPlane->position.x >(ofGetWindowWidth() / 2) + 170) &&
            currPlane->state == FLYING || currPlane->landing)
        {
            currPlane = Aircrafts.erase(currPlane);
        }
        else
        {
            ++currPlane;
        }
    }


    if (Aircrafts.size() < 10)
    {
        Aircraft newPlane;
        newPlane.setup();
        Aircrafts.push_back(newPlane);

        if (runway.getRunwaysFree() < 5 && runway.getRunwaysFree() > 0)
        {
            addAircraft();

        }
    }




}


//--------------------------------------------------------------
void ofApp::draw() {


    ofBackground(157);
    ofDrawBitmapString("Welcome To our Game", 10, ofGetHeight() / 2);
    radar.Draw();
    ofPushMatrix();
    runway.Draw();
    ofPopMatrix();

    //landing zone (debug)
    ofSetColor(255, 0, 0, 100);
    ofDrawRectangle(runway.landingZone);
    ofSetColor(255);

    gui.begin();
    ImGui::SetNextWindowPos(ofVec2f(ofGetWindowWidth() - 200, ofGetWindowHeight() - 500), ImGuiCond_Once);
    ImGui::Begin(" Collision Emergency Handling");

    for (int i = 0; i < Aircrafts.size(); ++i)
    {
        for (int j = i + 1; j < Aircrafts.size(); ++j)
        {
            if (Aircrafts[i].diverted == false && Aircrafts[j].diverted == false)
            {
                if (Aircrafts[i].checkCollision(Aircrafts[j]))
                {
                    string planeInfo = Aircrafts[i].planeID + " & " + Aircrafts[j].planeID;
                    ImGui::Text("%s", planeInfo.c_str());

                    if (ImGui::Button(("Divert " + planeInfo).c_str()))
                    {
                        Aircrafts[i].directionAngle += PI / 4;
                        Aircrafts[j].directionAngle -= PI / 4;

                        Aircrafts[i].diverted = true;
                        Aircrafts[j].diverted = true;
                    }
                }

            }
        }
    }

    ImGui::End();

    ImGui::SetNextWindowSize(ofVec2f(200, 500), ImGuiCond_Once);
    ImGui::Begin("Plane Management");
    ImGui::Text("Free Runways: %d", runway.getRunwaysFree());



    for (auto& plane : Aircrafts) {

        if (runway.landingZone.inside(plane.position) && plane.state == LANDING && !plane.landing)
        {
            if (!plane.deniedLanding)
            {
                ImGui::Text(plane.planeID.c_str());

                ImGui::Text("Altitude: %.1f feet", plane.altitude);

                ImGui::Text("Plane is requesting to land.");

                if (runway.getRunwaysFree())
                {
                    if (ImGui::Button("Approve Landing"))
                    {
                        plane.land();
                        runway.runwaysFree--;
                    }

                }



                if (ImGui::Button("Deny Landing"))
                {
                    plane.directionAngle += PI;
                    plane.state = FLYING;
                    plane.deniedLanding = true;

                }

            }
        }

        else if (runway.landingZone.inside(plane.position) && plane.state == TAKEOFF && !plane.landing)
        {

            ImGui::Text(plane.planeID.c_str());

            ImGui::Text("Plane is requesting takeoff.");


            if (ImGui::Button("Approve Takeoff"))
            {
                plane.takeoff();
                if (runway.runwaysFree < 6)
                {
                    runway.runwaysFree++;
                }
                ;
            }


            if (ImGui::Button("Deny Takeoff"))
            {
                if (runway.landingZone.width)
                    plane.directionAngle += PI; // Reverse direction
                plane.speed = 0.01;
                plane.deniedTakeOff = true;
            }
        }


    }

    ImGui::End();

    for (auto& plane : Aircrafts) {
        if (plane.state == LANDING && !plane.landing) {
            if (plane.deniedLanding == false)
            {
                ofSetColor(255, 255, 0);
                ofDrawBitmapString(plane.planeID + " is requesting to land", plane.position.x, plane.position.y - 20);
                ofSetColor(255);
            }
        }
        else if (plane.state == TAKEOFF) {
            ofSetColor(255, 255, 0);
            ofDrawBitmapString(plane.planeID + " is requesting to take off", plane.position.x, plane.position.y - 20);
            ofSetColor(255);
        }

        // Draw the plane if it's not landed
        if (!plane.landing)
        {
            plane.Draw();
        }
    }

    gui.end();
}







//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}

void ofApp::addAircraft() {
    Aircraft newPlane;
    newPlane.setup();

    // Position the plane within the landing zone, ensuring it's ready for takeoff
    int x = ofRandom(runway.landingZone.getX(), runway.landingZone.getX() + runway.landingZone.getWidth());
    int y = ofRandom(runway.landingZone.getY(), runway.landingZone.getY() + runway.landingZone.getHeight());
    newPlane.position.set(x, y);
    newPlane.updatePosition();
    // Set the plane's state to TAKEOFF
    newPlane.state = TAKEOFF;
    if (!runway.landingZone.inside(newPlane.position))
    {
        newPlane.state = FLYING;
    }

    // Add the plane to the list
    Aircrafts.push_back(newPlane);

    auto currPlane = Aircrafts.begin();
    while (currPlane != Aircrafts.end())
    {

        if ((currPlane->position.y < ofGetWindowHeight() - 668 || currPlane->position.y > ofGetWindowHeight() - 150 ||
            currPlane->position.x < (ofGetWindowWidth() / 2) - 200 || currPlane->position.x >(ofGetWindowWidth() / 2) + 170) &&
            currPlane->state == FLYING)
        {
            currPlane = Aircrafts.erase(currPlane);
        }
        else
        {
            ++currPlane;
        }

    }
}