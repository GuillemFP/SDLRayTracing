#ifndef MODULERENDER_H
#define MODULERENDER_H

#include "Module.h"

#define MODULERENDER_NAME "ModuleRender"

class SDL_Renderer;
struct Color;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init();
	bool Start();
	bool CleanUp();

	void DrawPixel(const Color& color, int x, int y);

private:
	SDL_Renderer* _renderer = nullptr;
};

#endif // !MODULERENDER_H