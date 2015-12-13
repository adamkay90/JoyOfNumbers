#include "lesson_data.h"

void LessonData::nextDialog() {
	dialogID++;
	text.setString(dialog.at(dialogID));
}

void LessonData::previousDialog() {
	if (dialogID > 0) {
		dialogID--;
		text.setString(dialog.at(dialogID));
	}
}

std::string LessonData::getDialog() {
	return dialog.at(dialogID);
}

std::string LessonData::getDialog(int id) {
	return dialog.at(id);
}

unsigned int LessonData::getDialogCount() {
	return dialog.size();
}