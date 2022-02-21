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
class FColor {
public:
	uint8_t R;
	uint8_t G;
	uint8_t B;
	uint8_t A;
};