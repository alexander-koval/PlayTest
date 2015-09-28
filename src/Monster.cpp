#include "stdafx.h"
#include "Monster.h"

Monster::Monster()
	: Gameable()
	, m_isAlive(true)
	, m_wanderAngle(.0f)
	, m_wanderDistance(200.f)
	, m_wanderRadius(20.f)
	, m_wanderRange(10.f)
    , m_currentState(StateAlive)
	, m_velocity()
	, m_current()
	, m_animations()
{
	Init();
}


Monster::~Monster()
{
}

void Monster::Draw()
{
	Render::Animation* current = m_current.get();
	if (current)
	{
		current->Draw(IPoint(m_position.x - Width() * .5f, m_position.y - Height() * .5f));
	}
}

void Monster::Update(float dt)
{
	Render::Animation* current = m_current.get();
	if (current) {
		if (IsAlive()) {
			m_velocity += Wander();
			m_position.x += m_velocity.x * dt;
			m_position.y += m_velocity.y * dt;
			m_velocity.Normalize();
		}
        if (IsDieing() && current->IsFinished()) {
            SetState(States::StateDead);
		} 
		current->Update(dt);
	}
}

void Monster::SetVelocity(const math::Vector3& velocity)
{
	m_velocity = velocity;
}

void Monster::SetVelocity(float x, float y, float z)
{
	m_velocity.x = x;
	m_velocity.y = y;
	m_velocity.z = z;	
}

const math::Vector3& Monster::GetVelocity() const
{
	return m_velocity;
}

int Monster::Width() const
{
	Render::Animation* current = m_current.get();
	if (current)
	{
		return current->getFrameWidth();
	}
	return 0;
}

int Monster::Height() const
{
	Render::Animation* current = m_current.get();
	if (current)
	{
		return current->getFrameHeight();
	}
	return 0;
}

void Monster::SetState(Monster::States state) {
    m_currentState = state;
    if (state != States::StateAlive) {
        SetVelocity(math::Vector3(0, 0, 0));
    } 
	m_current = m_animations[state];
}

bool Monster::IsAlive() const
{
    return m_currentState == States::StateAlive;
}

bool Monster::IsDead() const {
    return m_currentState == States::StateDead;
}

bool Monster::IsDieing() const {
    return m_currentState == States::StateDieing;
}

void Monster::Init()
{
	Render::Animation* idle = Core::resourceManager.Get<Render::Animation>("Bianfu1Idle")->Clone();
	idle->setCurrentFrame(math::random(idle->getFirstPlayedFrame(), idle->getLastPlayedFrame()));
    m_animations[StateAlive] = idle;
    m_animations[StateDieing] = Core::resourceManager.Get<Render::Animation>("Bianfu1Die")->Clone();
    m_animations[StateDead] = boost::intrusive_ptr<Render::Animation>();

	//m_explosion->posX = 100;
	//m_explosion->posY = 100;
}

math::Vector3 Monster::Wander()
{
	math::Vector3 circleCenter = m_velocity;
	circleCenter.Normalize();
	circleCenter *= m_wanderDistance;

	math::Vector3 displacement(0, 1, 0);
	displacement *= m_wanderRadius;

	//SetAngle(displacement, m_wanderAngle);
	float len = displacement.Length();
	displacement.x = math::cos(m_wanderAngle) * len;
	displacement.y = math::sin(m_wanderAngle) * len;

	m_wanderAngle += math::random(-m_wanderRange, m_wanderRange);

	math::Vector3 wanderForce = circleCenter + displacement;
	return wanderForce;
}
