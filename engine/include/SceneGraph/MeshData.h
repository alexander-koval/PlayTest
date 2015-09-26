#ifndef __MESHDATA_H__
#define __MESHDATA_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include <RefCounter.h>
#include <Render/RenderTypes.h>

#include "AxisAlignedBoundingBox.h"

namespace SceneGraph {

///
/// Данные меша.
///
class MeshData : public RefCounter {
public:
	typedef std::vector<StaticMeshVert> Vertices;
	typedef std::vector<uint16_t> Indices;
	
	MeshData(const std::string& filename, size_t offset);
	MeshData(Vertices&& _vertices, Indices&& _indeces);

	size_t GetMemoryInUse() const;

	bool IsEmpty() const { return __vertices.empty(); }

	void LoadFromFile();
		/// Загружает данные из файла _filename

	void Clear();
		/// Удаляет данные
		
	const Vertices& GetVertexData() const { return __vertices; }
		/// Возвращает коллекцию вершин
	
	const Indices& GetIndexData() const { return __indices; }
		/// Возвращает коллекцию индексов
	
	const AxisAlignedBoundingBox& GetBoundingBox() const { return __aabbox; }
		/// Возвращает ограничивающий параллелепипед

private:
	void __init();

private:
	std::string _filename;
		/// Имя бинарного файла данных

	size_t _offset;
		/// Смещение начала данных в файле

	Vertices __vertices;
		/// Данные буфера вершин
	
	Indices __indices;
		/// Данные буфера индексов
	
	AxisAlignedBoundingBox __aabbox;
		/// Ограничивающий параллелепипед для набора точек
};

typedef boost::intrusive_ptr<MeshData> MeshDataPtr;

} // namespace SceneGraph

#endif // __MESHDATA_H__
