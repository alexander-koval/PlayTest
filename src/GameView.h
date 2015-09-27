#pragma once
#include "GUI/Widget.h"

class Bubble;
class Monster;
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
	using MonsterPtr = std::unique_ptr < Monster > ;
	Render::Texture* m_texture;
	std::vector<MonsterPtr> m_monsters;
	//std::unique_ptr<Monster> m_monster;
	//Render::Animation* m_animation;
//	Render::SpritePtr m_sprite;
//	std::vector<BubblePtr> m_bubbles;
//    std::unique_ptr<Render::SpriteBatch> m_spriteBatch;
};

