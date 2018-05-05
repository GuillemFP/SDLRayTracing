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
	float vFov = config->GetFloat("Vertical FOV", 60.0f);
	float aspectRatio = config->GetFloat("Aspect Ratio", 1.5f);
	_frustum->SetVerticalFovAndAspectRatio(vFov * DEG_TO_RAD, aspectRatio);

	math::float3 position = ParseUtils::ParseVector(config->GetArray("Position"));
	math::float3 lookAt = ParseUtils::ParseVector(config->GetArray("LookAt"));
	float distanceToFocus = (lookAt - position).Length();

	_frustum->SetViewPlaneDistances(distanceToFocus, distanceToFocus + 1.0f);
	_frustum->SetPos(position);
	_frustum->SetFrame(position, math::float3::unitZ, math::float3::unitY);
	LookAt(lookAt);

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

math::Ray ModuleCamera::GenerateRay(float widthFactor, float heightFactor, math::LCG& randomGenerator) const
{
	math::float3 viewportPosition = _cornerBottomLeft + _viewportWidthVector * widthFactor + _viewportHeightVector * heightFactor;

	math::float3 randomInDisk = _lensRadius * MathUtils::RandomPointInDisk(randomGenerator);
	math::float3 rayOrigin = _position + _up * randomInDisk.x + _right * randomInDisk.y;

	math::float3 unitVector = (viewportPosition - rayOrigin).Normalized();
	return math::Ray(rayOrigin, unitVector);
}
