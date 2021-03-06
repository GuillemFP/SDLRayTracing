#include "ModuleRayTracing.h"

#include "Application.h"
#include "BvhNode.h"
#include "Color.h"
#include "Config.h"
#include "Globals.h"
#include "HitInfo.h"
#include "Math.h"
#include "Material.h"
#include "ModuleCamera.h"
#include "ModuleEntities.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ScatterInfo.h"
#include "Timer.h"
#include <omp.h>
#include <algorithm>

namespace
{
	bool HitEntity(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo, const EntitiesInfo& entitiesInfo, math::LCG& randomGenerator)
	{
#if USE_BVH
		return entitiesInfo.rootNode->Hit(ray, minDistance, maxDistance, hitInfo);
#else
		HitInfo currentHitInfo;
		float currentMaxDistance = maxDistance;
#if USE_C_ARRAYS
		for (size_t i = 0; i < entitiesInfo.size; i++)
		{
			if (entitiesInfo.entities[i]->Hit(ray, minDistance, currentMaxDistance, currentHitInfo, randomGenerator))
			{
				currentMaxDistance = currentHitInfo.distance;
				hitInfo = currentHitInfo;
			}
		}
#else
		const VEntity& entities = entitiesInfo.entities;
		for (VEntity::const_iterator it = entities.cbegin(); it != entities.cend(); ++it)
		{
			if ((*it)->Hit(ray, minDistance, currentMaxDistance, currentHitInfo, randomGenerator))
			{
				currentMaxDistance = currentHitInfo.distance;
				hitInfo = currentHitInfo;
			}
		}
#endif // USE_C_ARRAYS
		return hitInfo.isHit;
#endif // USE_BVH
	}
}

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
	_numberOfThreads = std::min(config->GetInt("MaxNumberOfThreads", 1), omp_get_max_threads());

	_pixelsWidth = App->_window->GetWindowsWidth();
	_pixelsHeight = App->_window->GetWindowsHeight();
	_colorRow = new Color[_pixelsWidth];

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
	RELEASE_ARRAY(_colorRow);

	return true;
}

update_status ModuleRayTracing::Update()
{
	if (_screenFinished)
	{
		return UPDATE_CONTINUE;
	}

	_frequencyTimer->Start();

#if USE_BVH
	const BvhNode* entities = App->_entities->GetBvhRootNode();
#elif USE_C_ARRAYS 
	EntitiesInfo entities(App->_entities->GetDeviceEntities(), App->_entities->GetNumberOfEntities());
#else
	const VEntity& entities = App->_entities->GetEntities();
#endif // USE_BVH

#if USE_OPENMP_PIXEL_LOOP
	#pragma omp parallel for num_threads(_numberOfThreads)
#endif // USE_OPENMP
	for (int i = 0; i < _pixelsWidth; i++)
	{
		_colorRow[i] = CalculatePixelColor(i, _currentY, entities);
	}

	for (int i = 0; i < _pixelsWidth; i++)
	{
		App->_renderer->DrawPixel(_colorRow[i], i, _currentY);
		WriteColor(_colorRow[i]);
	}

	if (--_currentY < 0)
	{
		_screenFinished = true;
		float seconds = _rayTracingTime->GetTimeInS();
		APPLOG("RayTracing finished after %f seconds", seconds);
		_rayTracingTime->Stop();
	}

	_accumulatedMs += _frequencyTimer->GetTimeInMs();
	_accumulatedRays += _pixelsWidth * _samplesPerPixel;
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

Color ModuleRayTracing::CalculatePixelColor(int xPixel, int yPixel, const EntitiesInfo& entitiesInfo) const
{
	Vector3 color = Vector3::zero;
	for (int i = 0; i < _samplesPerPixel; i++)
	{
		float u = float(xPixel + _randomGenerator->Float()) / float(_pixelsWidth);
		float v = float(yPixel + _randomGenerator->Float()) / float(_pixelsHeight);
		Ray ray = App->_camera->GenerateRay(u, v, *_randomGenerator);
		color += CalculateRayColor(ray, 0, entitiesInfo);
	}
	Color averagedColor(color / _samplesPerPixel);

#if GAMMA_CORRECTION
	return Color(sqrt(averagedColor.r), sqrt(averagedColor.g), sqrt(averagedColor.b)).Capped();
#else
	return averagedColor.Capped();
#endif
}

Vector3 ModuleRayTracing::CalculateRayColor(const Ray& ray, int depth, const EntitiesInfo& entitiesInfo) const
{
	HitInfo hitInfo;
	bool isHit = HitEntity(ray, _minDistance, _maxDistance, hitInfo, entitiesInfo, *_randomGenerator);

	if (isHit)
	{
		ScatterInfo scatterInfo;
		Vector3 emissive = hitInfo.entity->GetEmissive(hitInfo);
		if (depth < _maxScatters && hitInfo.entity->Scatter(ray, hitInfo, scatterInfo, *_randomGenerator))
		{
			Vector3 color = Vector3::zero;
			if (scatterInfo.reflects)
			{
				color += scatterInfo.reflectionCoeff * CalculateRayColor(scatterInfo.reflectedRay, depth + 1, entitiesInfo);
			}
			if (scatterInfo.refracts)
			{
				color += scatterInfo.refractionCoeff * CalculateRayColor(scatterInfo.refractedRay, depth + 1, entitiesInfo);
			}

			return emissive + scatterInfo.attenuation * color;
		}

		if (depth == 0)
		{
			return emissive;
		}

		return emissive;
	}
	
	return App->_entities->GetSkyboxColor(hitInfo);
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