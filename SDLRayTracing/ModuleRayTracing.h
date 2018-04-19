#ifndef MODULERAYTRACING_H
#define MODULERAYTRACING_H

#include "Module.h"

#define MODULERAYTRACING_NAME "ModuleRayTracing"

class ModuleRayTracing : public Module
{
public:
	ModuleRayTracing();
	~ModuleRayTracing();

	bool Init();
	bool Start();

private:
	int _pixelsWidth = 0;
	int _pixelsHeight = 0;
};

#endif // !MODULERAYTRACING_H