#pragma once

#include "TGUI\TGUI.hpp"
#include "lesson_data.h"


class LessonNaturalNumbers : public LessonData
{
private:
	sf::Text text;
	std::vector<std::vector<std::string>> dialog;

public:

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	LessonNaturalNumbers(sf::Text text);
	~LessonNaturalNumbers();

	virtual void getDialog();
	virtual void getDialogCount();

};