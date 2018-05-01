#include "ModuleCamera.h"

#include "Application.h"
#include "Config.h"
#include "Math.h"
#include "ModuleWindow.h"
#include "ParseUtils.h"

ModuleCamera::ModuleCamera() : Module(MODULECAMERA_NAME)
{
}

bool ModuleCamera::Init(Config* config)
{
	int pixelsWidth = App->_window->GetWindowsWidth();
	int pixelsHeight = App->_window->GetWindowsHeight();

	_origin = ParseUtils::ParseVector(config->GetArray("Origin"));
	_front = ParseUtils::ParseVector(config->GetArray("Front"));
	_up = ParseUtils::ParseVector(config->GetArray("Up"));
	_right = ParseUtils::ParseVector(config->GetArray("Right"));

	Config viewport = config->GetSection("Viewport");

	float viewportWidth = viewport.GetFloat("Width");
	float viewportHeight = viewport.GetFloat("Height");
	float viewportDistance = viewport.GetFloat("Distance");

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
