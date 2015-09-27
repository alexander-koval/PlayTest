#include "stdafx.h"
#include "Shockwave.h"


Shockwave::Shockwave()
: Gameable()
, m_endScale(1.f)
, m_startScale(.1f)
, m_growTime(0.f)
, m_lifetime(0.f)
, m_elapsed(0.f)
, m_isAlive(true)
, m_texture(nullptr)
{
	Init();
}

Shockwave::~Shockwave()
{
}

void Shockwave::Invalidate()
{
	m_elapsed = 0.f;
	m_isAlive = true;
}

void Shockwave::Draw()
{
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(m_position.x, m_position.y, 0);
	Render::device.MatrixScale(m_scale);
	Render::device.MatrixTranslate(-m_texture->Width() * .5f, -m_texture->Height() * .5f, 0);
	m_texture->Draw();
	Render::device.PopMatrix();
}

void Shockwave::Update(float dt)
{
	if (m_scale < m_endScale && m_lifetime > m_elapsed)
	{
		m_scale += (m_endScale - m_startScale) / m_growTime * dt;
	}

	if (m_lifetime < m_elapsed && m_scale > 0.f)
	{
		m_scale -= (m_endScale - m_startScale) / 0.5f * dt;
	}
	if (m_elapsed < m_lifetime + 0.5f)
	{
		m_elapsed += dt;		
	} else
	{
		m_isAlive = false;
	}
}

int Shockwave::Width() const
{
	if (m_texture)
	{
		return m_texture->Width() * m_scale;
	}
	return 0;

}

int Shockwave::Height() const
{ 
	if (m_texture)
	{
		return m_texture->Height() * m_scale;
	}
	return 0;
}

void Shockwave::Init()
{
	m_texture = Core::resourceManager.Get<Render::Texture>("Shockwave");
}

void Shockwave::SetEndScale(float scale)
{
	m_endScale = scale;
}

float Shockwave::GetEndScale() const
{
	return m_endScale;
}

void Shockwave::SetStartScale(float scale)
{
	m_startScale = scale;
}

float Shockwave::GetStartScale() const
{
	return m_startScale;
}

void Shockwave::SetLifetime(float time)
{
	m_lifetime = time;
}

float Shockwave::GetLifetime() const
{
	return m_lifetime;
}

void Shockwave::SetGrowTime(float time)
{
	m_growTime = time;
}

float Shockwave::GetGrowTime() const
{
	return m_growTime;
}

float Shockwave::GetRadius() const
{
	return Width() * 0.5f;
}

bool Shockwave::IsAlive() const
{
	return m_isAlive;
}