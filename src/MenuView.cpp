#include "stdafx.h"
#include "MenuView.h"
#include "Game.h"

MenuView::MenuView(const std::string& name, rapidxml::xml_node<>* elem) 
	: GUI::Widget(name, elem) {
	IRect size = Core::appInstance->GetMainWindow()->GetClientSizes();
	width = size.width;
	height = size.height;
}

void MenuView::Draw() {
	Render::BindFont("Sansation");
	Render::PrintString(width * 0.5f, height * 0.5f, "Test game application\nPress MOUSE BUTTON to continue", 
		1.f, CenterAlign, BaseLineAlign);
	if (Game::instance().GetGameInfo().isDevelopMode()) {
		Render::PrintString(width * 0.5f, height * 0.4f, "This game is in TEST MODE.\nThe file \"input.txt\" is in use", 
			1.f, CenterAlign, BaseLineAlign);
	}

	Render::BindFont("arial");
	Render::PrintString(5, 5, "Animations and sounds taken from the game \"Starry Nuts\"", 1.f, LeftAlign, BaseLineAlign);

}

bool MenuView::MouseDown(const IPoint& mouse_pos) {
	Core::mainScreen.SetFadeTime(1.f);
	Core::mainScreen.fadeToLayer("GameLayer", "Screen:RemoveLayer(\"MenuLayer\")", Core::ScreenImpl::FADE_ALPHA);
	return false;
}