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
        //plane.setPos(ofRandom(100, 900), ofRandom(600, 1000));
        if (runway.landingZone.inside(plane.position)) {
            plane.state = TAKEOFF;
        }
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

        if (runway.landingZone.inside(currPlane->position)) {
            if (currPlane->state != TAKEOFF) {
                currPlane->state = LANDING;
            }
        }

        else if (!runway.landingZone.inside(currPlane->position)) {
            currPlane->state = FLYING;
        }

        // Check if the plane is out of bounds
        if (currPlane->position.y < ofGetWindowHeight() - 668 || currPlane->position.y > ofGetWindowHeight() - 150 ||
            currPlane->position.x < (ofGetWindowWidth() / 2) - 200 || currPlane->position.x >(ofGetWindowWidth() / 2) + 170)
        {
            
            currPlane = Aircrafts.erase(currPlane); 
        }
        else
        {
            ++currPlane; 
        }
    }

    if (Aircrafts.size() < 10) {
        Aircraft newPlane;
        newPlane.setup();

       


        Aircrafts.push_back(newPlane);
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

   
    ImGui::SetNextWindowSize(ofVec2f(200, 500), ImGuiCond_Once);
    ImGui::Begin("Plane Management");

    

    for (auto& plane : Aircrafts) {
        if (runway.landingZone.inside(plane.position) && plane.state == LANDING && !plane.landing) 
        {
           if (!plane.deniedLanding)
              { 
            ImGui::Text(plane.planeID.c_str());
               
                ImGui::Text("Plane is requesting to land.");

              
                  if (ImGui::Button("Approve Landing"))
                  {
                      plane.land();
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
                }

            
                if (ImGui::Button("Deny Takeoff"))
                {
                    plane.directionAngle += PI; // Reverse direction
                    plane.speed = 0.01;
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

//--------------------------------------------------------------
void ofApp::addAircraft()
{
    //use linked lists to add new aircrafts
}

//--------------------------------------------------------------
void ofApp::removeAircraft()
{
    //use linked lists to remove aircrafts

}

//--------------------------------------------------------------
void ofApp::handleCollisions() 
{
    //logic to handle collisions between planes
}

//--------------------------------------------------------------
void ofApp::manageRunways() 
{
   //logic to handle runways
}

