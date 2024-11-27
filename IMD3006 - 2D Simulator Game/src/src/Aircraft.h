#include "gameObject.h"
#include "ofMain.h"
using namespace::std;

class Aircraft : public gameObject
{
private:
	float speed = 0.0f;
	float altitude = 0.0f;
	float fuelLevel = 0.0f;
	

public:
	
	
	Aircraft();
	Aircraft* next = NULL;
	void takeoff();
	void land();
	void updatePosition();
	bool checkCollision(const Aircraft& other);
};

