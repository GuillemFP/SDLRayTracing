#ifndef MODULERAYTRACING_H
#define MODULERAYTRACING_H

#define MODULERAYTRACING_NAME "ModuleRayTracing"

#include "Module.h"
#include "Color.h"
#include "Vector3.h"
#include "SDL\include\SDL_stdinc.h"
#include <iostream>
#include <fstream>

namespace math
{
	class LCG;
}

class Ray;
class Camera;
class Timer;

class ModuleRayTracing : public Module
{
public:
	ModuleRayTracing();
	~ModuleRayTracing();

	bool Init(Config* config = nullptr);
	bool Start();
	bool CleanUp();

	update_status Update();

private:
	Color CalculatePixelColor(int xPixel, int yPixel) const;
	
	Vector3 CalculateRayColor(const Ray& ray, int depth) const;
	Vector3 CalculateBackgroundColor(const Ray& ray) const;

	void InitFile();
	void WriteColor(const Color& color);

	int GetInitialPixelY() const;
	int GetInitialPixelX() const;

private:
	bool _screenFinished = false;

	int _pixelsWidth = 0;
	int _pixelsHeight = 0;
	int _samplesPerPixel = 1;

	int _currentX = 0;
	int _currentY = 0;
	int _pixelsPerUpdate = 1;

	int _currentAccumulated = 0;
	Uint32 _accumulatedRPS = 0;
	Uint32 _accumulatedMs = 0;
	Uint32 _accumulatedRays = 0;

	int _maxScatters = 10;
	float _minDistance = 0.0f;
	float _maxDistance = 1.0f;

	math::LCG* _randomGenerator = nullptr;

	std::ofstream _ppmImage;

	Timer* _rayTracingTime = nullptr;
	Timer* _frequencyTimer = nullptr;

	Color* _colorRow = nullptr;
};

#endif // !MODULERAYTRACING_H