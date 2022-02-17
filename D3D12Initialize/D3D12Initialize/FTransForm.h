#pragma once
class FVector {
public:
	float x;
	float y;
	float z;
};
class FVector4 {
public:
	float x;
	float y;
	float z;
	float w;
};
class FTransform {
public:
	FVector4 Rotation;
	FVector Location;
	FVector Scale3D;
};