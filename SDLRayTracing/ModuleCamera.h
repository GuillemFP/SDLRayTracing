#ifndef MODULECAMERA_H
#define MODULECAMERA_H

#define MODULECAMERA_NAME "ModuleCamera"

#include "Module.h"
#include "MathGeoLib\include\Math\float3.h";
#include "MathGeoLib\include\Geometry\Ray.h"

namespace math
{
	class Frustum;
	class LCG;
}

class ModuleCamera : public Module
{
public:
	ModuleCamera();
	~ModuleCamera() = default;

	bool Init(Config* config = nullptr);
	bool CleanUp();

	void LookAt(const math::float3& lookAt);

	math::Ray GenerateRay(float widthFactor, float heigthFactor, math::LCG& randomGenerator) const;

private:
	math::Frustum* _frustum;

	math::float3 _position;
	math::float3 _up;
	math::float3 _right;

	math::float3 _cornerBottomLeft;
	math::float3 _viewportWidthVector;
	math::float3 _viewportHeightVector;

	float _lensRadius = 0.0f;
};

#endif // !CAMERA_H