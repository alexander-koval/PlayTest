#ifndef __EMITTERMASK_H__
#define __EMITTERMASK_H__

#pragma once

#include "Core/Resource.h"
#include "Core/ResourceLoader.h"
#include "Utils/random.hpp"

/// Маска эмиттера
class EmitterMask : public Resource {
public:
	EmitterMask(const std::string& filename, uint8_t luminanceMin, uint8_t luminanceMax, float scaleX, float scaleY);

	void SetPbiSource(const std::string& filename, size_t offset);

	const std::string& GetName() const { return _filename; }

	size_t GetMemoryInUse() const;

	FPoint RandomPoint(float scale = 1.0f) const;

	const std::string& GetFileName() const { return _filename; }

	uint8_t GetLuminanceMin() const { return _luminanceMin; }
	uint8_t GetLuminanceMax() const { return _luminanceMax; }
	
	float GetScaleX() const { return _scaleX; }
	float GetScaleY() const { return _scaleY; }

private:	
	std::string _filename;
	std::string _pbi_filename;
	size_t _pbi_offset;
	bool _usePoints;
	std::vector<IPoint> _points;
	uint8_t _luminanceMin, _luminanceMax;
	float _scaleX, _scaleY;

	// Ширина и высота изображения
	uint32_t _width, _height;

	std::vector<uint32_t> _distrFunction;
	uint32_t _normFactor;
	
private:
	friend class EmitterMaskLoader;

	void GetLuminanceData(std::vector<uint8_t>& luminance);
	void CalcDistrFunction(const std::vector<uint8_t>& luminance);

	void LoadMask();
	void UnloadMask();

private:
	EmitterMask(const EmitterMask&);
	EmitterMask& operator=(const EmitterMask&);
};

/// Загрузчик маски эмиттера
class EmitterMaskLoader : public ResourceLoader {
protected:
	void DoLoadData(Resource* resource);

	void DoLoadObject(Resource* resource);

	void DoUnload(Resource* resource);
};

#endif // __EMITTERMASK_H__
