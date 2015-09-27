#include "stdafx.h"
#include "Monster.h"


Monster::Monster()
	: Gameable()
	, m_isAlive(true)
	, m_velocity()
	, m_idle()
	, m_die()
	, m_current(m_idle)
{
	Init();
}


Monster::~Monster()
{
}

void Monster::Draw()
{
	Render::Animation* current = m_current.get();
	if (current)
	{
		current->Draw(IPoint(m_position.x - Width() * .5f, m_position.y - Height() * .5f));
	}
}

void Monster::Update(float dt)
{
	Render::Animation* current = m_current.get();
	if (current)
	{
		m_position.x += m_velocity.x * dt;
		m_position.y += m_velocity.y * dt;
		current->Update(dt);
	}
}

void Monster::SetVelocity(const math::Vector3& velocity)
{
	m_velocity = velocity;
}

void Monster::SetVelocity(float x, float y, float z)
{
	m_velocity.x = x;
	m_velocity.y = y;
	m_velocity.z = z;	
}

const math::Vector3& Monster::GetVelocity() const
{
	return m_velocity;
}

int Monster::Width() const
{
	Render::Animation* current = m_current.get();
	if (current)
	{
		return current->getFrameWidth();
	}
	return 0;
}

int Monster::Height() const
{
	Render::Animation* current = m_current.get();
	if (current)
	{
		return current->getFrameHeight();
	}
	return 0;
}

bool Monster::IsAlive() const
{
	return m_isAlive;
}

void Monster::SetAlive(bool alive)
{
	m_isAlive = alive;
}

void Monster::Init()
{
	m_idle.reset(Core::resourceManager.Get<Render::Animation>("Bianfu1Idle")->Clone());
	m_die.reset(Core::resourceManager.Get<Render::Animation>("Bianfu1Die")->Clone());
	m_idle->setCurrentFrame(math::random(m_idle->getFirstPlayedFrame(), m_idle->getLastPlayedFrame()));
	m_current = m_idle;	
}