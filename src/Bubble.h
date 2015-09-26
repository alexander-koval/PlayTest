#pragma once
#include "Render/Sprite.h"

class Bubble : public Render::Sprite
{
public:
	Bubble(Render::Texture* tex);

	virtual ~Bubble();

	virtual void Draw(Render::SpriteBatch*);

	virtual void Update(float dt);

	void SetFillColor(const Color& color);

	const Color& GetFillColor(void) const;

	void SetPosition(const FPoint& position);

	const FPoint& GetPosition() const;

	void SetScale(float scale);

	float GetScale() const;

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
	Color m_color;
	float m_scale;
	FPoint m_position;
	math::Vector3 m_velocity;
};
