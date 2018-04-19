#include "ModuleRayTracing.h"

#include "Application.h"
#include "Camera.h"
#include "Color.h"
#include "Math.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"

namespace
{
	Color calculateColor(const Ray& ray)
	{
		float3 direction = ray.dir;
		float t = 0.5f * (direction.y + 1.0f);
		return (1.0f - t) * float3::one + t * float3(0.5f, 0.7f, 1.0f);
	}
}

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

	//InitFile();

	float3 origin = float3::zero;
	float3 front = float3(0.0f, 0.0f, -1.0f);
	float3 up = float3(0.0f, 1.0f, 0.0f);
	float3 right = float3(1.0f, 0.0f, 0.0f);

	float viewportWidth = 4.0f;
	float viewportHeight = 2.0f;
	float viewportDistance = 1.0f;

	_camera = new Camera(origin, front, up, right, viewportWidth, viewportHeight, viewportDistance);

	for (int j = _pixelsHeight - 1; j >= 0; j--)
	{
		for (int i = 0; i < _pixelsWidth; i++)
		{
			float u = float(i) / float(_pixelsWidth);
			float v = float(j) / float(_pixelsHeight);
			Ray ray = _camera->GenerateRay(u, v);
			//Color color(float(i) / float(_pixelsWidth), float(j) / float(_pixelsHeight), 0.2f);
			Color color = calculateColor(ray);
			App->_renderer->DrawPixel(color, i, j);
			//WriteColor(color);
		}
	}

	return true;
}

bool ModuleRayTracing::Start()
{
	return true;
}

bool ModuleRayTracing::CleanUp()
{
	_ppmImage.close();

	RELEASE(_camera);

	return true;
}

void ModuleRayTracing::InitFile()
{
	_ppmImage.open("image.ppm");
	_ppmImage << "P3\n" << _pixelsWidth << " " << _pixelsHeight << "\n255\n";
}

void ModuleRayTracing::WriteColor(const Color& color)
{
	int ir = int(255.99*color.r);
	int ig = int(255.99*color.g);
	int ib = int(255.99*color.b);
	_ppmImage << ir << " " << ig << " " << ib << "\n";
}