#include "Metal.h"

#include "Globals.h"
#include "HitInfo.h"
#include "Math.h"
#include "ScatterInfo.h"

namespace
{
	math::float3 reflect(const math::float3& rayDirection, const math::float3& normal)
	{		
		return rayDirection - 2.0f * rayDirection.Dot(normal) * normal;
	}
}

Metal::Metal(const math::float3& albedo) : Material(Material::Type::Metal), _albedo(albedo)
{
}

Metal::~Metal()
{
}

bool Metal::Scatter(const math::Ray& ray, const HitInfo& hitInfo, ScatterInfo& scatterInfo, math::LCG& randomGenerator) const
{
	scatterInfo.scatteredRay.pos = hitInfo.point;
	scatterInfo.scatteredRay.dir = reflect(ray.dir, hitInfo.normal);
	scatterInfo.attenuation = _albedo;

	scatterInfo.scatters = scatterInfo.scatteredRay.dir.Dot(hitInfo.normal) > 0;
	return scatterInfo.scatters;
}