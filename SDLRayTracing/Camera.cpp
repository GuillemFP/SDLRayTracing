#include "Camera.h"

#include "Math.h"

Camera::Camera(const float3& origin, const float3& front, const float3& up, const float3& right, float viewportWidth, float viewportHeight, float viewportDistance) 
	: _origin(origin), _front(front), _up(up), _right(right)
{
	_viewportWidthVector = viewportWidth * _right;
	_viewportHeightVector = viewportHeight * _up;
	_cornerBottomLeft = origin + viewportDistance * front - 0.5f * _viewportWidthVector - 0.5f * _viewportHeightVector;
}

float Camera::GetViewportDistance() const
{
	return (_cornerBottomLeft - _origin).Dot(_front);
}

Ray Camera::GenerateRay(float widthFactor, float heightFactor) const
{
	float3 unitVector = VectorToViewport(widthFactor, heightFactor).Normalized();
	return Ray(_origin, unitVector);
}

float3 Camera::VectorToViewport(float widthFactor, float heightFactor) const
{
	float3 viewportPosition = _cornerBottomLeft + _viewportWidthVector * widthFactor + _viewportHeightVector * heightFactor;
	return viewportPosition - _origin;
}
