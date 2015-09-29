#pragma once
#include "GUI/Widget.h"
#include "SpritePool.h"

class Bomb;
class Bubble;
class Monster;
class Catcher;
typedef boost::intrusive_ptr<Bubble> BubblePtr;
class GameView : public GUI::Widget
{
public:
	GameView(const std::string& name, rapidxml::xml_node<>* elem);
	virtual ~GameView();

	virtual void Draw() override;
	virtual void Update(float dt) override;
	
	virtual void AcceptMessage(const Message& message) override;
	
	virtual bool MouseDown(const IPoint& mouse_pos) override;
	virtual void MouseMove(const IPoint& mouse_pos) override;
	virtual void MouseUp(const IPoint& mouse_pos) override;

private:
	void Init();
    
    void Cleanup();
    
    void UpdateMonsters(float dt);
    
    void UpdateShockwaves(float dt);
    
    void SpawnCatcher(const IPoint& position);

	void CollideWithWall(Monster& monster);
    
	bool CollideWithShockwave(Monster& monster, Catcher& shockwave);

    void CollideWithShockwaves(Monster& monster);

	bool isLevelComplete() const;

	bool isLevelFailed() const;

private:
	using MonsterPtr = boost::intrusive_ptr<Monster>;
	using ShockwavePtr = boost::intrusive_ptr<Catcher> ;
    Render::Texture* m_texture;
	std::vector<MonsterPtr> m_monsters;
	std::vector<ShockwavePtr> m_catchers;
    SpritePool<Monster> m_monsterPool;
	SpritePool<Catcher> m_catcherPool;

	EffectsContainer m_effects;
	ParticleEffectPtr m_shadow;

	std::size_t m_leftCatchers;
	std::size_t m_catchedMonsters;
};

