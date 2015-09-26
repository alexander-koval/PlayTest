#ifndef __CUBETEXTURE_H__
#define __CUBETEXTURE_H__

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
#	define DEVCUBETEXTURE GLuint
#endif

#ifdef ENGINE_TARGET_IPHONE
#	include <OpenGLES/ES2/gl.h>
#	define DEVCUBETEXTURE GLuint
#endif

#if defined(ENGINE_TARGET_LINUX)
#	include <GLES/gl.h>
#	include <GLES/glext.h>
#	define DEVCUBETEXTURE GLuint
#endif

#ifdef ENGINE_TARGET_MACOS
#	include <OpenGL/OpenGL.h>
#	define DEVCUBETEXTURE GLuint
#endif

namespace Render
{
class RenderDeviceGLES2;

// ����� ���������� ��������
class CubeTexture : public Resource, public Bindable
{
	friend class RenderDeviceGLES2;

public:
	std::string textureID;

	CubeTexture();
	virtual ~CubeTexture();

	void SetFaceFileName(int face, const std::string& path);
		
	static CubeTexture* CreateFromXml(rapidxml::xml_node<>* elem);
		
	virtual const std::string& GetName() const override { return textureID; }
	virtual size_t GetMemoryInUse() const override;

	/// �������� �� ���������, ��� ������������� ���������. ������������� ����������� ������������ �������� ��� ����������������� RenderDeviceImpl. ��. Texture::setDynamic
	bool Empty() const override;

	/// ��������� �������� � �������� �����
	virtual void Bind(int channel = 0, int stageOp = 0) override;

	virtual const void* GetNativeHandle() const override { return reinterpret_cast<const void*>(_tex); }

	virtual TextureType GetTextureType() const override { return TextureType::CubeTexture; }

	/// ��������� ��������
	virtual void Upload();
		/// ��������� ��������
	virtual void Release();
		
protected:

	//���� true, �� paths ������ ���� � ��������� ������ ��������
	//� ������� -x, -y, -z, +x, +y, +z. ���� �����-�� �� paths ������, �� ��� ����� �������� ������
	//���� false, �� paths[0] ������ ������� ���� � ��������, ������� �������������� �������
	//��������� ��������, ��������� �� ���������� (�� ������, ����� �� ����-�� ������ ���������,
	//��������� ��� �������� �������������)
	bool hasSeparatePaths;
	std::string paths[6];

	/// ���� �� �������� ���������
	bool wasUploaded;

	DEVCUBETEXTURE _tex;
	EnginePixelType _pixelType;
};

typedef boost::intrusive_ptr<CubeTexture> CubeTexturePtr;
}

#endif // __CUBETEXTURE_H__
