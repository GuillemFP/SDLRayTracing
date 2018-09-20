#ifndef MODULEMATERIALS_H
#define MODULEMATERIALS_H

#define MODULEMATERIALS_NAME "ModuleMaterials"

#include "Module.h"
#include "ImageData.h"
#include <string>
#include <vector>

class Material;
class Texture;
struct MaterialData;
struct TextureData;

namespace math
{
	class LCG;
}

class ModuleMaterials : public Module
{
public:
	ModuleMaterials();
	~ModuleMaterials();

	Material* LoadMaterial(const MaterialData& data);

private:
	using VImageTex = std::vector<unsigned char*>;

	Texture* TextureFactory(const TextureData& data);
	ImageData CreateImage(const std::string& path);
	
	math::LCG* _rng = nullptr;
	VImageTex _images;
};

#endif // !MODULEMATERIALS_H