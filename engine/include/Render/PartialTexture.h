#ifndef __PARTIALTEXTURE_H__
#define __PARTIALTEXTURE_H__

#pragma once

#include "Render/Texture.h"

namespace Render {

class Sheet;

/// ������ �������� ����������� �� ������� ����� ������ ��������.

/// ��� ��������������, ������� �� ������ � ���� �����������, � ������������ ����� ������������� Sheet'�. ��������� � ��������������� image � ���� ��� ����� �����������, ��� ������ ��� ���.
/// ����� �������� �������� ���������������� ����� ��������, � ��� �� ����� ������������
/// RenderDeviceImpl::TranslateUV.
class PartialTexture : public Texture 
{
	friend class Render::Sheet;

public:
	PartialTexture(Texture* texture, int x, int y, int w, int h, int ix, int iy, int fw, int fh, int aL, int texW = 0, int texH = 0);
	~PartialTexture();

	virtual const void* GetNativeHandle() const override { return texture->GetNativeHandle(); }
	virtual size_t GetMemoryInUse() const override { return sizeof(*this); }

	/// ��������� ����� �� ���������������� ���������� ����������. ���� ��, �� ���������� ������� TranslateUV ����� ����������.
	virtual bool needTranslate() const override;
	/// ������������� ���������� ���������. ���������� � RenderDeviceImpl ���� needTranslate ���������� true.
	virtual void TranslateUV(FPoint &uv) const override;
	/// ������������� ���������� ���������. ���������� � RenderDeviceImpl ���� needTranslate ���������� true.
	virtual void TranslateUV(FRect &rect, FRect &uv) const override;
	virtual void TranslateUV(math::Vector3& v0, math::Vector3& v1, math::Vector3& v2, math::Vector3& v3, FRect &uv) const override;

	/// ��������� ��������
	virtual void Bind(int channel = 0, int stageOp = 0) override;

	virtual TextureType GetTextureType() const override { return TextureType::PartialTexture; }

	virtual bool isPixelTransparent(int x, int y) const override;
	
	Render::Texture* GetBaseTexture() const { return texture.get(); }

	// ��������������� ������� �������� ������
	//
	virtual void Load(ResourceLoadMode load_mode) override;
	virtual void Unload(ResourceLoadMode load_mode) override;
	virtual void GroupLoad(ResourceLoadManager& glm) override;
	virtual void GroupUnload(ResourceLoadManager& glm) override;
	
protected:
	virtual void LoadFromFile(const std::string& filename) override { }
	virtual void LoadFromImage(const Image& image) override { }
	virtual void GetPropertiesFromFile(const std::string& filename) override { }

	/// ��������� ��������
	virtual void Release() override;

protected:
	/// �������� ������
	TexturePtr texture;
	/// ��������� � ������� ��������
	int16_t baseX, baseY, width, height, innerX, innerY, frameWidth, frameHeight, texW, texH;
	int16_t alphaLimit;
};

typedef boost::intrusive_ptr<PartialTexture> PartialTexturePtr;

} // namespace Render

#endif // __PARTIALTEXTURE_H__
