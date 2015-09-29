#include "stdafx.h"
#include "MenuView.h"


MenuView::MenuView(const std::string& name, rapidxml::xml_node<>* elem) 
	: GUI::Widget(name, elem) {
	IRect size = Core::appInstance->GetMainWindow()->GetClientSizes();
	width = size.width;
	height = size.height;
}

void MenuView::Draw() {
	Render::BindFont("Sansation");
	Render::PrintString(width / 2, height / 2, "Test game application for Playrix\nPress MOUSE BUTTON to continue", 
		1.f, CenterAlign, BaseLineAlign);
}

bool MenuView::MouseDown(const IPoint& mouse_pos) {
	Core::mainScreen.SetFadeTime(1.f);
	Core::mainScreen.fadeToLayer("GameLayer", "Screen:RemoveLayer(\"MenuLayer\")", Core::ScreenImpl::FADE_ALPHA);
	return false;
}