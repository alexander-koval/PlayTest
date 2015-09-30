#include "stdafx.h"
#include "GameInfo.h"

GameInfo::GameInfo()
	: m_isDevelopMode(false)
	, m_currentLevel(1)
	, m_catcherBornTime(.5f)
	, m_catcherLifetime(1.f)
	, m_catcherHidetime(.5f)
	, m_levels() {
	InitLevels();
}


GameInfo::GameInfo(const std::map<std::string, float>& configMap)
	: m_isDevelopMode(false)
	, m_currentLevel(1)
	, m_catcherBornTime(.5f)
	, m_catcherLifetime(1.f)
	, m_catcherHidetime(.5f)
	, m_levels() {
	using ConstIterator = std::map<std::string, float>::const_iterator;
	ConstIterator it = configMap.begin();
	it = configMap.find("CountPoints");
	if (it != configMap.end()) {
		size_t count = it->second;
		m_levels[1] = {count, count, count};
		m_isDevelopMode = true;
	} else {
		InitLevels();
	}
	it = configMap.find("BornTime");
	if (it != configMap.end()) {
		float count = it->second;
		m_catcherBornTime = count;
		m_isDevelopMode = true;
	}
	it = configMap.find("LifeTime");
	if (it != configMap.end()) {
		float count = it->second;
		m_catcherLifetime = count;
		m_isDevelopMode = true;
	}
	it = configMap.find("HideTime");
	if (it != configMap.end()) {
		float count = it->second;
		m_catcherHidetime = count;		
		m_isDevelopMode = true;
	}
}

void GameInfo::InitLevels() {
	m_levels[1] = { 5, 10, 20 };
	m_levels[2] = {5, 14, 20};
	m_levels[3] = {5, 13, 20};
	m_levels[4] = {4, 13, 20};
	m_levels[5] = {4, 15, 20};
	m_levels[6] = {4, 18, 30};
	m_levels[7] = {3, 22, 30};
	m_levels[8] = {3, 24, 30};
	m_levels[9] = {2, 24, 30};
	m_levels[10] = {2, 25, 30};
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

size_t GameInfo::numLevels() const {
	return m_levels.size();
}

float GameInfo::getCatcherBornTime() const {
	return m_catcherBornTime;
}

float GameInfo::getCatcherLifetime() const {
	return m_catcherLifetime;
}

float GameInfo::getCatcherHidetime() const {
	return m_catcherHidetime;
}

bool GameInfo::isDevelopMode() const {
	return m_isDevelopMode;
}