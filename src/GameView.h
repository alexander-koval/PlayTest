#pragma once
#include "GUI/Widget.h"

class Bubble;
typedef boost::intrusive_ptr<Bubble> BubblePtr;
class GameView : public GUI::Widget
{
public:
	GameView(const std::string& name, rapidxml::xml_node<>* elem);
	virtual ~GameView();

	virtual void Draw();
	virtual void Update(float dt);
	
	virtual void AcceptMessage(const Message& message);
	
	virtual bool MouseDown(const IPoint& mouse_pos);
	virtual void MouseMove(const IPoint& mouse_pos);
	virtual void MouseUp(const IPoint& mouse_pos);

private:
	void Init();

private:

	Render::Texture* m_texture;
//	Render::SpritePtr m_sprite;
	std::vector<BubblePtr> m_bubbles;
    std::unique_ptr<Render::SpriteBatch> m_spriteBatch;
};

