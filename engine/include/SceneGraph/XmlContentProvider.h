#ifndef __XMLCONTENTPROVIDER_H__
#define __XMLCONTENTPROVIDER_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "SceneGraph/ContentProvider.h"
#include "SceneGraph/ModelNode.h"
#include "SceneGraph/Mesh.h"
#include "SceneGraph/SkinnedMesh.h"
#include "SceneGraph/KeyFramedAnimation.h"
#include "SceneGraph/Material.h"

namespace SceneGraph {

///
/// Повайдер контента, загужающий скелетную модель из XML описания. 
///
class XmlContentProvider : public ContentProvider {
public:
	XmlContentProvider();
	
	~XmlContentProvider();
	
	ModelNode* LoadModel(const std::string& filename); /// Загружает модель из файла	
	ModelNode* LoadModel(rapidxml::xml_node<char>* xe);

private:
	void FindMeshNodes(ModelNode* pModel, SceneNode::HardPtr pNode);
		/// Рекурсивно ищет узлы мешей и добавляет их к коллекции детей модели 
	
	SceneNode::HardPtr LoadNode(SceneNode* parent, rapidxml::xml_node<char>* xe);
		/// Рекурсивно загружает узел с потомками 
	
	MeshPtr LoadMesh(rapidxml::xml_node<char>* xe);
		/// Загружает меш 
	
	BoneContentPtr LoadBoneContent(rapidxml::xml_node<char>* xe);
		/// Загружает веса вершин для костей скелета 
	
	Animation::HardPtr LoadAnimation(ModelNode* pModel, rapidxml::xml_node<char>* xe);
		/// Загружает анимацию
	
	AnimationChannel::HardPtr LoadAnimationChannel(KeyFramedAnimation* pAnimation, ModelNode* pModel, rapidxml::xml_node<char>* xe);
		/// Загружает канал анимации 
	
	MaterialPtr LoadMaterial(rapidxml::xml_node<char>* xe);
		/// Загружает материал 
	
	math::Matrix4 LoadMatrix(rapidxml::xml_node<char>* xe);
		/// Загружает матрицу трансформации 
	
	math::Vector3 LoadVector(rapidxml::xml_node<char>* xe);
		/// Загружает вектор
	
	math::Quaternion LoadQuaternion(rapidxml::xml_node<char>* xe);
		/// Загружает кватернион
};

} // namespace SceneGraph

#endif // __XMLCONTENTPROVIDER_H__
