#include "ModuleRayTracing.h"

#include "Application.h"
#include "Color.h"
#include "Math.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"

ModuleRayTracing::ModuleRayTracing() : Module(MODULERAYTRACING_NAME)
{
}

ModuleRayTracing::~ModuleRayTracing()
{
}

bool ModuleRayTracing::Init()
{
	_pixelsWidth = App->_window->GetWindowsWidth();
	_pixelsHeight = App->_window->GetWindowsHeight();

	for (int j = _pixelsHeight - 1; j >= 0; j--)
	{
		for (int i = 0; i < _pixelsWidth; i++)
		{
			Color color(float(i) / float(_pixelsWidth), float(j) / float(_pixelsHeight), 0.2f);
			App->_renderer->DrawPixel(color, i, j);
		}
	}

	return true;
}

bool ModuleRayTracing::Start()
{
	return true;
}