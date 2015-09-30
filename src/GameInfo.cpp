#include "stdafx.h"
#include "GameInfo.h"


GameInfo& GameInfo::instance() {
	static GameInfo* instance = new GameInfo();
	return *instance;
}

GameInfo::GameInfo() 
	: m_currentLevel(1)
	, m_levels() {
	m_levels[1] = { 5, 10, 20 };
	m_levels[2] = { 5, 14, 20 };
	m_levels[3] = { 5, 13, 20 };
	m_levels[4] = { 4, 13, 20 };
	m_levels[5] = { 4, 15, 20 };
	m_levels[6] = { 4, 18, 30 };
	m_levels[7] = { 3, 22, 30 };
	m_levels[8] = { 3, 24, 30 };
	m_levels[9] = { 2, 24, 30 };
	m_levels[10] = { 2, 26, 30 };
}

bool GameInfo::nextLevel() {
	if (m_currentLevel < m_levels.size()) {
		return ++m_currentLevel;
	} 
	return false;
}

void GameInfo::setCurrentLevel(int value) {
	m_currentLevel = value;
}

size_t GameInfo::getCurrentLevel() const {
	return m_currentLevel;
}

size_t GameInfo::getNumMonsters() const {
	const LevelInfo& level = m_levels.at(m_currentLevel);
	return level.numMonsters;
}

size_t GameInfo::getNumCatchers() const {
	const LevelInfo& level = m_levels.at(m_currentLevel);
	return level.numCatchers;
}

size_t GameInfo::getNumMonstersToCatch() const {
	const LevelInfo& level = m_levels.at(m_currentLevel);
	return level.numMonstersToCatch;
}

size_t GameInfo::numLevels() const
{
	return m_levels.size();
}