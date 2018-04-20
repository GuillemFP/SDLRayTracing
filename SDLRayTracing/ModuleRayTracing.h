#ifndef MODULERAYTRACING_H
#define MODULERAYTRACING_H

#define MODULERAYTRACING_NAME "ModuleRayTracing"

#include "Module.h"
#include "Color.h"
#include <iostream>
#include <fstream>

namespace math
{
	float3;
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

private:
	void InitFile();
	void WriteColor(const Color& color);

private:
	int _pixelsWidth = 0;
	int _pixelsHeight = 0;

	std::ofstream _ppmImage;
};

#endif // !MODULERAYTRACING_H