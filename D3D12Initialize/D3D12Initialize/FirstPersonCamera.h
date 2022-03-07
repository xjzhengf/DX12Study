#pragma once
#include "stdafx.h"
#include "Camera.h"

class FirstPersonCamera : public Camera
{
public:
	//Ïà»úÒÆ¶¯
	void Strafe(float d) ;
	void Walk(float d) ;
	void UpDown(float d) ;
	void Pitch(float angle) ;
	void RotateY(float angle) ;
	void RotateLook(float angle) ;

	 void OnMouseDown(WPARAM btnState, int x, int y, HWND mhMainWnd) ;
	 void OnMouseMove(WPARAM btnState, int x, int y) ;
	 void OnMouseUp(WPARAM btnState, int x, int y) ;

	 void CameraMove(std::string inputKey) override;
private:
	POINT mLastMousePos;
};
