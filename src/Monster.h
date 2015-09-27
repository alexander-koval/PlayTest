#pragma once

//#include "intrusive_weak_ptr.hpp"

class Monster
{
public:
	Monster();

	virtual ~Monster();

	virtual void Draw();

	virtual void Update(float dt);

	void SetPosition(const IPoint& position);

	const IPoint& GetPosition() const;

	void SetVelocity(const math::Vector3& velocity);

	void SetVelocity(float x, float y, float z = 0);

	const math::Vector3& GetVelocity() const;

	int Width() const;

	int Height() const;

	IRect GetLocalBounds() const;

	IRect GetGlobalBounds() const;

private:
	virtual void Init(void);

private:
	IPoint m_position;
	math::Vector3 m_velocity;
	boost::intrusive_ptr<Render::Animation> m_idle;
	boost::intrusive_ptr<Render::Animation> m_die;
	intrusive_weak_ptr<Render::Animation> m_current;
};

