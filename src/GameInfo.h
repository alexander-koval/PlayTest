#pragma once

#include <map>

class GameInfo
{
public:
	static GameInfo& instance();

	GameInfo();

	bool nextLevel();

	void setCurrentLevel(int value);

	size_t getCurrentLevel() const;
	
	size_t getNumMonsters() const;

	size_t getNumCatchers() const;

	size_t getNumMonstersToCatch() const;

	size_t numLevels() const;

private:
	struct LevelInfo {
		size_t numCatchers;
		size_t numMonstersToCatch;
		size_t numMonsters;
	};

	size_t m_currentLevel;
	std::map<size_t, LevelInfo> m_levels;
};

