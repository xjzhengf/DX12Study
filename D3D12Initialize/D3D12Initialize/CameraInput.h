#pragma once
#include "stdafx.h"
#include "Camera.h"

class CameraMove : public Camera
{
public:
	//Ïà»úÒÆ¶¯
	void Strafe(float d);
	void Walk(float d);
	void UpDown(float d);
	void Pitch(float angle);
	void RotateY(float angle);
	void RotateLook(float angle);
private:

};
