#pragma once
class Gameable : public RefCounter
{
public:
	Gameable();

	virtual ~Gameable();

	virtual void Draw() = 0;

	virtual void Update(float dt) = 0;

	virtual void SetPosition(const IPoint& position);

	virtual const IPoint& GetPosition() const;

	virtual int Width() const = 0;

	virtual int Height() const = 0;

	virtual void SetScale(float scale);

	virtual float GetScale() const;

	virtual IRect GetLocalBounds() const;

	virtual IRect GetGlobalBounds() const;

protected:
	float m_scale;
	IPoint m_position;
};

