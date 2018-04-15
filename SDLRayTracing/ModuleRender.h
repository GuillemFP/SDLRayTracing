#ifndef MODULERENDER_H
#define MODULERENDER_H

#include "Module.h"

#define MODULERENDER_NAME "ModuleRender"

class SDL_Renderer;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init();
	bool Start();
	bool CleanUp();

private:
	SDL_Renderer* _renderer = nullptr;
};

#endif // !MODULERENDER_H