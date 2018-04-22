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

	bool Init(Config* config = nullptr);
	bool CleanUp();

	const math::float3& GetOrigin() const { return _origin; }
	const math::float3& GetFront() const { return _front; }
	const math::float3& GetUp() const { return _up; }
	const math::float3& GetRight() const { return _right; }

	float GetViewportDistance() const;

	math::Ray GenerateRay(float widthFactor, float heigthFactor) const;

private:
	math::float3 _origin;
	math::float3 _front;
	math::float3 _up;
	math::float3 _right;

	math::float3 _cornerBottomLeft;
	math::float3 _viewportWidthVector;
	math::float3 _viewportHeightVector;
};

#endif // !CAMERA_H