#include "stdafx.h"
#include "FirstPersonCamera.h"

void FirstPersonCamera::Strafe(float d)
{
	glm::vec3 s = { d,d,d };
	glm::vec3 r = GetRight();
	glm::vec3 p = GetCameraPos3f();
	SetCameraPos(VectorMultiplyAdd(s, r, p));
	SetViewDirty(true);
}

void FirstPersonCamera::Walk(float d)
{
	glm::vec3 s = { d,d,d };
	glm::vec3 l = GetLook();
	glm::vec3 p = GetCameraPos3f();

	SetCameraPos(VectorMultiplyAdd(s, l, p));
	SetViewDirty(true);
}

void FirstPersonCamera::UpDown(float d)
{
	glm::vec3 s = { d,d,d };
	glm::vec3 u = GetUp();
	glm::vec3 p = GetCameraPos3f();
	SetCameraPos(VectorMultiplyAdd(s, u, p));
	SetViewDirty(true);
}

void FirstPersonCamera::Pitch(float angle)
{
	glm::mat4x4 R = glm::mat4x4(1.0f);
	R = glm::rotate(R, angle, GetRight());
	SetUp(glm::normalize(Transform(R, GetUp()))) ;
	SetLook(glm::normalize(Transform(R, GetLook())));
	SetRight(glm::normalize(Transform(R, GetRight())));
	SetViewDirty(true);
}

void FirstPersonCamera::RotateY(float angle)
{
	glm::mat4x4 M = glm::identity<glm::mat4x4>();

	M = glm::rotate(M, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	SetRight(glm::normalize(Transform(M, GetRight())));
	SetUp(glm::normalize(Transform(M, GetUp())));
	SetLook(glm::normalize(Transform(M, GetLook())));
	SetViewDirty(true);
}

void FirstPersonCamera::RotateLook(float angle)
{
	glm::mat4x4 R = glm::mat4x4(1.0f);
	R = glm::rotate(R, angle, GetLook());
	SetUp(glm::normalize(Transform(R, GetUp()))) ;
	SetRight(glm::normalize(Transform(R, GetRight()))) ;
	SetViewDirty(true);
}

void FirstPersonCamera::OnMouseDown(int x, int y)
{
	mLastMousePos.x = x;
	mLastMousePos.y = y;
	SetCapture(mhMainWnd);
}

void FirstPersonCamera::OnMouseMove(int x, int y)
{

	float dx = glm::radians(0.25f * static_cast<float>(x - mLastMousePos.x));
	float dy = glm::radians(0.25f * static_cast<float>(y - mLastMousePos.y));

	RotateY(dx);
	Pitch(dy);
	
	mLastMousePos.x = x;
	mLastMousePos.y = y;
}

void FirstPersonCamera::OnMouseUp( int x, int y)
{
	ReleaseCapture();
}

void FirstPersonCamera::CameraMove(const std::string& inputKey, LPARAM lParam)
{
	if (inputKey == "KEYDOWN_A") {
		Strafe(-1.0f * (GetCameraSpeed()));
		return ;
	}
	if (inputKey == "KEYDOWN_S") {
		Walk(-1.0f * (GetCameraSpeed()));
		return;
	}
	if (inputKey == "KEYDOWN_D") {
		Strafe(1.0f * (GetCameraSpeed()));
		return;
	}
	if (inputKey == "KEYDOWN_W") {
		Walk(1.0f * (GetCameraSpeed()));
		return;
	}
	if (inputKey == "KEYDOWN_E") {
		UpDown(1.0f * (GetCameraSpeed()));
		return;
	}
	if (inputKey == "KEYDOWN_Q") {
		UpDown(-1.0f * (GetCameraSpeed()));
		return;
	}
	if (inputKey == "RBUTTONDOWN") {
		OnMouseDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return;
	}
	if (inputKey == "RBUTTONUP") {
		OnMouseUp(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return;
	}
	if (inputKey == "LBUTMOUSEMOVE"|| inputKey == "RBUTMOUSEMOVE") {
		OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return;
	}
}
