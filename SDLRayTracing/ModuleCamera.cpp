#include "ModuleCamera.h"

#include "Application.h"
#include "Math.h"
#include "ModuleWindow.h"

ModuleCamera::ModuleCamera() : Module(MODULECAMERA_NAME)
{
}

bool ModuleCamera::Init()
{
	int pixelsWidth = App->_window->GetWindowsWidth();
	int pixelsHeight = App->_window->GetWindowsHeight();

	_origin = math::float3::zero;
	_front = math::float3(0.0f, 0.0f, -1.0f);
	_up = math::float3(0.0f, 1.0f, 0.0f);
	_right = math::float3(1.0f, 0.0f, 0.0f);

	float viewportWidth = 4.0f;
	float viewportHeight = 3.0f;
	float viewportDistance = 1.0f;

	_viewportWidthVector = viewportWidth * _right;
	_viewportHeightVector = viewportHeight * _up;
	_cornerBottomLeft = _origin + viewportDistance * _front - 0.5f * _viewportWidthVector - 0.5f * _viewportHeightVector;

	return true;
}

bool ModuleCamera::CleanUp()
{
	return true;
}

float ModuleCamera::GetViewportDistance() const
{
	return (_cornerBottomLeft - _origin).Dot(_front);
}

math::Ray ModuleCamera::GenerateRay(float widthFactor, float heightFactor) const
{
	math::float3 viewportPosition = _cornerBottomLeft + _viewportWidthVector * widthFactor + _viewportHeightVector * heightFactor;
	math::float3 unitVector = (viewportPosition - _origin).Normalized();
	return math::Ray(_origin, unitVector);
}
