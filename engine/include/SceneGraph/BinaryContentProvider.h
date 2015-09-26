#ifndef __BINARY_CONTENT_PROVIDER_H__
#define __BINARY_CONTENT_PROVIDER_H__

#ifdef _MSC_VER
#pragma once
#endif


#include <SceneGraph/ContentProvider.h>
#include <SceneGraph/ModelNode.h>
#include <SceneGraph/Mesh.h>
#include <SceneGraph/MeshData.h>
#include <SceneGraph/SkinnedMesh.h>
#include <SceneGraph/KeyFramedAnimation.h>
#include <SceneGraph/Material.h>
#include <Utils/Xml.h>

namespace SceneGraph {

/* Структура файла
	Версия
	Количество материалов, материалы
	Количество мешей, меши
	Количество узлов
	Узел
		Количество узлов
		Узел
		...
		Узел
		...
	Узел
	...
	Количество анимаций, анимации
*/

class BinaryContentProvider : public ContentProvider
{
public:
	BinaryContentProvider() :
		_lazyLoad(true)
	{
	}

public:
	ModelNode* LoadModel(const std::string& filename);

	// Сохраняет модель в бинарник
	void Binarize(const std::string& filename, const std::string& binaryFilename);

	static void LoadMeshData(const std::string& filename, size_t offset, MeshData::Vertices* _vertices, MeshData::Indices* _indeces);
	static void LoadChannelsToAnimation(const std::string& filename, size_t offset, KeyFramedAnimation* animation);

private:
	// Вспомогательные методы загрузки
	//
	void ReadMaterials();
	void ReadMeshes();
	Mesh* ReadMesh();
	void __ReadSkeleton(ModelNode* _model);
	SceneNode* ReadNode(SceneNode* parent);
	void ReadAnimations(ModelNode* _model);
	std::string ReadString();
	math::Matrix4 ReadMatrix();

	static int ReadMeshDataFrom(IO::InputStream* stream, MeshData::Vertices* _vertices, MeshData::Indices* _indeces);

	static void ReadStringFrom(IO::InputStream* stream, std::string& str);
	static void ReadMatrixFrom(IO::InputStream* stream, math::Matrix4& matrix);

	static void ReadChannelFrom(IO::InputStream* stream, KeyFramedAnimationChannel* channel = NULL);
	static void ReadChannelsFrom(IO::InputStream* stream, KeyFramedAnimation* animation = NULL);

	std::map<std::string, MaterialPtr> _materials;	// Материалы модели
	std::map<std::string, MeshPtr> _meshes;			// Меши модели
	IO::InputStreamPtr _stream;
	std::string _srcName;
	bool _lazyLoad;

	// Вспомогательные методы сохранения
	//
	void WriteMaterials();
	void WriteMeshes();
	void WriteMesh(pugi::xml_node meshXml);
	void WriteNodes();
	void WriteNode(pugi::xml_node nodeXml);
	void WriteAnimations();
	void WriteAnimation(pugi::xml_node animationXml);
	void WriteChannel(pugi::xml_node channelXml);
	void WriteString(const char *str);
	void WriteMatrix(pugi::xml_node matrixXml);

	FILE*_dest;
	pugi::xml_node _src;
};

} // namespace SceneGraph



#endif // __BINARY_CONTENT_PROVIDER_H__