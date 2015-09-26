#include "stdafx.h"
#include "GameView.h"
#include "Bubble.h"
#include "Render/SpriteBatch.h"

GameView::GameView(const std::string& name, rapidxml::xml_node<>* elem) 
	: GUI::Widget(name, elem)
	, m_texture(nullptr)
	, m_bubbles(50)
	, m_spriteBatch(new Render::SpriteBatch())
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
	m_spriteBatch->Begin();
	for (std::vector<BubblePtr>::iterator it = m_bubbles.begin(); it != m_bubbles.end(); ++it)
	{
		const BubblePtr& bubble_ptr = *it;
		bubble_ptr->Draw(m_spriteBatch.get());
	}
	m_spriteBatch->End();
//	Render::device.MatrixScale(1.f);
}

void GameView::Update(float dt)
{
	for (std::vector<BubblePtr>::iterator it = m_bubbles.begin(); it != m_bubbles.end(); ++it)
	{
		const BubblePtr& bubble_ptr = *it;
		const math::Vector3& vel = bubble_ptr->GetVelocity();
		if (bubble_ptr->GetPosition().x < 0 || bubble_ptr->GetPosition().x + bubble_ptr->Width() > width)
		{
			bubble_ptr->SetVelocity(-vel.x, vel.y, vel.z);
		}
		if (bubble_ptr->GetPosition().y < 0 || bubble_ptr->GetPosition().y + bubble_ptr->Height() > height)
		{
			bubble_ptr->SetVelocity(vel.x, -vel.y, vel.z);
		}
		
		bubble_ptr->Update(dt);
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
	for (std::vector<BubblePtr>::iterator it = m_bubbles.begin(); it != m_bubbles.end(); ++it)
	{
		Bubble* bubble = new Bubble(m_texture);
		bubble->SetScale(.1f);
		bubble->SetPosition(FPoint(math::random(0, width), math::random(0, height)));
		bubble->SetFillColor(Color(math::random(0, 255), math::random(0, 255), math::random(0, 255), 255));
		bubble->SetVelocity(math::random(-100, 100), math::random(-100, 100), 0);
		it->reset(bubble);
	}


//	m_sprite.reset(new Render::Sprite(m_texture));
//	m_bubblePtr->setColor(Color::BLACK);
}