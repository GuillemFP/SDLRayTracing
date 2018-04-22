#ifndef MODULERAYTRACING_H
#define MODULERAYTRACING_H

#define MODULERAYTRACING_NAME "ModuleRayTracing"

#include "Module.h"
#include "Color.h"
#include "MathGeoLib\include\Math\float2.h"
#include "MathGeoLib\include\Math\float3.h"
#include <iostream>
#include <fstream>

namespace math
{
	class Ray;
	class LCG;
}

class Camera;

class ModuleRayTracing : public Module
{
public:
	ModuleRayTracing();
	~ModuleRayTracing();

	bool Init();
	bool Start();
	bool CleanUp();

	update_status Update();

private:
	Color CalculatePixelColor(int xPixel, int yPixel) const;
	
	math::float3 CalculateRayColor(const math::Ray& ray) const;
	math::float3 CalculateBackgroundColor(const math::Ray& ray) const;

	void InitFile();
	void WriteColor(const Color& color);

private:
	bool _screenFinished = false;

	int _pixelsWidth = 0;
	int _pixelsHeight = 0;
	int _samplesPerPixel = 100;

	int _currentX = 0;
	int _currentY = 0;
	int _pixelsPerUpdate = 50;

	float _minDistance = 0.01f;
	float _maxDistance = 1000.0f;

	math::LCG* _randomGenerator;

	std::ofstream _ppmImage;
};

#endif // !MODULERAYTRACING_H