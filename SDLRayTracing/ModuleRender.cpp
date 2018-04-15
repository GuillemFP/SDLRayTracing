#include "ModuleRender.h"

#include "Application.h"
#include "ModuleWindow.h"
#include "SDL/include/SDL.h"

#include <iostream>
#include <fstream>

ModuleRender::ModuleRender() : Module(MODULERENDER_NAME)
{
}

ModuleRender::~ModuleRender()
{
}

bool ModuleRender::Init()
{
	LOG("Creating Renderer context");

	Uint32 flags = 0;
	_renderer = SDL_CreateRenderer(App->_window->GetWindow(), -1, flags);

	if (!_renderer)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	return true;
}

bool ModuleRender::Start()
{
	int nx = App->_window->GetWindowsWidth();
	int ny = App->_window->GetWindowsHeight();

	std::ofstream myFile;
	myFile.open("image.ppm");

	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
	SDL_RenderClear(_renderer);

	myFile << "P3\n" << nx << " " << ny << "\n255\n";
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			float r = float(i) / float(nx);
			float g = float(j) / float(ny);
			float b = 0.2f;
			int ir = int(255.99*r);
			int ig = int(255.99*g);
			int ib = int(255.99*b);
			myFile << ir << " " << ig << " " << ib << "\n";
			SDL_SetRenderDrawColor(_renderer, ir, ig, ib, 255);
			SDL_RenderDrawPoint(_renderer, i, j);
		}
	}

	SDL_RenderPresent(_renderer);

	myFile.close();

	return true;
}

bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy window
	if (_renderer)
	{
		SDL_DestroyRenderer(_renderer);
	}

	return true;
}

