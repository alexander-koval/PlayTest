#include "stdafx.h"
#include "Bubble.h"

Bubble::Bubble(Render::Texture* texture) 
	: Render::Sprite(texture)
	, m_color()
	, m_scale(1.f)
    , m_position()
	, m_velocity() {
	Init();
}

Bubble::~Bubble()
{
}

void Bubble::Draw(Render::SpriteBatch* batch)
{
	Render::BeginColor(m_color);
	Render::Sprite::Draw(batch, m_position);
	Render::EndColor();
}

void Bubble::Update(float dt)
{
	m_position.x += m_velocity.x * dt;
	m_position.y += m_velocity.y * dt;
	//m_position.x += (m_velocity.x *= math::random(-1, 1));
	//m_position.y += (m_velocity.y *= math::random(-1, 1));
	//m_velocity.x *= 0.95f;
	//m_velocity.y *= 0.95f;
}

void Bubble::Init()
{

}

void Bubble::SetPosition(const FPoint& position)
{
	m_position = position;
}

const FPoint& Bubble::GetPosition() const
{
	return m_position;
}

void Bubble::SetScale(float scale)
{
	m_scale = scale;
}

float Bubble::GetScale() const
{
	return m_scale;
}

void Bubble::SetFillColor(const Color& color)
{
	m_color = color;
}

const Color& Bubble::GetFillColor() const
{
	return m_color;
}

void Bubble::SetVelocity(const math::Vector3& velocity)
{
	m_velocity = velocity;
}

void Bubble::SetVelocity(float x, float y, float z)
{
	m_velocity.x = x;
	m_velocity.y = y;
	m_velocity.z = z;
}

const math::Vector3& Bubble::GetVelocity() const
{
	return m_velocity;
}

int Bubble::Width() const
{
	return _texture->Width();
}

int Bubble::Height() const
{
	return _texture->Height();
}

IRect Bubble::GetLocalBounds() const
{
	return _texture->getBitmapRect();
}

IRect Bubble::GetGlobalBounds() const
{
	return IRect(m_position.x, m_position.y, _texture->Width(), _texture->Height());
}