#pragma once

#include "GameInfo.h"
#include <memory>

class Game {
public:
	static Game& instance();

	void SetGameInfo(std::unique_ptr<GameInfo>& gameInfo) { m_gameInfo = std::move(gameInfo); }

	void SetGameInfo(std::unique_ptr<GameInfo>&& gameInfo) { m_gameInfo = std::move(gameInfo); }

	GameInfo& GetGameInfo() { return *m_gameInfo.get(); }

private:
	std::unique_ptr<GameInfo> m_gameInfo;
};

