#pragma once

#include <vector>
#include <TGUI\TGUI.hpp>

class LessonData {

protected:
	std::vector<std::string> dialog;
	int dialogID;
	sf::Text text;

public:

	void draw(const float dt);
	void update(const float dt);
	void handleInput();

	void nextDialog();
	void previousDialog();

	std::string getDialog();
	std::string getDialog(int id);

	unsigned int getDialogCount();

};

