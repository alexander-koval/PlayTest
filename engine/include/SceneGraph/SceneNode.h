#ifndef __SCENENODE_H__
#define __SCENENODE_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "SceneGraph/AxisAlignedBoundingBox.h"
#include "SceneGraph/SceneNode.h"
#include "Utils/Matrix4.h"
#include "Utils/Quaternion.h"
#include "Render/Target.h"
#include "RefCounter.h"

#include <map>

namespace SceneGraph {

class Scene;
class ModelNode;

///
/// ������� ����� ��� ���� ����� �����.
///
class SceneNode : public RefCounter {
public:
	typedef boost::intrusive_ptr<SceneNode> HardPtr;
	
	typedef std::map<std::string, SceneNode::HardPtr> SceneNodesMap;
	typedef std::list<SceneNode::HardPtr> SceneNodesList;
	
	///
	/// ����������� ���� ����� �����.
	///
	enum Type {
		Unknown,
			/// ����������� ���� (�� ������������)
		Frame,
			/// �����
		Mesh,
			/// ���
		Model,
			/// ������
		Light,
			/// �������� �����
		Camera
			/// ������
	};
	
	SceneNode(const std::string& name, SceneNode* parent, Scene* scene, SceneNode::Type type = SceneNode::Unknown);
	
	virtual SceneNode* Clone();

	virtual size_t GetMemoryInUse() const;
	
	SceneNode::Type GetType() const;
		/// ���������� ��� ���� �����
	
	void SetType(SceneNode::Type type);
		/// ������������� ��� ���� �����
	
	virtual unsigned int GetRenderPassMask() const;
		/// ���������� ���� �������� ������������, ��� ������� ������ ������������� ��������� ����
	
	const std::string& GetName() const;
		/// ���������� ��� ����
	
	void SetName(const std::string& name);
		/// ������������� ��� ����
	
	SceneNode* GetParent() const;
		/// ���������� ������������ ����
	
	void SetParent(SceneNode* parent);
		/// ������������� ������������ ����
	
	Scene* GetScene() const;
		/// ���������� �����, ������� ����������� ������ ����
	
	void SetScene(Scene* scene);
		/// ������������� �����, ������� ����������� ������ ����
	
	const math::Vector3& GetOriginalPosition() const;
	const math::Quaternion& GetOriginalRotation() const;
	const math::Vector3& GetOriginalScaling() const;
		/// ���������� �������� ������ �������������

	const math::Matrix4& GetOriginalTransform() const;
		/// ���������� ������� ��������� �������������� ����
	
	void SetOriginalTransform(const math::Matrix4& transform);
		/// ������������� ������� ��������� �������������� ����
	
	void MultiplyOriginalTransform(const math::Matrix4& transform);
		/// �������� ������� ��������� �������������� ���� �� ��������� ������� �������������
	
	void MultiplyOriginalTransformLocal(const math::Matrix4& transform);
		/// �������� �������� ������� ��������� �������������� ���� �� ��������� ������� �������������

	inline void AllFramesResetRelativeTransform(){_relativeTransform = _originalTransform;} /// ������������� ������� �������������� �������������� ������� ��������� ��������������

	const math::Matrix4& GetRelativeTransform() const;
		/// ���������� ������� �������������� �������������� ����
	
	void SetRelativeTransform(const math::Matrix4& transform);
		/// ������������� �������������� �������������� ����

	void SetAbsoluteTransform(const math::Matrix4& transform);
		/// ������������� ���������� �������������� ����
	
	void AddRelativeTransform(const math::Matrix4& transform);
		/// ��������� �������������� � �������������� �������������� ����
	
	void MultiplyRelativeTransform(const math::Matrix4& transform);
		/// �������� ������������� �������������� ���� �� ��������� ������� �������������
	
	void MultiplyRelativeTransformLocal(const math::Matrix4& transform);
		/// �������� �������� ������������� �������������� ���� �� ��������� ������� �������������
	
	void UpdateAbsoluteTransform();
		/// ���������� ��������� ������������� ���� ������������ ������� ������� ���������
	
	const math::Matrix4& GetAbsoluteTransform() const;
		/// ���������� ������� ����������� �������������� ����
	
	const AxisAlignedBoundingBox& GetBoundingBox() const;
		/// ���������� ����������� �� ���� �������������� �������������
	
	AxisAlignedBoundingBox GetTransformedBoundingBox() const;
		/// ���������� ������������������ �������������� �������������
	
	void SetBoundingBox(const AxisAlignedBoundingBox& aabbox);
		/// ������������� �������������� �������������, ����������� �� ����
	
	const SceneNodesMap& GetChildren() const; /// ���������� ��������� �������� �����
	
	bool AddChild(SceneNode::HardPtr node);
		/// ��������� ���� � ������ �������� �����
	
	SceneNode::HardPtr RemoveChild(const std::string& name);
		/// ������� ���� �� ������ �������� ����� ������������
	
	void Remove();
		/// ������� ���� �� ������ �������� ����� ��������
	
	SceneNode::HardPtr FindChild(const std::string& name) const;
		/// ���������� ���� ���� ����� �����
	
	virtual void Update(float dt);
		/// ���������� ������ ����� ��� ������� ���� �� ������� �������
	
	virtual void Draw() const;/// ���������� ������ ����� ��� ��������� ����

	virtual bool Hit(const math::Vector3 &base, const math::Vector3 &dir) const;
		/// �������� ��������� � ������, ��������� ��� �����
	
	virtual void acceptScene(const Scene* _scene);
protected:	
	SceneNode(const SceneNode& rhs);
	
	SceneNode& operator = (const SceneNode& rhs);

protected:
	SceneNode::Type _type;
		/// ��� ���� �����
	
	std::string _name;
		/// ���������� ��� ����
	
	Scene* _scene;
		/// �����, ������� ����������� ������ ����
	
	SceneNode* _parent;
		/// ������������ ����
	
	SceneNodesMap _children;
		/// ����������� ����� �� ���� ��� �������� ������ �����
	
		///
		/// �������������� OriginalTransform ������ ����� ������������� �������������� ����
		/// �� ��������� � �������������� ������������� ����, ������� ���������� �� �����
		/// ������������ � ��������������� �� ����� �������� ������.
		///
		/// �������������� RelativeTransform ��������������� ������ OriginalTransform
		/// � ������ ������� ����� � ����������� ���������������� �� ����� ��������� ��������.

	math::Vector3 _originalPosition;
	math::Quaternion _originalRotation;
	math::Vector3 _originalScaling;
		/// �������� �������������� ������������� (����������� �� ������ ������������ _originalTransform
		/// ����� ��� ��������� ������ ������������� ��-��������� ��� KeyframeAnimation

	math::Matrix4 _originalTransform; /// �������� ������������� ����.	
	math::Matrix4 _relativeTransform; /// ������������� ���� ������������ ������������ ������������� ����.	
	math::Matrix4 _absoluteTransform; /// ������������� ������������ �������� ������������.
		///
		/// �������������� AbsoluteTransform �������� ���������� �� ��������� � ����
		/// � �������������� ��� ���� �������� ������������ ����� ����,
		/// ��� ����� ����������� ��� ��������� � ������������� �������������� ���� ����� �����.
	
	AxisAlignedBoundingBox _aabbox;
		/// �������������� �������������, ����������� �� ����
};

} // namespace SceneGraph

#endif // __SCENENODE_H__
