#ifndef __SKINNEDMESH_H__
#define __SKINNEDMESH_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "SceneGraph/Mesh.h"
#include "SceneGraph/BoneContent.h"
#include "Utils/Vector3.h"

#include <boost/intrusive_ptr.hpp>

namespace SceneGraph {

typedef boost::intrusive_ptr<class SkinnedMesh> SkinnedMeshPtr;

///
/// Скелетный меш.
///
class SkinnedMesh : public Mesh {
public:
	typedef std::vector<BoneContentPtr> BonesContent;
	typedef std::vector<CBone::Weights> VertexWeights;
	typedef std::vector<SceneGraph::AxisAlignedBoundingBox> BonesAABBoxes;

protected:
	SkinnedMesh();
	SkinnedMesh(SkinnedMesh& rhs);

public:	
	Mesh* Clone();	
	size_t GetMemoryInUse() const;

public:	
	void setSkeleton(ModelNode* _node);
	inline void setSkinInfo(BonesContent&& _skinInfo){ _m_skinInfo = boost::make_shared<BonesContent>(_skinInfo); }; /// устанавливает информацию по скинигу

public:
	virtual bool Hit(const math::Vector3 &base, const math::Vector3 &dir) const;
	AxisAlignedBoundingBox GetAABBox(const math::Matrix4& _view) const;

public:	
	static SkinnedMeshPtr Create(); /// Создаёт объект меша, но не заполняет его данными

protected:
	SkinnedMesh& operator=(const SkinnedMesh& rhs); /// Копирование запрещено

protected:
	void init();
	void deinit();

protected:
	std::vector<SceneNode*> _m_bonesToFrames;

	boost::shared_ptr<BonesContent> _m_skinInfo; /// Skininfo - информация по скинингу
	boost::shared_ptr<VertexWeights> _vertexWeights; /// переформатированная информация по скиннингу наоборот, т.е в ней хранится врешина и кости от которых она зависит, шарится между всеми прототипами
	boost::shared_ptr<BonesAABBoxes> _m_bonesAABBoxes; //AABBохы для костей, данного меша, шарится между всеми прототипами
};

} // namespace SceneGraph

#endif // __SKINNEDMESH_H__
