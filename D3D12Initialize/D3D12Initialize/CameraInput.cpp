#include "stdafx.h"
#include "CameraInput.h"

void CameraMove::Strafe(float d)
{
	glm::vec3 s = { d,d,d };
	glm::vec3 r = GetRight();
	glm::vec3 p = GetCameraPos3f();
	SetCameraPos(VectorMultiplyAdd(s, r, p));
}

void CameraMove::Walk(float d)
{
	glm::vec3 s = { d,d,d };
	glm::vec3 l = GetLook();
	glm::vec3 p = GetCameraPos3f();

	SetCameraPos(VectorMultiplyAdd(s, l, p));

}

void CameraMove::UpDown(float d)
{
	glm::vec3 s = { d,d,d };
	glm::vec3 u = GetUp();
	glm::vec3 p = GetCameraPos3f();
	SetCameraPos(VectorMultiplyAdd(s, u, p));

}

void CameraMove::Pitch(float angle)
{
	glm::mat4x4 R = glm::mat4x4(1.0f);
	R = glm::rotate(R, angle, GetRight());
	SetUp(glm::normalize(Transform(R, GetUp()))) ;
	SetLook(glm::normalize(Transform(R, GetLook())));
	SetRight(glm::normalize(Transform(R, GetRight())));

}

void CameraMove::RotateY(float angle)
{
	glm::mat4x4 M = glm::identity<glm::mat4x4>();

	M = glm::rotate(M, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	SetRight(glm::normalize(Transform(M, GetRight())));
	SetUp(glm::normalize(Transform(M, GetUp())));
	SetLook(glm::normalize(Transform(M, GetLook())));
}

void CameraMove::RotateLook(float angle)
{
	glm::mat4x4 R = glm::mat4x4(1.0f);
	R = glm::rotate(R, angle, GetLook());
	SetUp(glm::normalize(Transform(R, GetUp()))) ;
	SetRight(glm::normalize(Transform(R, GetRight()))) ;


}