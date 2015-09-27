#include "stdafx.h"
#include "GameView.h"
#include "Bubble.h"
#include "Monster.h"
#include "Render/SpriteBatch.h"

GameView::GameView(const std::string& name, rapidxml::xml_node<>* elem) 
	: GUI::Widget(name, elem)
	, m_texture(nullptr)
	, m_monsters(50)
{
	width = 768;
	height = 1024;
	Init();
}

GameView::~GameView()
{
}

void GameView::Draw()
{
	/*
	m_spriteBatch->Begin();

	const Color& color = Render::device.GetCurrentColor();
	Render::device.SetCurrentColor(Color::BLUE);
	m_sprite->Draw(m_spriteBatch.get(), FPoint(200, 200));
	Render::device.SetCurrentColor(Color::RED);
	m_sprite->Draw(m_spriteBatch.get(), FPoint(200, 400));
	Render::device.SetCurrentColor(color);
	m_spriteBatch->End();
	*/
//	Render::device.MatrixScale(0.5f);
	for (std::vector<MonsterPtr>::iterator it = m_monsters.begin(); it != m_monsters.end(); ++it)
	{
		const MonsterPtr& monster = *it;
		monster->Draw();
	}
//	Render::device.MatrixScale(1.f);
}

void GameView::Update(float dt)
{
	for (std::vector<MonsterPtr>::iterator it = m_monsters.begin(); it != m_monsters.end(); ++it)
	{
		const MonsterPtr& monster = *it;
		const math::Vector3& vel = monster->GetVelocity();
		if (monster->GetPosition().x < 0 || monster->GetPosition().x + monster->Width() > width)
		{
			monster->SetVelocity(-vel.x, vel.y, vel.z);
		}
		if (monster->GetPosition().y < 0 || monster->GetPosition().y + monster->Height() > height)
		{
			monster->SetVelocity(vel.x, -vel.y, vel.z);
		}
		monster->Update(dt);
	}
}

void GameView::AcceptMessage(const Message& message)
{
}

bool GameView::MouseDown(const IPoint& mouse_pos)
{
	return false;
}

void GameView::MouseMove(const IPoint& mouse_pos)
{
}

void GameView::MouseUp(const IPoint& mouse_pos)
{
}

void GameView::Init()
{
	m_texture = Core::resourceManager.Get<Render::Texture>("Dot");
	for (std::vector<MonsterPtr>::iterator it = m_monsters.begin(); it != m_monsters.end(); ++it)
	{
		Monster* monster = new Monster();
		monster->SetPosition(IPoint(math::random(0, width), math::random(0, height)));
		monster->SetVelocity(math::random(-100, 100), math::random(-100, 100), 0);
		it->reset(monster);
	}

//	m_sprite.reset(new Render::Sprite(m_texture));
//	m_bubblePtr->setColor(Color::BLACK);
}