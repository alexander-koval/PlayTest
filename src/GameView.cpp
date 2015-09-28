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
	, m_monsters()
	, m_shockwaves()
    , m_monsterPool(MONSTER_COUNT, 0)
	, m_shockwavePool(SHOCKWAVE_COUNT, SHOCKWAVE_COUNT)
	, m_effects()
	, m_shadow()

{
    width = 768;//TestAppDelegate::WINDOW_WIDTH;
    height = 1024;//TestAppDelegate::WINDOW_HEIGHT;
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
	for (std::vector<MonsterPtr>::iterator it = m_monsters.begin(); it != m_monsters.end(); ++it) {
		if (*it) (*it)->Draw();
	}

	for (std::vector<ShockwavePtr>::iterator it = m_shockwaves.begin(); it != m_shockwaves.end(); ++it) {
		if (*it) (*it)->Draw();
	}
	m_bomb->Draw();
	m_effects.Draw();
}

void GameView::Update(float dt)
{
	GUI::Widget::Update(dt);
    UpdateMonsters(dt);
    UpdateShockwaves(dt);
	m_bomb->Update(dt);
	m_effects.Update(dt);
}

void GameView::AcceptMessage(const Message& message)
{

}

bool GameView::MouseDown(const IPoint& mouse_pos)
{
    SpawnShockwave(mouse_pos);
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
	for (std::size_t index = 0; index < MONSTER_COUNT; ++index)
	{
        MonsterPtr monster = m_monsterPool.get();
		monster->SetPosition(IPoint(math::random(0, width - monster->Width()), math::random(0, height - monster->Height())));
		monster->SetVelocity(math::random(-100, 100), math::random(-0, 0), 0);
        monster->SetState(Monster::StateAlive);
		m_monsters.push_back(std::move(monster));
	}
}

void GameView::Cleanup() {
    std::vector<MonsterPtr> monsters;
    m_monsters.swap(monsters);
    for (std::vector<MonsterPtr>::iterator it = monsters.begin(); it != monsters.end(); ++it) {
        if (*it) m_monsterPool.set(*it);
    }
    
    std::vector<ShockwavePtr> shockwaves;
    m_shockwaves.swap(shockwaves);
    for (std::vector<ShockwavePtr>::iterator it = shockwaves.begin(); it != shockwaves.end(); ++it) {
        if (*it) m_shockwavePool.set(*it);
    }
}

void GameView::UpdateMonsters(float dt) {
    std::vector<MonsterPtr>::iterator it = m_monsters.begin();
    while (it != m_monsters.end()) {
        const MonsterPtr& monster = *it;
        if (monster) {
            CollideWithWall(*monster);
            monster->Update(dt);
            CollideWithShockwaves(*monster);
            if (monster->IsDead()) {
				m_shadow = m_effects.AddEffect("Shadow");
				m_shadow->posX = monster->GetPosition().x;
				m_shadow->posY = monster->GetPosition().y;
                m_monsterPool.set(monster);
                it = m_monsters.erase(it);
				m_shadow->Reset();
                continue;
            }
        }
        ++it;
    }
}

void GameView::UpdateShockwaves(float dt) {
    std::vector<ShockwavePtr>::iterator it = m_shockwaves.begin();
    while (it != m_shockwaves.end()) {
        const ShockwavePtr& shockwave = *it;
        shockwave->Update(dt);
        if (!shockwave->IsAlive()) {
            m_shockwavePool.set(shockwave);
            it = m_shockwaves.erase(it);
            continue;
        }
        ++it;
    }
}

void GameView::SpawnMonster(const IPoint& position) {
//    MonsterPtr monster = m_monsterPool.get();
//    if (monster) {
//        monster->SetPosition(position);
//        monster->SetState(Monster::StateAlive);
//        m_monsters->push_back(std::move(monster));
//    }
}

void GameView::SpawnShockwave(const IPoint& position) {
    ShockwavePtr shockwave = m_shockwavePool.get();
    if (shockwave)
    {
        shockwave->Invalidate();
        shockwave->SetPosition(IPoint(position.x, position.y));
        shockwave->SetStartScale(.01f);
        shockwave->SetEndScale(1.f);
        shockwave->SetScale(.1f);
        shockwave->SetLifetime(1.f);
        shockwave->SetGrowTime(.5f);
        m_shockwaves.push_back(std::move(shockwave));
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
    return distance < monster.Height() * 0.5f + shockwave.GetRadius();
}

void GameView::CollideWithShockwaves(Monster& monster) {
    if (monster.IsAlive()) {
        std::vector<ShockwavePtr>::iterator it = m_shockwaves.begin();
        while (it != m_shockwaves.end()) {
            if (*it && (*it)->IsAlive()) {
                bool result = CollideWithShockwave(monster, *(*it));
                if (result) {
                    monster.SetState(Monster::StateDieing);
                    SpawnShockwave(monster.GetPosition());
                    break;
                }
            }
            ++it;
        }
    }
}