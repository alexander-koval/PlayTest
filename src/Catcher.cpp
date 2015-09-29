#include "stdafx.h"
#include "Catcher.h"


Catcher::Catcher()
: Gameable()
, m_endScale(1.f)
, m_startScale(.1f)
, m_growTime(0.f)
, m_lifetime(0.f)
, m_elapsed(0.f)
, m_isAlive(true)
, m_animation()
{
	Init();
}

Catcher::~Catcher()
{
}

void Catcher::Invalidate()
{
	m_elapsed = 0.f;
	m_isAlive = true;
	m_rotation = math::random(0, 360);
}

void Catcher::Draw()
{
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(m_position.x, m_position.y, 0);
	Render::device.MatrixScale(m_scale);
	Render::device.MatrixRotate(math::Vector3(0, 0, 1), m_rotation);
	Render::device.MatrixTranslate(-m_animation->getFrameWidth() * .5f, -m_animation->getFrameHeight() * .5f, 0);
	Render::BeginAlphaMul((m_scale <= 1.f && m_scale > 0.f) ? m_scale : 1.f);
	m_animation->Draw();
	Render::EndAlphaMul();
	Render::device.PopMatrix();
}

void Catcher::Update(float dt)
{
	if (m_scale < m_endScale && m_lifetime > m_elapsed) {
		m_scale += (m_endScale - m_startScale) / m_growTime * dt;
	}
	if (m_lifetime < m_elapsed && m_scale > 0.f) {
		m_scale -= (m_endScale - m_startScale) / 0.5f * dt;
	}
	if (m_elapsed < m_lifetime + 0.5f) {
		m_elapsed += dt;		
	} else {
		m_isAlive = false;
	}
	m_animation->Update(dt);
}

int Catcher::Width() const
{
	if (m_animation) {
		return m_animation->getFrameWidth() * m_scale;
	}
	return 0;

}

int Catcher::Height() const
{ 
	if (m_animation) {
		return m_animation->getFrameHeight() * m_scale;
	}
	return 0;
}

void Catcher::Init()
{
	Invalidate();
	m_animation.reset(Core::resourceManager.Get<Render::Animation>("EyeWatch")->Clone());
}

void Catcher::SetEndScale(float scale)
{
	m_endScale = scale;
}

float Catcher::GetEndScale() const
{
	return m_endScale;
}

void Catcher::SetStartScale(float scale)
{
	m_startScale = scale;
}

float Catcher::GetStartScale() const
{
	return m_startScale;
}

void Catcher::SetLifetime(float time)
{
	m_lifetime = time;
}

float Catcher::GetLifetime() const
{
	return m_lifetime;
}

void Catcher::SetGrowTime(float time)
{
	m_growTime = time;
}

float Catcher::GetGrowTime() const
{
	return m_growTime;
}

float Catcher::GetRadius() const
{
	return Width() * 0.5f;
}

bool Catcher::IsAlive() const
{
	return m_isAlive;
}