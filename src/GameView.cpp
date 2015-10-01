#include "stdafx.h"
#include "GameView.h"
#include "Monster.h"
#include "Catcher.h"
#include "GameInfo.h"
#include "Game.h"

GameView::GameView(const std::string& name, rapidxml::xml_node<>* elem)
	: GUI::Widget(name, elem)
	  , m_texture(nullptr)
	  , m_monsters(Game::instance().GetGameInfo().getNumMonsters())
	  , m_catchers()
	  , m_monsterPool(Game::instance().GetGameInfo().getNumMonsters(), Game::instance().GetGameInfo().getNumMonsters())
	  , m_catcherPool(Game::instance().GetGameInfo().getNumCatchers(), Game::instance().GetGameInfo().getNumCatchers())
	  , m_effects()
	  , m_shadow()
	  , m_trails(Game::instance().GetGameInfo().getNumMonsters())
	  , m_leftCatchers(0)
	  , m_catchedMonsters(0) {
	IRect size = Core::appInstance->GetMainWindow()->GetClientSizes();
	width = size.width;
	height = size.height;
	Init();
}

GameView::~GameView() {
}

void GameView::Draw() {
	GUI::Widget::Draw();
	m_effects.Draw();
	for (std::vector<MonsterPtr>::iterator it = m_monsters.begin(); it != m_monsters.end(); ++it) {
		if (*it) (*it)->Draw();
	}

	for (std::vector<CatchersPtr>::iterator it = m_catchers.begin(); it != m_catchers.end(); ++it) {
		if (*it) (*it)->Draw();
	}

	Render::BindFont("Sansation");
	if (isLevelFailed()) {
		Render::PrintString(width * .5f, height * .5f, "LEVEL FAILED\nPress RIGTH MOUSE BUTTON to restart", 1.f, CenterAlign, BaseLineAlign);
	} else if (isLevelComplete()) {
		Render::PrintString(width * .5f, height * .5f, "LEVEL COMPLETE\nPress RIGHT MOUSE BUTTON to continue", 1.f, CenterAlign, BaseLineAlign);
	}

	Render::PrintString(width - 100, height - 10, "Level: " + std::to_string(Game::instance().GetGameInfo().getCurrentLevel()));
	Render::PrintString(10, height - 10, "Monsters Catched: " + std::to_string(m_catchedMonsters) + " from " + std::to_string(Game::instance().GetGameInfo().getNumMonstersToCatch()));
	Render::PrintString(10, height - 40, "Catchers: " + std::to_string(m_leftCatchers));
}

void GameView::Update(float dt) {
	GUI::Widget::Update(dt);
	UpdateMonsters(dt);
	UpdateCatchers(dt);
	m_effects.Update(dt);
}

void GameView::AcceptMessage(const Message& message) {
	if (message.getPublisher() == "Layer" && message.getData() == "LayerInit") {
		MM::manager.PlayTrack("ambient", true, 1.0f);
	}
}

bool GameView::MouseDown(const IPoint& mouse_pos) {
	if (Core::mainInput.GetMouseRightButton()) {
		if (isLevelComplete() || isLevelFailed()) {
			if (isLevelComplete()) {
				Game::instance().GetGameInfo().nextLevel();
			}
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

void GameView::Init() {
	m_catchedMonsters = 0;
	m_leftCatchers = Game::instance().GetGameInfo().getNumCatchers();
	size_t numMonsters = Game::instance().GetGameInfo().getNumMonsters();
	m_trails.resize(numMonsters);
	m_catchers.reserve(m_leftCatchers);
	for (std::size_t index = 0; index < numMonsters; ++index) {
		MonsterPtr monster = m_monsterPool.get();
		m_trails[index] = m_effects.AddEffect("Trail");
		m_trails[index]->posX = monster->GetPosition().x;
		m_trails[index]->posY = monster->GetPosition().y;
		monster->SetPosition(IPoint(math::random(0, width - monster->Width()), math::random(0, height - monster->Height())));
		monster->SetVelocity(math::random(-100, 100), math::random(-100, 100), 0);
		monster->SetState(Monster::StateAlive);
		m_monsters[index] = std::move(monster);
		m_trails[index]->Reset();
	}
}

void GameView::Cleanup() {
	m_catchedMonsters = 0;
	m_leftCatchers = 0;
	int numMonsters = Game::instance().GetGameInfo().getNumMonsters();
	std::vector<MonsterPtr> monsters(numMonsters);
	m_monsters.swap(monsters);
	for (std::vector<MonsterPtr>::iterator it = monsters.begin(); it != monsters.end(); ++it) {
		if (*it) m_monsterPool.set(*it);
	}

	std::vector<CatchersPtr> catchers;
	m_catchers.swap(catchers);
	for (std::vector<CatchersPtr>::iterator it = catchers.begin(); it != catchers.end(); ++it) {
		if (*it) m_catcherPool.set(*it);
	}
	
	m_trails.clear();
	m_effects.KillAllEffects();
}

void GameView::UpdateMonsters(float dt) {
	for (std::size_t index = 0; index < m_monsters.size(); ++index) {
		const MonsterPtr& monster = m_monsters[index];
		if (monster) {
			CollideWithWall(*monster);
			monster->Update(dt);
			CollideWithCatchers(*monster);
			m_trails[index]->posX = monster->GetPosition().x;
			m_trails[index]->posY = monster->GetPosition().y;
			if (monster->IsDead()) {
				m_trails[index]->Finish();
				m_shadow = m_effects.AddEffect("Shadow");
				m_shadow->posX = monster->GetPosition().x;
				m_shadow->posY = monster->GetPosition().y;
				m_monsterPool.set(std::move(monster));
				std::swap(m_monsters[index], m_monsters.back());
				std::swap(m_trails[index], m_trails.back());
				m_monsters.resize(m_monsters.size() - 1);
				m_trails.resize(m_trails.size() - 1);
				m_shadow->Reset();
			}
		}
	}
}

void GameView::UpdateCatchers(float dt) {
	for (std::size_t index = 0; index < m_catchers.size(); ++index) {
		const CatchersPtr& catcher = m_catchers[index];
		catcher->Update(dt);
		if (!catcher->IsAlive()) {
			m_catcherPool.set(std::move(catcher));
			std::swap(m_catchers[index], m_catchers.back());
			m_catchers.resize(m_catchers.size() - 1);
		}
	}
}

void GameView::SpawnCatcher(const IPoint& position) {
	const GameInfo& gameInfo = Game::instance().GetGameInfo();
	CatchersPtr catcher = m_catcherPool.get();
	if (catcher) {
		catcher->Invalidate();
		catcher->SetPosition(IPoint(position.x, position.y));
		catcher->SetStartScale(.1f);
		catcher->SetEndScale(1.f);
		catcher->SetScale(.1f);
		catcher->SetLifetime(gameInfo.getCatcherBornTime() + gameInfo.getCatcherLifetime());
		catcher->SetGrowTime(gameInfo.getCatcherBornTime());
		catcher->SetHideTIme(gameInfo.getCatcherHidetime());
		m_catchers.push_back(std::move(catcher));
		MM::manager.PlaySample("hide_in", false, 1.f);
	}
}

void GameView::CollideWithWall(Monster& monster) {
	const math::Vector3& vel = monster.GetVelocity();
	if (monster.GetPosition().x < 0 || monster.GetPosition().x > width) {
		monster.SetVelocity(-vel.x, vel.y, vel.z);
	}
	if (monster.GetPosition().y < 0 || monster.GetPosition().y > height) {
		monster.SetVelocity(vel.x, -vel.y, vel.z);
	}
}

bool GameView::CollideWithCatcher(Monster& monster, Catcher& cathcer) {
	IPoint deltaPoint = monster.GetPosition() - cathcer.GetPosition();
	float distance = std::sqrt(deltaPoint.x * deltaPoint.x + deltaPoint.y * deltaPoint.y);
	return distance < monster.Height() * 0.5f + cathcer.GetRadius();
}

void GameView::CollideWithCatchers(Monster& monster) {
	if (monster.IsAlive()) {
		std::vector<CatchersPtr>::iterator it = m_catchers.begin();
		while (it != m_catchers.end()) {
			if (*it && (*it)->IsAlive()) {
				bool result = CollideWithCatcher(monster, *(*it));
				if (result) {
					monster.SetState(Monster::StateDieing);
					SpawnCatcher(monster.GetPosition());
					++m_catchedMonsters;
					MM::manager.PlaySample("scream_01", false, .2f);
					break;
				}
			}
			++it;
		}
	}
}

bool GameView::isLevelComplete() const {
	const GameInfo& gameInfo = Game::instance().GetGameInfo();
	size_t numMonstersToCatch = gameInfo.getNumMonstersToCatch();
	return (numMonstersToCatch <= m_catchedMonsters);
}

bool GameView::isLevelFailed() const {
	const GameInfo& gameInfo = Game::instance().GetGameInfo();
	return (m_leftCatchers <= 0 && m_catchers.size() == 0 && !isLevelComplete());
}
