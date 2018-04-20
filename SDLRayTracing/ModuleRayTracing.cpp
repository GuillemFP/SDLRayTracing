#include "ModuleRayTracing.h"

#include "Application.h"
#include "Color.h"
#include "Math.h"
#include "ModuleCamera.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"

namespace
{
	bool hitSphere(const float3& center, float radius, const Ray& ray)
	{
		float3 oc = ray.pos - center;
		float a = ray.dir.Dot(ray.dir);
		float b = 2.0f * oc.Dot(ray.dir);
		float c = oc.Dot(oc) - radius*radius;
		float discriminant = b*b - 4 * a*c;
		return (discriminant > 0);
	}

	Color calculateColor(const Ray& ray)
	{
		if (hitSphere(float3(1.0f, 0.0f, -4.0f), 0.5f, ray))
			return Color(1.0f, 0.0f, 0.0f);
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

	for (int j = _pixelsHeight - 1; j >= 0; j--)
	{
		for (int i = 0; i < _pixelsWidth; i++)
		{
			float u = float(i) / float(_pixelsWidth);
			float v = float(j) / float(_pixelsHeight);
			Ray ray = App->_camera->GenerateRay(u, v);
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