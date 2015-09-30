#pragma once

#include <map>

class GameInfo
{
public:
	GameInfo();

	GameInfo(const std::map<std::string, float>& configMap);

	bool nextLevel();

	void setCurrentLevel(int value);

	size_t getCurrentLevel() const;
	
	size_t getNumMonsters() const;

	size_t getNumCatchers() const;

	size_t getNumMonstersToCatch() const;

	size_t numLevels() const;

	float getCatcherBornTime() const;

	float getCatcherLifetime() const;

	float getCatcherHidetime() const;

	bool isDevelopMode() const;

private:
	void InitLevels();

	struct LevelInfo {
		size_t numCatchers;
		size_t numMonstersToCatch;
		size_t numMonsters;
	};

	bool m_isDevelopMode;
	size_t m_currentLevel;
	float m_catcherBornTime;
	float m_catcherLifetime;
	float m_catcherHidetime;
	std::map<size_t, LevelInfo> m_levels;
};

