// GameController.cpp
#include "GameController.h"
void GameController::setup() 
{
    radar.setup();
    runway.setup();
    ui.setup();
    

    for (int i = 0; i < 5; i++)
    {
        Aircraft plane;
        plane.setup();
        Aircrafts.push_back(plane);
    }
    
}

void GameController::update() 
{
    if (ui.retry) 
    {
        resetGame(); 
        ui.retry = false;
    }

    if (!ui.instructions && !lost && !won)
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

          
            

            if (ui.planesLanded + ui.planesTakenOff >= 10)
            {
                won = true;
                ui.airTrafficSound.stop();
            }

            if (!radar.boundaryBox.inside(currPlane->position) || currPlane->landing == true)
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
            newPlane.position.set(ofRandom(radar.boundaryBox.getLeft(), radar.boundaryBox.getRight()),
                ofRandom(radar.boundaryBox.getTop(), radar.boundaryBox.getBottom()));
            if (runway.landingZone.inside(newPlane.position) && newPlane.state != TAKENOFF)
            {
                newPlane.state = TAKEOFF;
            }
            Aircrafts.push_back(newPlane);



            if (runway.getRunwaysFree() < 3 && runway.getRunwaysFree() > 0)
            {
               plane.addAircraft(Aircrafts);
            }
        }

    }

    for (auto& plane : Aircrafts)
    {
        if (plane.showCountdown)
        {
            plane.state == COLLISION;
            plane.divertCountdown -= ofGetLastFrameTime();
            if (plane.divertCountdown <= 0)
            {
                lost = true;
            }
            
        }
    }
   
}


void GameController::draw()
{
    ofBackground(0, 120, 100);
    radarV.Draw(radar);
    
    
    ofPushMatrix();
    ofTranslate(ofGetWindowWidth() / 3, ofGetWindowHeight() / 2);
    runway.Draw();
    ofPopMatrix();

     for (const auto& plane : Aircrafts)
     {
         aircraftView.Draw(plane);
     }

    ui.draw(Aircrafts, runway, ui.planesTakenOff, ui.planesLanded, lost, ui.instructions, won);
}

void GameController::handleKeyPress(int key)
{
    if (key == ' ')
    {
        ui.instructions = false;
        ui.airTrafficSound.play();
    }
}

void GameController::resetGame() 
{
        ui.planesTakenOff = 0;
        ui.planesLanded = 0;
        won = false;
        Aircrafts.clear();
        runway.setup();
        ui.retry = false;
        lost = false;
        ui.instructions = true;

        for (int i = 0; i < 15; i++)
        {
            Aircraft plane;
            plane.setup();
            plane.position.set(ofRandom(radar.boundaryBox.getLeft(), radar.boundaryBox.getRight()),
                ofRandom(radar.boundaryBox.getTop(), radar.boundaryBox.getBottom()));

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
    
}
