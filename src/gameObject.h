#pragma once
#include "ofxOpenCv.h"
class gameObject
{
protected:	//make img protected so child classes can use it
	ofImage img;
public:
	int x;
	int y;

	int height;
	int width;


	gameObject();
	~gameObject();

	//virtual functions are expected to be modified by child class
	//any call will result in child class to be executed
	virtual void Draw();
	virtual ofImage* GetImage();
};