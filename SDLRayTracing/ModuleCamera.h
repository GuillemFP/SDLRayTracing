#ifndef MODULECAMERA_H
#define MODULECAMERA_H

#define MODULECAMERA_NAME "ModuleCamera"

#include "Module.h"
#include "Vector3.h"
#include "Ray.h"

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

	Ray GenerateRay(float widthFactor, float heigthFactor, math::LCG& randomGenerator) const;

private:
	math::Frustum* _frustum;

	Vector3 _position;
	Vector3 _up;
	Vector3 _right;

	Vector3 _cornerBottomLeft;
	Vector3 _viewportWidthVector;
	Vector3 _viewportHeightVector;

	float _lensRadius = 0.0f;
	float _minTime = 0.0f;
	float _maxTime = 0.0f;
};

#endif // !CAMERA_H