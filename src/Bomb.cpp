#include "stdafx.h"
#include "Bomb.h"


Bomb::Bomb()
	: Gameable()
	, m_timer(0.f)
	, m_scale(0.2f)
	, m_sparcleRotation(0.f)
	, m_bombTexture(nullptr)
	, m_sparcleTexture(nullptr)
{
	Init();
}

Bomb::~Bomb()
{
}

void Bomb::Draw()
{
	Render::device.PushMatrix();

	Render::device.MatrixTranslate(m_position.x, m_position.y, 0);
	Render::device.MatrixScale(m_scale);
	Render::device.MatrixTranslate(-m_bombTexture->Width() * .5f, -m_bombTexture->Height() * .5f, 0);
	m_bombTexture->Draw();

	Render::device.MatrixTranslate(m_bombTexture->Width() * .72f, m_bombTexture->Height() * .72f, 0);
	Render::device.MatrixRotate(math::Vector3(0, 0, 1), m_sparcleRotation);
	Render::device.MatrixTranslate(-m_sparcleTexture->Width() * .5f, -m_sparcleTexture->Height() * .5f, 0);
	m_sparcleTexture->Draw();

	Render::device.PopMatrix();
}

void Bomb::Update(float dt)
{
	m_timer += dt;

	while (m_timer > math::PI)
	{
		m_timer -= math::PI;
	}

	//m_scale = sinf(m_timer);
//	m_scale = 
	m_sparcleRotation += 180 * dt;
	if (m_sparcleRotation > 360)
	{
		m_sparcleRotation -= 360;
	}
}

int Bomb::Width() const
{
	if (m_bombTexture)
	{
		return m_bombTexture->Height() * m_scale;
	}
	return 0;
}

int Bomb::Height() const
{
	if (m_bombTexture)
	{
		return m_bombTexture->Width() * m_scale;
	}
	return 0;
}

void Bomb::Init()
{
	m_bombTexture = Core::resourceManager.Get<Render::Texture>("Bomb");
	m_sparcleTexture = Core::resourceManager.Get<Render::Texture>("Sparcle");
}
