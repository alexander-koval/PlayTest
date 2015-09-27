#pragma once

#include "Gameable.h"

class Monster : public Gameable
{
public:
	Monster();

	virtual ~Monster();

	virtual void Draw() override;

	virtual void Update(float dt) override;

	void SetVelocity(const math::Vector3& velocity);

	void SetVelocity(float x, float y, float z = 0);

	const math::Vector3& GetVelocity() const;

	int Width() const override;

	int Height() const override;

	void SetAlive(bool value);

	bool IsAlive() const;

private:
	void Init(void);

private:
	bool m_isAlive;
	math::Vector3 m_velocity;
	boost::intrusive_ptr<Render::Animation> m_idle;
	boost::intrusive_ptr<Render::Animation> m_die;
	intrusive_weak_ptr<Render::Animation> m_current;
};

