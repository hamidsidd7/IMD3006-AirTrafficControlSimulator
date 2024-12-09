#include "Runway.h"

void Runway::setup()
{
	//next = NULL;
	status = "available";
	id = 0;
	runwayImg.load("runway");
}

void Runway::setStatus(const string newStatus)
{

}



string Runway::getStatus()
{
	return "NULL";
}
bool Runway::isAvailable()
{
	return true;
}