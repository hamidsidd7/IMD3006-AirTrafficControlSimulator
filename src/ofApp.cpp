#include "ofApp.h"
#include "ofxOpenCv.h"
#include "Aircraft.h"
//--------------------------------------------------------------
void ofApp::setup()
{
    windowWidth = ofGetWindowWidth();
    windowHeight = ofGetWindowHeight();
    ofSetFrameRate(60);
    
    gui.setup();
    runway.setup();
    radar.setup();

    boundaryBox.set(ofGetWindowWidth()/2.5, ofGetWindowHeight()/3, 220, 250); 
    boundaryBox.scaleFromCenter(2,2);
    


    //runwayPosX = runway.runwayImg.getWidth() / 2;
   // runwayPosY = runway.runwayImg.getHeight() / 2;
    for (int i = 0; i < 12; i++)
    {
        //radar.radarImg.load("radar.png");
        Aircraft plane;
        plane.setup();
        plane.position.set(ofRandom(boundaryBox.getLeft(), boundaryBox.getRight()), 
            ofRandom(boundaryBox.getTop(), boundaryBox.getBottom())  
        );

        if (runway.landingZone.inside(plane.position) && plane.state != TAKENOFF)
        {
            plane.state = TAKEOFF;
        }
        Aircrafts.push_back(plane);

    }


    for (int i = 0; i < ofRandom(3); i++)
    {


        Aircraft plane;
        plane.setup();


        int x = ofRandom(runway.landingZone.getX(), runway.landingZone.getX() + runway.landingZone.getWidth());
        int y = ofRandom(runway.landingZone.getY(), runway.landingZone.getY() + runway.landingZone.getHeight());
        plane.position.set(x, y);

        plane.state = FLYING;
        Aircrafts.push_back(plane);


    }
    ofToggleFullscreen();
   
}

//--------------------------------------------------------------
void ofApp::update()
{
    windowWidth = ofGetWindowWidth();
    windowHeight = ofGetWindowHeight();

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

            if ((currPlane->position.x == runway.landingZone.getLeft() || currPlane->position.x == runway.landingZone.getRight() ||
                currPlane->position.y == runway.landingZone.getTop() || currPlane->position.y == runway.landingZone.getBottom()) && currPlane->state != TAKEOFF)
            {
                currPlane->directionAngle += PI;
            }
        }
        else if (!runway.landingZone.inside(currPlane->position) && currPlane->state != TAKENOFF)
        {
            currPlane->state = FLYING;
            currPlane->landing = false;
        }


       
        if (!boundaryBox.inside(currPlane->position) || currPlane->landing == true) 
        {
            currPlane = Aircrafts.erase(currPlane);
        }
        else {
            ++currPlane;
        }
    }


    if (Aircrafts.size() < 12)
    {
        Aircraft newPlane;
        newPlane.setup();
        newPlane.position.set(ofRandom(boundaryBox.getLeft(), boundaryBox.getRight()),
            ofRandom(boundaryBox.getTop(), boundaryBox.getBottom())
        );
        if (runway.landingZone.inside(newPlane.position) && newPlane.state != TAKENOFF)
        {
            newPlane.state = TAKEOFF;
        }
        Aircrafts.push_back(newPlane);

        

        if (runway.getRunwaysFree() < 3 && runway.getRunwaysFree() > 0)
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
    /* Draw the boundary box (debug)
    ofSetColor(0, 255, 0, 100);
    ofDrawRectangle(boundaryBox);
    ofSetColor(255);*/

    ofPushMatrix();
    ofTranslate(ofGetWindowWidth() / 3, ofGetWindowHeight() / 2);
    runway.Draw();
    ofPopMatrix();

    /*landing zone (debug)
    ofSetColor(255, 0, 0, 100);
    ofDrawRectangle(runway.landingZone);
    ofSetColor(255);*/
   

    gui.begin();
    
        ImGui::SetNextWindowPos(ofVec2f(60, ofGetWindowHeight() - 500), ImGuiCond_Once);
        ImGui::SetNextWindowSize(ofVec2f(250, 200), ImGuiCond_Once);
        ImGui::Begin("Collision Emergency Handling");
        
        for (int i = 0; i < Aircrafts.size(); ++i)
        {
            for (int j = i + 1; j < Aircrafts.size(); ++j)
            {
                if (Aircrafts[i].diverted == false && Aircrafts[j].diverted == false)
                {
                    if (Aircrafts[i].checkCollision(Aircrafts[j]))
                    {
                        Aircrafts[i].state = COLLISION;
                        Aircrafts[j].state = COLLISION;

                        string planeInfo = Aircrafts[i].planeID + " & " + Aircrafts[j].planeID;
                        ImGui::Text("%s", planeInfo.c_str());

                        if (ImGui::Button(("Divert " + planeInfo).c_str()))
                        {
                            Aircrafts[i].directionAngle += PI / 4;
                            Aircrafts[j].directionAngle -= PI / 4;

                            Aircrafts[i].diverted = true;
                            Aircrafts[j].diverted = true;
                        
                            Aircrafts[i].state = FLYING;
                            Aircrafts[j].state = FLYING;
                            

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
                    plane.directionAngle += PI;
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
        ofPushMatrix();
        plane.Draw();
        ofPopMatrix();
    }

    gui.end();
}


void ofApp::addAircraft() 
{
    Aircraft newPlane;
    newPlane.setup();

    // Position the plane within the landing zone, ensuring it's ready for takeoff
    int x = ofRandom(runway.landingZone.getX(), runway.landingZone.getX() + runway.landingZone.getWidth());
    int y = ofRandom(runway.landingZone.getY(), runway.landingZone.getY() + runway.landingZone.getHeight());
    newPlane.position.set(x, y);
    newPlane.updatePosition();
    // Set the plane's state to TAKEOFF
    newPlane.state = TAKEOFF;
    

    // Add the plane to the list
    Aircrafts.push_back(newPlane);
}

void ofApp::windowResized(int w, int h)
{
    boundaryBox.set(ofGetWindowWidth() / 2.5, ofGetWindowHeight() / 3, 400, 400); // Adjust dimensions as needed
    boundaryBox.scaleFromCenter(2, 2);

    windowWidth = ofGetWindowWidth() - 200;
    windowHeight = ofGetWindowHeight();

    runway.setup();
   
}