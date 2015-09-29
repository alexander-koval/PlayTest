#pragma once

#include "Gameable.h"

class Shockwave : public Gameable
{
public:
	Shockwave();

	virtual ~Shockwave();

	void Invalidate();

	void Draw() override;
	
	void Update(float dt) override;
	
	int Width() const override;
	
	int Height() const override;

	void SetEndScale(float scale);

	float GetEndScale() const;

	void SetStartScale(float scale);

	float GetStartScale() const;

	void SetLifetime(float time);

	float GetLifetime() const;

	void SetGrowTime(float time);

	float GetGrowTime() const;

	float GetRadius() const;

	bool IsAlive() const;

private:
	void Init();

private:
	using EyesPtr = std::unique_ptr < Render::Animation > ;
	float m_endScale;
	float m_startScale;
	float m_growTime;
	float m_lifetime;
	float m_elapsed;
	bool m_isAlive;
	float m_rotation;
	EyesPtr m_animation;
	
};

