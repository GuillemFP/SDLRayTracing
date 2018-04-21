#include "ModuleRayTracing.h"

#include "Application.h"
#include "Color.h"
#include "HitInfo.h"
#include "Math.h"
#include "ModuleCamera.h"
#include "ModuleEntities.h"
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

	//InitFile();

	for (int j = _pixelsHeight - 1; j >= 0; j--)
	{
		for (int i = 0; i < _pixelsWidth; i++)
		{
			float u = float(i) / float(_pixelsWidth);
			float v = float(j) / float(_pixelsHeight);
			math::Ray ray = App->_camera->GenerateRay(u, v);
			HitInfo hitInfo;
			Color color = App->_entities->Hit(ray, hitInfo) ? Color(0.5f * (hitInfo.normal + math::float3::one)) : CalculateBackgroundColor(ray);
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

	return true;
}

Color ModuleRayTracing::CalculateBackgroundColor(const math::Ray& ray) const
{
	math::float3 direction = ray.dir;
	float t = 0.5f * (direction.y + 1.0f);
	return (1.0f - t) * math::float3::one + t * math::float3(0.5f, 0.7f, 1.0f);
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