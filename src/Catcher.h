#pragma once

#include "Gameable.h"

class Catcher : public Gameable
{
public:
	Catcher();

	virtual ~Catcher();

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

	void SetHideTIme(float time);

	float GetHideTime() const;

	float GetRadius() const;

	bool IsAlive() const;

private:
	void Init();

private:
	using EyesPtr = std::unique_ptr < Render::Animation > ;
	float m_endScale;
	float m_startScale;
	float m_growTime;
	float m_hideTime;
	float m_lifetime;
	float m_elapsed;
	bool m_isAlive;
	float m_rotation;
	EyesPtr m_animation;
	
};

