#ifndef __TESTAPPDELEGATE_H__
#define __TESTAPPDELEGATE_H__

#pragma once

class TestAppDelegate : public Core::EngineAppDelegate {
public:
	enum {
		WINDOW_WIDTH = 768,
		WINDOW_HEIGHT = 1024
	};

	TestAppDelegate();

	virtual void GameContentSize(int deviceWidth, int deviceHeight, int &width, int &height) override;
	virtual void ScreenMode(DeviceMode &mode) override;

	virtual void RegisterTypes() override;
	virtual void LoadResources() override;

	virtual void OnPostDraw() override;
};

#endif // __TESTAPPDELEGATE_H__
