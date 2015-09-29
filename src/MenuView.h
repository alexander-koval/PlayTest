#pragma once
#include "GUI/Widget.h"

class MenuView : public GUI::Widget {
public:
	MenuView(const std::string& name, rapidxml::xml_node<>* elem);

	virtual void Draw() override;

	virtual bool MouseDown(const IPoint& mouse_pos) override;
};

