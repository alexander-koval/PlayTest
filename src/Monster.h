#pragma once

#include "Gameable.h"
#include "Utils.h"
#include "Render.h"
#include <map>

class Monster : public Gameable
{
public:
    enum States {
        StateAlive,
        StateDead,
        StateDieing,
        StatesAmount
    };
    
	Monster();

	virtual ~Monster();

	virtual void Draw() override;

	virtual void Update(float dt) override;

	void SetVelocity(const math::Vector3& velocity);

	void SetVelocity(float x, float y, float z = 0);

	const math::Vector3& GetVelocity() const;

	int Width() const override;

	int Height() const override;
    
    void SetState(States state);

	bool IsAlive() const;
    
    bool IsDead() const;
    
    bool IsDieing() const;

private:
	void Init(void);

	math::Vector3 Wander();

private:
	bool m_isAlive;
	float m_wanderAngle;
	float m_wanderDistance;
	float m_wanderRadius;
	float m_wanderRange;
    States m_currentState;
	math::Vector3 m_velocity;
	intrusive_weak_ptr<Render::Animation> m_current;
    std::map< States, boost::intrusive_ptr<Render::Animation> > m_animations;
};

