#ifndef _RENDER_COMBINEDTEXTURE_H_
#define _RENDER_COMBINEDTEXTURE_H_

#include "Render/Texture.h"

namespace Render {

class CombinedTexture : public Texture
{
public:
	CombinedTexture();

	virtual size_t GetMemoryInUse() const;
		
	/// Забиндить текстуру. Параметры должны быть по-умолчанию, иначе ошибка.
	virtual void Bind(int channel = 0, int stageOp = 0);
		
	virtual bool isPixelTransparent(int x, int y) const;
		
	virtual TextureType GetTextureType() const { return TextureType::CombinedTexture; }

	void SetAlphaTexturePath(const std::string& path) { _alphaTexPath = path; }

	Texture* GetColorTexture() { return _colorTex.get(); }

	Texture* GetAlphaTexture() { return _alphaTex.get(); }

protected:
	/// Загрузить текстуру
	virtual void Upload(bool bCleanAfterUpload = true);
	/// Выгрузить текстуру
	virtual void Release();

	virtual void Purge();
		
	virtual void LoadFromFile(const std::string& filename = std::string());
	virtual void LoadFromImage(const Image& image_) { Assert(false); }

protected:
	std::string _alphaTexPath;

	TexturePtr _colorTex;
	TexturePtr _alphaTex;
};
	
} // namespace Render

#endif // _RENDER_COMBINEDTEXTURE_H_
