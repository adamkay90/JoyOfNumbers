#pragma once

#include <vector>
#include <TGUI\TGUI.hpp>

class LessonData {

public:

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	std::string getDialog(int id);
	int getDialogCount();
};

