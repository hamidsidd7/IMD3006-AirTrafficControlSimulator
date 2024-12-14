// UI.cpp
#include "UI.h"
#include "ofApp.h"

void UI::setup() {
    gui.setup();
    startScreen.load("instructions.jpg");
    lossScreen.load("lost.png");
    winScreen.load("win.png");

    airTrafficSound.load("air-traffic-control.mp3");
    airTrafficSound.setVolume(0.15f);
    airTrafficSound.setLoop(true);

    emergencySound.load("emergency.mp3");
    emergencySound.setVolume(0.15f);

    planeSound.load("Plane sound.mp3");
    planeSound.setVolume(0.04f);
    planeSound.setLoop(true);
    planeSound.play();
    instructions = true;
    planesTakenOff = 0;
    planesLanded = 0;
    retry = false;
}

void UI::draw(vector<Aircraft>& Aircrafts, Runway& runway, int planesTakenOff, int planesLanded, bool& lost, bool& instructions, bool& won) {
    gui.begin();

    handleInstructionsScreen(instructions, startScreen);
    handleLossScreen(lost, won, lossScreen, winScreen);

    if (!instructions && !lost && !won) {
        handleGameUI(Aircrafts, runway, planesTakenOff, planesLanded, lost);
        drawPlaneManagementUI(Aircrafts, runway);
    }

    gui.end();
}

void UI::handleInstructionsScreen(bool& instructions, ofImage& startScreen) {
    if (instructions) {
        startScreen.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    }
}

void UI::handleLossScreen(bool& lost, bool& won, ofImage& lossScreen, ofImage& winScreen) {
    if (lost)
    {
        lossScreen.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
        ImGui::SetNextWindowPos(ofVec2f(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2), ImGuiCond_Once);
        ImGui::Begin("You lost");
        if (ImGui::Button("Try Again")) {
            // Trigger GameController resetGame
            retry = true;
            //controller.resetGame(); 
            airTrafficSound.stop();
        }
        ImGui::End();
    }
    else if (won) 
    {
        winScreen.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
        ImGui::SetNextWindowPos(ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2), ImGuiCond_Once);
        ImGui::Begin("You Win");
        if (ImGui::Button("Play Again")) {
            // Trigger GameController resetGame
            // controller.resetGame(); 
            airTrafficSound.stop();
            retry = true;
        }
        ImGui::End();
    }
}

void UI::handleGameUI(vector<Aircraft>& Aircrafts, Runway& runway, int planesTakenOff, int planesLanded, bool& lost) {
    ImGui::SetNextWindowPos(ofVec2f(60, ofGetWindowHeight() - 500), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ofVec2f(250, 200), ImGuiCond_Once);
    ImGui::Begin("Collision Emergency Handling");

    // Draw in-game UI elements like emergency handling
    for (int i = 0; i < Aircrafts.size(); ++i) {
        for (int j = i + 1; j < Aircrafts.size(); ++j) {
            if (Aircrafts[i].diverted == false && Aircrafts[j].diverted == false) {
                if (Aircrafts[i].checkCollision(Aircrafts[j])) {
                    Aircrafts[i].state = COLLISION;
                    Aircrafts[j].state = COLLISION;
                    if (!Aircrafts[i].showCountdown) {
                        Aircrafts[i].divertCountdown = 5.0;
                        Aircrafts[i].showCountdown = true;
                    }
                    if (!Aircrafts[j].showCountdown) {
                        Aircrafts[j].divertCountdown = 5.0;
                        Aircrafts[j].showCountdown = true;
                        emergencySound.play();
                    }

                    if (ImGui::Button(("Divert " + Aircrafts[i].planeID + " & " + Aircrafts[j].planeID).c_str())) {
                        Aircrafts[i].directionAngle += PI / 4;
                        Aircrafts[j].directionAngle -= PI / 4;
                        Aircrafts[i].diverted = true;
                        Aircrafts[j].diverted = true;
                        Aircrafts[i].state = FLYING;
                        Aircrafts[j].state = FLYING;
                        Aircrafts[i].showCountdown = false;
                        Aircrafts[j].showCountdown = false;
                    }
                }
            }
        }
    }
    ImGui::End();

    ImGui::SetNextWindowPos(ofVec2f(ofGetWindowWidth() / 2, 20), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ofVec2f(200, 100), ImGuiCond_Once);
    ImGui::Begin("Planes Status");
    ImGui::Text("Planes Landed: %d", planesLanded);
    ImGui::Text("Planes Taken Off: %d", planesTakenOff);
    ImGui::End();
}

void UI::drawPlaneManagementUI(vector<Aircraft>& Aircrafts, Runway& runway)
{
    ImGui::SetNextWindowSize(ofVec2f(200, 500), ImGuiCond_Once);
    ImGui::Begin("Plane Management");
    ImGui::Text("Free Runways: %d", runway.getRunwaysFree());

    for (auto& plane : Aircrafts) {
        if (runway.landingZone.inside(plane.position) && plane.state == LANDING)
        {
            if (!plane.deniedLanding) 
            {
                ImGui::Text(plane.planeID.c_str());
                ImGui::Text("Altitude: %.1f feet", plane.altitude);
                ImGui::Text("Plane is requesting to land.");
                if (runway.getRunwaysFree() > 0) 
                {
                    if (ImGui::Button("Approve Landing"))
                    {
                        plane.land();
                        planesLanded++;
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
                planesTakenOff++;
                runway.runwaysFree++;
            }
            if (ImGui::Button("Deny Takeoff"))
            {
                plane.directionAngle += PI;
                plane.speed = 0.01;
                plane.deniedTakeOff = true;
            }
        }
    }
    ImGui::End();
}
