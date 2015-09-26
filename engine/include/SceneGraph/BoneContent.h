#ifndef __BONECONTENT_H__
#define __BONECONTENT_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include <Utils/Matrix4.h>
#include <RefCounter.h>

namespace SceneGraph {

typedef boost::intrusive_ptr<class CBone> BoneContentPtr;

///
/// ����� (���� ������ ����������� ����).
///
class CBone : public RefCounter
{
public:
	struct Weight{
		Weight(int _vertexindex, float _boneweight):
			vertexindex(_vertexindex),
			boneweight(_boneweight)
		{

		}

		int vertexindex; 
		float boneweight; 
	};

	typedef std::vector<Weight> Weights;

public:	
	CBone(const std::string& _name, const math::Matrix4& _invMatrix);

	size_t GetMemoryInUse() const;

	inline const std::string& getName(){return __m_name;};		
	inline const math::Matrix4& GetBoneOffset() const{ return __m_invMatrix; };
	
	inline const Weights& GetWeights() const{ return _weights; };
	inline void AddWeight(const Weight& weight){ _weights.push_back(weight); }; //������������ ������� � ������ �������� ���������

private:
	std::string __m_name; //��� �����, ������������ ��� ���������� ������ � ������(��������) �������
	Weights _weights;
	math::Matrix4 __m_invMatrix; //�������� ������� �������������� �����, ������ ���������� ������ �� ���������� ������� ��������� � ������� ��������� �������� � ������
};

} // namespace SceneGraph

#endif // __BONECONTENT_H__
