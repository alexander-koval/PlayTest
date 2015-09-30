#ifndef __GAMEAPPDELEGATE_H__
#define __GAMEAPPDELEGATE_H__

#pragma once

class GameAppDelegate : public Core::EngineAppDelegate {
public:
	GameAppDelegate();

	virtual void GameContentSize(int deviceWidth, int deviceHeight, int &width, int &height) override;
	virtual void ScreenMode(DeviceMode &mode) override;

	virtual void RegisterTypes() override;
	virtual void LoadResources() override;

	virtual void OnPostDraw() override;
};

#endif // __GAMEAPPDELEGATE_H__
