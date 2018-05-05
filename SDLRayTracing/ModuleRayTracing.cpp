#include "ModuleRayTracing.h"

#include "Application.h"
#include "Color.h"
#include "Config.h"
#include "HitInfo.h"
#include "Math.h"
#include "Material.h"
#include "ModuleCamera.h"
#include "ModuleEntities.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ScatterInfo.h"
#include "Timer.h"

ModuleRayTracing::ModuleRayTracing() : Module(MODULERAYTRACING_NAME)
{
}

ModuleRayTracing::~ModuleRayTracing()
{
}

bool ModuleRayTracing::Init(Config* config)
{
	_randomGenerator = new math::LCG();

	_rayTracingTime = new Timer();
	_frequencyTimer = new Timer();

	_maxScatters = config->GetInt("MaxScatters");
	_minDistance = config->GetFloat("MinDistance");
	_maxDistance = config->GetFloat("MaxDistance");

	_samplesPerPixel = config->GetFloat("SamplesPerPixel");
	_pixelsPerUpdate = config->GetFloat("PixelPerUpdate");

	_pixelsWidth = App->_window->GetWindowsWidth();
	_pixelsHeight = App->_window->GetWindowsHeight();

	_currentX = GetInitialPixelX();
	_currentY = GetInitialPixelY();

	InitFile();

	return true;
}

bool ModuleRayTracing::Start()
{
	_rayTracingTime->Start();

	return true;
}

bool ModuleRayTracing::CleanUp()
{
	_ppmImage.close();

	RELEASE(_rayTracingTime);
	RELEASE(_frequencyTimer);

	RELEASE(_randomGenerator);

	return true;
}

update_status ModuleRayTracing::Update()
{
	if (_screenFinished)
	{
		return UPDATE_CONTINUE;
	}

	_frequencyTimer->Start();
	for (int i = 0; i < _pixelsPerUpdate; i++)
	{
		Color color = CalculatePixelColor(_currentX, _currentY);
		App->_renderer->DrawPixel(color, _currentX, _currentY);
		WriteColor(color);

		if (++_currentX >= _pixelsWidth)
		{
			_currentX = 0;
			if (--_currentY < 0)
			{
				_screenFinished = true;
				float seconds = _rayTracingTime->GetTimeInS();
				APPLOG("RayTracing finished after %f seconds", seconds);
				_rayTracingTime->Stop();
				break;
			}
		}
	}

	_accumulatedMs += _frequencyTimer->GetTimeInMs();
	_accumulatedRays += _pixelsPerUpdate * _samplesPerPixel;
	if (_accumulatedMs >= 1000)
	{
		Uint32 raysPerSecond = _accumulatedRays * 1000 / _accumulatedMs;
		_accumulatedRPS += raysPerSecond;
		++_currentAccumulated;
		APPLOG("Averaged: %lu rays per second", _accumulatedRPS / _currentAccumulated);

		_accumulatedMs -= 1000;
		_accumulatedRays -= raysPerSecond;
	}
	_frequencyTimer->Stop();

	return UPDATE_CONTINUE;
}

Color ModuleRayTracing::CalculatePixelColor(int xPixel, int yPixel) const
{
	Vector3 color = Vector3::zero;
	for (int i = 0; i < _samplesPerPixel; i++)
	{
		float u = float(xPixel + _randomGenerator->Float()) / float(_pixelsWidth);
		float v = float(yPixel + _randomGenerator->Float()) / float(_pixelsHeight);
		Ray ray = App->_camera->GenerateRay(u, v, *_randomGenerator);
		color += CalculateRayColor(ray, 0);
	}
	Color averagedColor(color / _samplesPerPixel);
#if GAMMA_CORRECTION
	return Color(sqrt(averagedColor.r), sqrt(averagedColor.g), sqrt(averagedColor.b));
#else
	return averagedColor;
#endif
}

Vector3 ModuleRayTracing::CalculateRayColor(const Ray& ray, int depth) const
{
	HitInfo hitInfo;
	bool isHit = App->_entities->Hit(ray, _minDistance, _maxDistance, hitInfo);

	if (isHit)
	{
		ScatterInfo scatterInfo;
		if (depth < _maxScatters && hitInfo.material->Scatter(ray, hitInfo, scatterInfo, *_randomGenerator))
		{
			Vector3 color = Vector3::zero;
			if (scatterInfo.reflects)
			{
				color += scatterInfo.reflectionCoeff * CalculateRayColor(scatterInfo.reflectedRay, depth + 1);
			}
			if (scatterInfo.refracts)
			{
				color += scatterInfo.refractionCoeff * CalculateRayColor(scatterInfo.refractedRay, depth + 1);
			}

			return scatterInfo.attenuation * color;
		}

		return Vector3::zero;
	}
	
	return CalculateBackgroundColor(ray);
}

Vector3 ModuleRayTracing::CalculateBackgroundColor(const Ray& ray) const
{
	float t = 0.5f * (ray.dir.y() + 1.0f);
	return (1.0f - t) * Vector3::one + t * Vector3(0.5f, 0.7f, 1.0f);
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

int ModuleRayTracing::GetInitialPixelY() const
{
	return _pixelsHeight - 1;
}

int ModuleRayTracing::GetInitialPixelX() const
{
	return 0;
}