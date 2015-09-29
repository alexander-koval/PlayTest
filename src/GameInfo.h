#pragma once

#include <map>

class GameInfo
{
public:
	static GameInfo& instance();

	GameInfo();

	bool nextLevel();

	void setCurrentLevel(int value);

	int getCurrentLevel() const;
	
	int getNumMonsters() const;

	int getNumCatchers() const;

	int getNumMonstersToCatch() const;

	int numLevels() const;

private:
	struct LevelInfo {
		int numCatchers;
		int numMonstersToCatch;
		int numMonsters;
	};

	int m_currentLevel;
	std::map<int, LevelInfo> m_levels;
};

