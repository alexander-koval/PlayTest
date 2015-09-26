#ifndef __MESH_H__
#define __MESH_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "Render/VertexBuffer.h"
#include "Render/IndexBuffer.h"
#include "SceneGraph/SceneNode.h"
#include "SceneGraph/Material.h"
#include "SceneGraph/MeshData.h"
#include "Utils/Vector3.h"
#include "RefCounter.h"

#include <boost/intrusive_ptr.hpp>
#include <boost/shared_ptr.hpp>

namespace SceneGraph {

typedef boost::intrusive_ptr<class Mesh> MeshPtr;

///
/// Меш.
///
class Mesh : public RefCounter
{
protected:
	Mesh();
	Mesh(Mesh& rhs);
	virtual ~Mesh();

public:
	virtual Mesh* Clone();	
	virtual size_t GetMemoryInUse() const;

public:		
	MaterialPtr GetMaterial() const;/// Возвращает материал меша
	void SetMaterial(MaterialPtr material); /// Устанавливает материал меша	

	const MeshDataPtr GetData() const; /// Возвращает данные меша	
	void SetData(MeshDataPtr data); /// Устанавливает данные меша

	void SetRenderTarget(Render::Target *target);

public:
	void LoadData(); /// Загружает данные меша в аппаратные буферы, используется ресурсным менеджером и в момент потери графического контекста	
	void UnloadData(); /// Выгружает данные и освобождает аппаратные буферы, используется ресурсным менеджером
	
	virtual void Draw(); /// Отрисовывает себя
	virtual bool Hit(const math::Vector3 &base, const math::Vector3 &dir) const; /// Проверка попадания в меш
	virtual AxisAlignedBoundingBox GetAABBox(const math::Matrix4& _view) const; /// Возвращает ограничивающий параллелепипед, выровненный по осям координат(https://ru.wikipedia.org/wiki/AABB)

public:	
	static Mesh* Create(); /// Создаёт прототип меша

protected:
	virtual void init(); //Вызывается при ленивой инициализации прототипа, инициализирует только расшаренное между всеми прототипами состояние
	virtual void deinit(); //Вызывается при ленивой деинициализации прототипа, деинициализирует только расшаренное между всеми прототипами состояние

	virtual void LoadGPUVertexes(boost::shared_ptr<Render::VertexBuffer>& _vertexBufer);
	virtual void UpdateVertexes();

protected:
	Mesh& operator=(const Mesh& rhs); // Копирование запрещено

protected:
	boost::shared_ptr<Render::VertexBuffer> _vertices;
		/// Буфер вершин
	
	boost::shared_ptr<Render::IndexBuffer> _indices;
		/// Буфер индексов
	
	MaterialPtr _material;
		/// Материал меша
	
	MeshDataPtr _data;
		/// Данные меша

private:
	bool __m_initialized;
};

} // namespace SceneGraph

#endif // __MESH_H__
