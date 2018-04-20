#ifndef MODULECAMERA_H
#define MODULECAMERA_H

#define MODULECAMERA_NAME "ModuleCamera"

#include "Module.h"
#include "MathGeoLib\include\Math\float3.h";
#include "MathGeoLib\include\Geometry\Ray.h"

class ModuleCamera : public Module
{
public:
	ModuleCamera();
	~ModuleCamera() = default;

	bool Init();
	bool CleanUp();

	const float3& GetOrigin() const { return _origin; }
	const float3& GetFront() const { return _front; }
	const float3& GetUp() const { return _up; }
	const float3& GetRight() const { return _right; }

	float GetViewportDistance() const;

	Ray GenerateRay(float widthFactor, float heigthFactor) const;

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