#include "gameObject.h"

gameObject::gameObject()
{
	x = y = 0;
	height = 152;
	width = 90;
}


gameObject::~gameObject()
{
}

void gameObject::Draw()
{
	img.draw(x, y);
}

ofImage* gameObject::GetImage()
{
	return &img;
}