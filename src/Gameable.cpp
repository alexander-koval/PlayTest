#include "stdafx.h"
#include "Gameable.h"


Gameable::Gameable()
: m_scale(1.f)
, m_position()
{
}


Gameable::~Gameable()
{
}

void Gameable::SetPosition(const IPoint& position)
{
	m_position = position;
}

void Gameable::SetScale(float scale)
{
	m_scale = scale;
}

float Gameable::GetScale() const
{
	return m_scale;
}

IRect Gameable::GetLocalBounds() const
{
	return IRect(0, 0, Width(), Height());
}

IRect Gameable::GetGlobalBounds() const
{
	return IRect(m_position.x, m_position.y, Width(), Height());
}

const IPoint& Gameable::GetPosition() const
{
	return m_position;
}