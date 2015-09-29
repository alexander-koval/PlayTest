#include "stdafx.h"
#include "GameView.h"
#include "Bomb.h"
#include "Monster.h"
#include "Shockwave.h"
#include "GameInfo.h"

GameView::GameView(const std::string& name, rapidxml::xml_node<>* elem)
	: GUI::Widget(name, elem)
	, m_texture(nullptr)
	, m_monsters(GameInfo::instance().getNumMonsters())
	, m_catchers()
	, m_monsterPool(GameInfo::instance().getNumMonsters(), GameInfo::instance().getNumMonsters())
	, m_catcherPool(GameInfo::instance().getNumCatchers(), GameInfo::instance().getNumCatchers())
	, m_effects()
	, m_shadow()
	, m_leftCatchers(0)
	, m_catchedMonsters(0)
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
	for (std::vector<MonsterPtr>::iterator it = m_monsters.begin(); it != m_monsters.end(); ++it) {
		if (*it) (*it)->Draw();
	}

	for (std::vector<ShockwavePtr>::iterator it = m_catchers.begin(); it != m_catchers.end(); ++it) {
		if (*it) (*it)->Draw();
	}
	m_effects.Draw();


	Render::BindFont("Sansation");
	if (isLevelFailed()) {
		Render::PrintString(width / 2, height / 2, "LEVEL FAILED\nPress RIGTH MOUSE BUTTON to restart", 1.f, CenterAlign, BaseLineAlign);
	} else if (isLevelComplete()) {
		Render::PrintString(width / 2, height / 2, "LEVEL COMPLETE\nPress RIGHT MOUSE BUTTON to continue", 1.f, CenterAlign, BaseLineAlign);		
	}

	Render::PrintString(width - 100, height - 10, "Level: " + std::to_string(GameInfo::instance().getCurrentLevel()));
	Render::PrintString(10, height - 10, "Monsters Catched: " + std::to_string(m_catchedMonsters) + " from " + std::to_string(GameInfo::instance().getNumMonstersToCatch()));
	Render::PrintString(10, height - 40, "Catchers: " + std::to_string(m_leftCatchers));
}

void GameView::Update(float dt)
{
	GUI::Widget::Update(dt);
    UpdateMonsters(dt);
    UpdateShockwaves(dt);
	m_effects.Update(dt);
}

void GameView::AcceptMessage(const Message& message)
{

}

bool GameView::MouseDown(const IPoint& mouse_pos) {
	if (Core::mainInput.GetMouseRightButton()) {
		if (isLevelComplete() || isLevelFailed()) {
			if (isLevelComplete()) { GameInfo::instance().nextLevel(); }
			Cleanup();
			Init();
		}
	} else {
		if (m_leftCatchers > 0 && !isLevelComplete() && !isLevelFailed()) {
			SpawnCatcher(mouse_pos);
			m_leftCatchers = (m_leftCatchers > 0) ? --m_leftCatchers : 0;
		}
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
	m_catchedMonsters = 0;
	m_leftCatchers = GameInfo::instance().getNumCatchers();
	int numMonsters = GameInfo::instance().getNumMonsters();
	for (std::size_t index = 0; index < numMonsters; ++index)
	{
        MonsterPtr monster = m_monsterPool.get();
		monster->SetPosition(IPoint(math::random(0, width - monster->Width()), math::random(0, height - monster->Height())));
		monster->SetVelocity(math::random(-100, 100), math::random(-0, 0), 0);
        monster->SetState(Monster::StateAlive);
		m_monsters[index] = std::move(monster);
	}
}

void GameView::Cleanup() {
	m_catchedMonsters = 0;
	m_leftCatchers = 0;
	int numMonsters = GameInfo::instance().getNumMonsters();
    std::vector<MonsterPtr> monsters(numMonsters);
    m_monsters.swap(monsters);
    for (std::vector<MonsterPtr>::iterator it = monsters.begin(); it != monsters.end(); ++it) {
        if (*it) m_monsterPool.set(*it);
    }
    
    std::vector<ShockwavePtr> shockwaves;
    m_catchers.swap(shockwaves);
    for (std::vector<ShockwavePtr>::iterator it = shockwaves.begin(); it != shockwaves.end(); ++it) {
        if (*it) m_catcherPool.set(*it);
    }
}

void GameView::UpdateMonsters(float dt) {
	for (std::size_t index = 0; index < m_monsters.size(); ++index) {
		const MonsterPtr& monster = m_monsters[index];
		if (monster) {
			CollideWithWall(*monster);
			monster->Update(dt);
			CollideWithShockwaves(*monster);
			if (monster->IsDead()) {
				m_shadow = m_effects.AddEffect("Shadow");
				m_shadow->posX = monster->GetPosition().x;
				m_shadow->posY = monster->GetPosition().y;
                m_monsterPool.set(monster);
				std::swap(m_monsters[index], m_monsters.back());
				m_monsters.resize(m_monsters.size() - 1);
				m_shadow->Reset();
			}
		}
	}
}

void GameView::UpdateShockwaves(float dt) {
	for (std::size_t index = 0; index < m_catchers.size(); ++index) {
        const ShockwavePtr& shockwave = m_catchers[index];
        shockwave->Update(dt);
        if (!shockwave->IsAlive()) {
            m_catcherPool.set(shockwave);
			std::swap(m_catchers[index], m_catchers.back());
			m_catchers.resize(m_catchers.size() - 1);
        }		
	}
}

void GameView::SpawnCatcher(const IPoint& position) {
    ShockwavePtr shockwave = m_catcherPool.get();
    if (shockwave)
    {
        shockwave->Invalidate();
        shockwave->SetPosition(IPoint(position.x, position.y));
        shockwave->SetStartScale(.01f);
        shockwave->SetEndScale(1.f);
        shockwave->SetScale(.1f);
        shockwave->SetLifetime(1.f);
        shockwave->SetGrowTime(.5f);
        m_catchers.push_back(std::move(shockwave));
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
        std::vector<ShockwavePtr>::iterator it = m_catchers.begin();
        while (it != m_catchers.end()) {
            if (*it && (*it)->IsAlive()) {
                bool result = CollideWithShockwave(monster, *(*it));
                if (result) {
                    monster.SetState(Monster::StateDieing);
                    SpawnCatcher(monster.GetPosition());
					++m_catchedMonsters;
                    break;
                }
            }
            ++it;
        }
    }
}

bool GameView::isLevelComplete() const
{
	const GameInfo& gameInfo = GameInfo::instance();
	int numMonstersToCatch = gameInfo.getNumMonstersToCatch();
	return (numMonstersToCatch <= m_catchedMonsters);
}

bool GameView::isLevelFailed() const {
	const GameInfo& gameInfo = GameInfo::instance();
	return (m_leftCatchers <= 0 && m_catchers.size() == 0 && !isLevelComplete());
}