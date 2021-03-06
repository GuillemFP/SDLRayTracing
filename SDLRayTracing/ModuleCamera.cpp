#include "ModuleCamera.h"

#include "Application.h"
#include "Config.h"
#include "Math.h"
#include "MathUtils.h"
#include "ModuleWindow.h"
#include "ParseUtils.h"

ModuleCamera::ModuleCamera() : Module(MODULECAMERA_NAME)
{
}

bool ModuleCamera::Init(Config* config)
{
	_frustum = new math::Frustum();
	_frustum->SetKind(math::FrustumProjectiveSpace::FrustumSpaceGL, math::FrustumHandedness::FrustumRightHanded);

	_lensRadius = config->GetFloat("Aperture", 0.0f) * 0.5f;
	_minTime = config->GetFloat("Min Time", 0.0f);
	_maxTime = config->GetFloat("Max Time", 0.0f);
	float vFov = config->GetFloat("Vertical FOV", 60.0f);
	float aspectRatio = config->GetFloat("Aspect Ratio", 1.5f);
	_frustum->SetVerticalFovAndAspectRatio(vFov * DEG_TO_RAD, aspectRatio);

	Vector3 position = ParseUtils::ParseVector(config->GetArray("Position"));
	Vector3 lookAt = ParseUtils::ParseVector(config->GetArray("LookAt"));
	Vector3 focusPoint = ParseUtils::ParseVector(config->GetArray("FocusPoint"));
	float distanceToFocus = (focusPoint - position).length();

	_frustum->SetViewPlaneDistances(distanceToFocus, distanceToFocus + 1.0f);
	_frustum->SetPos(position.toFloat3());
	_frustum->SetFrame(position.toFloat3(), math::float3::unitZ, math::float3::unitY);
	LookAt(lookAt.toFloat3());

	_position = _frustum->Pos();
	_up = _frustum->Up();
	_right = _frustum->WorldRight();
	
	math::float3 corners[8];
	_frustum->GetCornerPoints(corners);
	_cornerBottomLeft = corners[0];
	_viewportWidthVector = corners[1] - _cornerBottomLeft;
	_viewportHeightVector = corners[2] - _cornerBottomLeft;

	return true;
}

bool ModuleCamera::CleanUp()
{
	RELEASE(_frustum);

	return true;
}

void ModuleCamera::LookAt(const math::float3& lookAt)
{
	math::float3 direction = (lookAt - _frustum->Pos()).Normalized();
	math::float3x3 matrix = math::float3x3::LookAt(_frustum->Front(), direction, _frustum->Up(), math::float3::unitY);

	_frustum->SetFront(matrix.MulDir(_frustum->Front()).Normalized());
	_frustum->SetUp(matrix.MulDir(_frustum->Up()).Normalized());
}

Ray ModuleCamera::GenerateRay(float widthFactor, float heightFactor, math::LCG& randomGenerator) const
{
	Vector3 viewportPosition = _cornerBottomLeft + _viewportWidthVector * widthFactor + _viewportHeightVector * heightFactor;

	Vector3 randomInDisk = _lensRadius * MathUtils::RandomPointInDisk(randomGenerator);
	Vector3 rayOrigin = _position + _up * randomInDisk.x() + _right * randomInDisk.y();

	Vector3 unitVector = normalize(viewportPosition - rayOrigin);
	const float time = randomGenerator.FloatIncl(_minTime, _maxTime);
	return Ray(rayOrigin, unitVector, time);
}
