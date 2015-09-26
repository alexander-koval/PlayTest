#ifndef __RENDERTARGET_H__
#define __RENDERTARGET_H__

#pragma once

#include "Render/Texture.h"
#include "Render/RenderTypes.h"
#include "Render/Bindable.h"
#include "Utils/IRect.h"

namespace Render {

//
// Объект, ведущий себя подобно текстуре, в который можно что-то рисовать.
//
// Особенности:
// 1) тот кто создал объект методом Render::RenderDeviceImpl::CreateRenderTarget,
//    обязан также удалить его методом Render::RenderDeviceImpl::DeleteRenderTarget;
// 2) при создании до вызова Render::device.BeginRenderTo таргет считается пустым (IsEmpty),
//    также он становится пустым при сбросе контекста на андроиде;
//
class Target : public Bindable
{
public:
	virtual ~Target();

	bool needTranslate() const;
	
	void TranslateUV(FPoint& uv) const;
	void TranslateUV(FRect& rect, FRect& uv) const;
	void TranslateUV(math::Vector3& v0, math::Vector3& v1, math::Vector3& v2, math::Vector3& v3, FRect &uv) const;

	/// Возвращает ширину таргета
	int Width() const { return static_cast<int>(_width); }
	/// Возвращает высоту таргета
	int Height() const { return static_cast<int>(_height); }

	/// Возвращает рисуемую часть таргета
	IRect getBitmapRect() const { return IRect(IPoint(0, 0), _width, _height); }

	/// Пустой ли Таргет.
	/// Пустой таргет есть валидный таргет, но его содержимое было утеряно в результате сброса устройства
	virtual bool Empty() const override;

	///
	/// Установка текущей текстурой
	///
	virtual void Bind(int cannel = 0, int stageOp = 0) override;

	///
	/// Возвращает тип объекта
	///
	virtual TextureType GetTextureType() const override { return TextureType::Target; }

	///
	/// Возвращает идентификатор объекта в устройстве
	///
	virtual const void* GetNativeHandle() const override { return reinterpret_cast<const void*>(_texture); }

	///
	/// Рисование текстуры
	///
	void Draw(const FPoint& position);

	///
	/// Использует ли таргет мультисэмплинг
	///
	bool IsMultisampled() const;

	///
	/// Сохраняет содержимое в буфер.
	/// Работает только между вызовами BeginRenderTo()/EndRenderTo().
	///
	bool CopyToImage(Image& image);

	///
	/// Сохранить в формате BMP
	/// Особенность: переворачивает текстуру по вертикали
	/// Работает только между вызовами BeginRenderTo()/EndRenderTo().
	///
	void SaveAsBmp(const std::string & path);

	///
	/// Сохранить в формате PNG
	/// Особенность: переворачивает текстуру по вертикали
	/// Работает только между вызовами BeginRenderTo()/EndRenderTo().
	///
	void SaveAsPng(const std::string & path);
	
	///
	/// Сохранить в формате JPEG
	/// Работает только между вызовами BeginRenderTo()/EndRenderTo().
	///
	void SaveAsJpeg(const std::string& path, int quality = 80);

private:
	///
	/// Конструктор скрыт для всех кроме RenderDeviceImpl
	///
	Target(int width, int height);

	///
	/// Очистить ресурсы, которыми владеет объект
	///
	void Release();

private:
	friend class RenderDeviceGLES2;

	DEVTEXTURE _texture;	
	DEVTEXTURE _depthStencilBuffer;
	DEVTEXTURE _stencilSeparateBuffer;

#if defined(ENGINE_TARGET_IPHONE)
    DEVTEXTURE _msRB;
    DEVTEXTURE _msDB;
    DEVTEXTURE _msFB;
#endif
	
	int16_t _width;      ///< ширина текстуры
	int16_t _height;     ///< высота текстуры
	int16_t _widthPow2;  ///< ширина текстуры, округлённая до ближайшей большей степени двойки
	int16_t _heightPow2; ///< высота текстуры, округлённая до ближайшей большей степени двойки

	EnginePixelType _pixelType; ///< Формат пикселя
	MultisampleType _msType;    ///< тип мультисэмплинга

	bool _empty        : 1; ///< Пуста ли цель рендеринга
	bool _depth        : 1; ///< Используется ли depth buffer
	bool _stencil      : 1; ///< Используется ли stencil buffer
	bool _multisampled : 1; ///< Используется ли сглаживание
};

} // namespace Render

#endif // __RENDERTARGET_H__
