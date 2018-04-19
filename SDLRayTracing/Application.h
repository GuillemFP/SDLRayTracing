#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>
#include "Globals.h"
#include "Module.h"

class ModuleInput;
class ModuleWindow;
class ModuleRender;

class ModuleRayTracing;

class Application
{
public:
	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleInput* _input;
	ModuleWindow* _window;
	ModuleRender* _renderer;
	
	ModuleRayTracing* _rayTracing;

private:
	std::vector<Module*> _modules;
};

extern Application* App;

#endif // !APPLICATION_H