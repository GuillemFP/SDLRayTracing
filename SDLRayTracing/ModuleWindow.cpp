#include "ModuleWindow.h"

#include "SDL/include/SDL.h"

ModuleWindow::ModuleWindow() : Module(MODULEWINDOW_NAME)
{
}

ModuleWindow::~ModuleWindow()
{
}

bool ModuleWindow::Init()
{
	_windowsWidth = WINDOWS_WIDTH;
	_windowsHeight = WINDOWS_HEIGHT;

	LOG("Init SDL window & surface");

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	Uint32 flags = SDL_WINDOW_SHOWN;

	_window = SDL_CreateWindow("Ray Tracing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _windowsWidth, _windowsHeight, flags);

	if (!_window)
	{
		LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	_screenSurface = SDL_GetWindowSurface(_window);

	return true;
}

bool ModuleWindow::CleanUp()
{
	//Destroy window
	if (_window)
	{
		SDL_DestroyWindow(_window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}
