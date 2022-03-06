#pragma once
#include "stdafx.h"
#include "Camera.h"

class CameraInput : public Camera
{
public:
	CameraInput();
	~CameraInput();


	//����ƶ�
	void Strafe(float d);
	void Walk(float d);
	void UpDown(float d);
	void Pitch(float angle);
	void RotateY(float angle);
	void RotateLook(float angle);
private:

};

CameraInput::CameraInput()
{
}

CameraInput::~CameraInput()
{
}