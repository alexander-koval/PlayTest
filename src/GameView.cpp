#include "stdafx.h"
#include "GameView.h"
#include "Bomb.h"
#include "Monster.h"
#include "Shockwave.h"
#include "TestAppDelegate.h"

static const int SHOCKWAVE_COUNT = 10;
static const int MONSTER_COUNT = 10;

GameView::GameView(const std::string& name, rapidxml::xml_node<>* elem)
	: GUI::Widget(name, elem)
	, m_texture(nullptr)
	, m_bomb(new Bomb())
	, m_monsters(MONSTER_COUNT)
	, m_activeShockwaves()
	, m_shockwavePool(SHOCKWAVE_COUNT, SHOCKWAVE_COUNT)
{
	width = TestAppDelegate::WINDOW_WIDTH;
	height = TestAppDelegate::WINDOW_HEIGHT;
	Init();
}

GameView::~GameView()
{
}

void GameView::Draw()
{
	GUI::Widget::Draw();
	IPoint mousePosition = Core::mainInput.GetMousePos();
	m_bomb->SetPosition(IPoint(mousePosition.x + m_bomb->Width() * .5f, mousePosition.y + m_bomb->Height() * .5f));
	for (std::vector<MonsterPtr>::iterator it = m_monsters.begin(); it != m_monsters.end(); ++it)
	{
		const MonsterPtr& monster = *it;
		if (monster)
		{
			monster->Draw();
		}
	}

	for (std::vector<ShockwavePtr>::iterator it = m_activeShockwaves.begin(); it != m_activeShockwaves.end(); ++it)
	{
		const ShockwavePtr& shockwave = *it;
		shockwave->Draw();
	}
	m_bomb->Draw();
}

void GameView::Update(float dt)
{
	GUI::Widget::Update(dt);
	std::vector<MonsterPtr>::iterator monster_it = m_monsters.begin();
	while (monster_it != m_monsters.end())
	{
		const MonsterPtr& monster = *monster_it;
		if (monster)
		{
			CollideWithWall(*monster);
			monster->Update(dt);
			if (!monster->IsAlive())
			{
				monster_it = m_monsters.erase(monster_it);
				continue;
			}
		}
		++monster_it;
	}
	
	std::vector<ShockwavePtr>::iterator shockwave_it = m_activeShockwaves.begin();
	while (shockwave_it != m_activeShockwaves.end())
	{
		const ShockwavePtr& shockwave = *shockwave_it;
	    shockwave->Update(dt);
		if (!shockwave->IsAlive())
		{
			m_shockwavePool.set(shockwave);
			shockwave_it = m_activeShockwaves.erase(shockwave_it);
			continue;
		}
		++shockwave_it;
	}
	m_bomb->Update(dt);

	shockwave_it = m_activeShockwaves.begin();
	while (shockwave_it != m_activeShockwaves.end())
	{
		const ShockwavePtr& shockwave = *shockwave_it;
		if (shockwave->IsAlive())
		{
			monster_it = m_monsters.begin();
			while (monster_it != m_monsters.end())
			{
				const MonsterPtr& monster = *monster_it;
				if (monster->IsAlive())
				{
					bool result = CollideWithShockwave(*monster, *shockwave);
					if (result) monster->SetAlive(false);
				}
				++monster_it;
			}
		}
		++shockwave_it;
	}
}

void GameView::AcceptMessage(const Message& message)
{

}

bool GameView::MouseDown(const IPoint& mouse_pos)
{
	ShockwavePtr shockwave = m_shockwavePool.get();
	if (shockwave)
	{
		shockwave->Invalidate();
		shockwave->SetPosition(IPoint(mouse_pos.x, mouse_pos.y));
		shockwave->SetStartScale(.01f);
		shockwave->SetEndScale(1.f);
		shockwave->SetScale(.1f);
		shockwave->SetLifetime(5.f);
		shockwave->SetGrowTime(1.f);
		m_activeShockwaves.push_back(shockwave);
	}

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
	for (std::size_t index = 0; index < MONSTER_COUNT; ++index)
	{
		MonsterPtr monster(new Monster());
		monster->SetPosition(IPoint(math::random(0, width - monster->Width()), math::random(0, height - monster->Height())));
		monster->SetVelocity(math::random(-200, 200), math::random(-200, 200), 0);
		m_monsters[index] = std::move(monster);
	}
}

void GameView::CollideWithWall(Monster& monster)
{
	const math::Vector3& vel = monster.GetVelocity();
	if (monster.GetPosition().x < 0 || monster.GetPosition().x > width)
	{
		monster.SetVelocity(-vel.x, vel.y, vel.z);
	}
	if (monster.GetPosition().y < 0 || monster.GetPosition().y > height)
	{
		monster.SetVelocity(vel.x, -vel.y, vel.z);
	}
}

bool GameView::CollideWithShockwave(Monster& monster, Shockwave& shockwave)
{
	IPoint deltaPoint = monster.GetPosition() - shockwave.GetPosition();
	float distance = std::sqrt(deltaPoint.x * deltaPoint.x + deltaPoint.y * deltaPoint.y);
	if (distance < monster.Height() * 0.5f + shockwave.GetRadius())
	{
		return true;
	}
	return false;
}