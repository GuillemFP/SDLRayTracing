#include "Metal.h"

#include "Globals.h"
#include "HitInfo.h"
#include "Math.h"
#include "MathUtils.h"
#include "ScatterInfo.h"
#include "Texture.h"

Metal::Metal(Texture* texture, float fuzziness) : Material(Material::Type::Metal), _texture(texture), _fuzziness(fuzziness)
{
}

Metal::~Metal()
{
	RELEASE(_texture);
}

bool Metal::Scatter(const Ray& ray, const HitInfo& hitInfo, ScatterInfo& scatterInfo, math::LCG& randomGenerator) const
{
	scatterInfo.reflectedRay.pos = hitInfo.point;
	scatterInfo.reflectedRay.time = ray.time;                                                    

	Vector3 scatteredRay = MathUtils::ReflectedVector(ray.dir, hitInfo.normal) + _fuzziness * MathUtils::RandomPointInSphere(randomGenerator);
	scatterInfo.reflectedRay.dir = normalize(scatteredRay);
	scatterInfo.attenuation = _texture->GetColor(hitInfo);

	scatterInfo.reflects = dot(scatterInfo.reflectedRay.dir, hitInfo.normal) > 0;
	return scatterInfo.reflects;
}