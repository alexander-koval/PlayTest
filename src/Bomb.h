#pragma once

#include "Gameable.h"

namespace Render {
class Texture;
}

class Bomb : public Gameable
{
public:
	Bomb();

	virtual ~Bomb();

	virtual void Draw() override;

	virtual void Update(float dt) override;

	virtual int Width() const override;

	virtual int Height() const override;

private:
	void Init();

private:
	float m_timer;
	float m_scale;
	float m_sparcleRotation;
	Render::Texture* m_bombTexture;
	Render::Texture* m_sparcleTexture;
	
};

