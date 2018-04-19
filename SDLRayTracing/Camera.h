#ifndef CAMERA_H
#define CAMERA_H

#include "MathGeoLib\include\Math\float3.h";
#include "MathGeoLib\include\Geometry\Ray.h"

class Camera
{
public:
	Camera(const float3& origin, const float3& front, const float3& up, const float3& right, float viewportWidth, float viewportHeight, float viewportDistance);
	~Camera() = default;

	const float3& GetOrigin() const { return _origin; }
	const float3& GetFront() const { return _front; }
	const float3& GetUp() const { return _up; }
	const float3& GetRight() const { return _right; }

	float GetViewportDistance() const;

	Ray GenerateRay(float widthFactor, float heigthFactor) const;
	float3 VectorToViewport(float widthFactor, float heightFactor) const;

private:
	float3 _origin;
	float3 _front;
	float3 _up;
	float3 _right;

	float3 _cornerBottomLeft;
	float3 _viewportWidthVector;
	float3 _viewportHeightVector;
};

#endif // !CAMERA_H