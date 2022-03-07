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

void FirstPersonCamera::OnMouseDown(WPARAM btnState, int x, int y, HWND mhMainWnd)
{
	mLastMousePos.x = x;
	mLastMousePos.y = y;
	SetCapture(mhMainWnd);
}

void FirstPersonCamera::OnMouseMove(WPARAM btnState, int x, int y)
{
	if ((btnState & MK_LBUTTON) != 0|| (btnState & MK_RBUTTON) != 0) {
		float dx = glm::radians(0.25f * static_cast<float>(x - mLastMousePos.x));
		float dy = glm::radians(0.25f * static_cast<float>(y - mLastMousePos.y));
		//mTheta += dx;
		//mPhi += dy;
		//mPhi = MathHelper::Clamp(mPhi, 0.1f, MathHelper::Pi - 0.1f);

		RotateY(dx);
		Pitch(dy);
	}
	mLastMousePos.x = x;
	mLastMousePos.y = y;
}

void FirstPersonCamera::OnMouseUp(WPARAM btnState, int x, int y)
{
	ReleaseCapture();
}

void FirstPersonCamera::CameraMove(std::string inputKey)
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
}
