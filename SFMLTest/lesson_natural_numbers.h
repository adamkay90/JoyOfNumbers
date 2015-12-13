#pragma once

#include "TGUI\TGUI.hpp"
#include "lesson_data.h"


class LessonNaturalNumbers : public LessonData
{
private:

public:

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	LessonNaturalNumbers(sf::Text text);
	~LessonNaturalNumbers();
};