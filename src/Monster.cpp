#include "stdafx.h"
#include "Monster.h"


Monster::Monster() 
	: m_position()
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
		current->Draw(m_position);
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

void Monster::SetPosition(const IPoint& position)
{
	m_position = position;
}

const IPoint& Monster::GetPosition() const
{
	return m_position;
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

IRect Monster::GetLocalBounds() const
{
	return IRect(0, 0, Width(), Height());
}

IRect Monster::GetGlobalBounds() const
{
	return IRect(m_position.x, m_position.y, Width(), Height());
}

void Monster::Init()
{
	m_idle.reset(Core::resourceManager.Get<Render::Animation>("Bianfu1Idle")->Clone());
	m_die.reset(Core::resourceManager.Get<Render::Animation>("Bianfu1Die")->Clone());
	m_idle->setCurrentFrame(math::random(m_idle->getFirstPlayedFrame(), m_idle->getLastPlayedFrame()));
//	m_idle->setPlayback(true);
	m_current = m_idle;	
}