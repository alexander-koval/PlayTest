#pragma once
#include "GUI/Widget.h"
#include "SpritePool.h"
#include "Bomb.h"

class Bomb;
class Bubble;
class Monster;
class Shockwave;
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
    
    void Cleanup();
    
    void UpdateMonsters(float dt);
    
    void UpdateShockwaves(float dt);
    
    void SpawnMonster(const IPoint& position);
    
    void SpawnShockwave(const IPoint& position);

	void CollideWithWall(Monster& monster);
    
	bool CollideWithShockwave(Monster& monster, Shockwave& shockwave);

    void CollideWithShockwaves(Monster& monster);

private:
	using MonsterPtr = boost::intrusive_ptr<Monster>;
	using ShockwavePtr = boost::intrusive_ptr<Shockwave> ;
    Render::Texture* m_texture;
	std::unique_ptr<Bomb> m_bomb;
	std::vector<MonsterPtr> m_monsters;
	std::vector<ShockwavePtr> m_shockwaves;
    SpritePool<Monster> m_monsterPool;
	SpritePool<Shockwave> m_shockwavePool;

	EffectsContainer m_effects;
	ParticleEffectPtr m_shadow;

};

