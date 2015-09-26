#ifndef __LAZYKEYFRAMEDANIMATION_H__
#define __LAZYKEYFRAMEDANIMATION_H__

#include "SceneGraph/KeyFramedAnimation.h"

namespace SceneGraph {

class LazyKeyFramedAnimationPool;

class LazyKeyFramedAnimation: public KeyFramedAnimation {
public:
	typedef boost::intrusive_ptr<LazyKeyFramedAnimation> HardPtr;

	LazyKeyFramedAnimation(const std::string& name, float duration, float ticksPerSec, const std::string& filename, size_t pos);

	virtual void Play();
	virtual void Stop();
	virtual Animation::HardPtr Clone();
	virtual void SetModelNode(ModelNode* modelNode);

protected:
	LazyKeyFramedAnimation(const LazyKeyFramedAnimation& rhs);
	LazyKeyFramedAnimation& operator = (const LazyKeyFramedAnimation& rhs);

private:
	std::string _filename;
	size_t _pos;
	LazyKeyFramedAnimationPool* __m_pool;
};
	
}

#endif // __LAZYKEYFRAMEDANIMATION_H__

