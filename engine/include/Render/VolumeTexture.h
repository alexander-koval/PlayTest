#ifndef __VOLUMETEXTURE_H__
#define __VOLUMETEXTURE_H__

#pragma once

#include "Utils/FPoint.h"
#include "Utils/Math.hpp"
#include "Render/Texture.h"
#include "Core/Resource.h"

namespace Core
{
	class ResourceManager;
}

#if defined(ENGINE_TARGET_WIN32)
#	include <GLES2/gl2.h>
#	include <GLES2/gl2ext.h>
#	define DEVVOLUMETEXTURE GLuint
#endif

#ifdef ENGINE_TARGET_IPHONE
#	include <OpenGLES/ES2/gl.h>
#	define DEVVOLUMETEXTURE GLuint
#endif

#ifdef ENGINE_TARGET_ANDROID
#	include <GLES/gl.h>
#	include <GLES/glext.h>
#	define DEVVOLUMETEXTURE GLuint
#endif

#ifdef ENGINE_TARGET_MACOS
#	include <OpenGL/OpenGL.h>
#	define DEVVOLUMETEXTURE GLuint
#endif

namespace Render
{
class RenderDeviceGLES2;

// ����� 3D ��������
class VolumeTexture : public Resource, public Bindable
{
	friend class RenderDeviceGLES2;

public:
	std::string textureID;

	VolumeTexture();
	virtual ~VolumeTexture();
		
	static VolumeTexture* CreateFromXml(rapidxml::xml_node<>* elem);
		
	virtual const std::string& GetName() const override { return textureID; }
	virtual size_t GetMemoryInUse() const override;

	/// �������� �� ��������� ��� ������������� ���������. ������������� ����������� ������������ �������� ��� ����������������� RenderDeviceImpl.
	bool Empty() const override;

	/// ��������� �������� � �������� �����
	virtual void Bind(int channel = 0, int stageOp = 0) override;

	virtual TextureType GetTextureType() const override { return TextureType::VolumeTexture; }

	virtual const void* GetNativeHandle() const override { return reinterpret_cast<const void*>(_tex); }

	/// ��������� ��������
	virtual void Upload();
	/// ��������� ��������
	virtual void Release();

protected:
	std::string path;

	/// ���� �� �������� ���������
	bool wasUploaded;

	DEVVOLUMETEXTURE _tex;
};

typedef boost::intrusive_ptr<VolumeTexture> VolumeTexturePtr;
}

#endif // __VOLUMETEXTURE_H__
