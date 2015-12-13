#include "lesson_natural_numbers.h"

LessonNaturalNumbers::LessonNaturalNumbers(sf::Text text) {
	LessonNaturalNumbers::text = text;

	this->dialog.push_back("Hi, and welcome to the Joy of Numbers. I’m your host, Bob Ross. \nI’m so glad you could join me today to learn about one of life’s most fascinating topics.");
	this->dialog.push_back("Today, we’re going to talk about natural numbers. You probably\nknow a lot about natural numbers already, and you don’t even know it yet.");
	this->dialog.push_back("Let’s get started, shall we?");
	this->dialog.push_back("Natural numbers are, to put it simply, numbers you can count on your fingers and toes. \nOne, two, three, those are all natural numbers.");
	this->dialog.push_back("Of course, we can’t forget little old zero! That’s a natural number too.");
	this->dialog.push_back("Every natural number is followed by another natural number. 1 is followed by 2, 100 is followed by 101. This goes on and on.");
	this->dialog.push_back("Since zero is the smallest of the natural numbers, it doesn’t follow any other natural number. It’s at the front of the line.");
	this->dialog.push_back("If we have two natural numbers, but we don’t know anything about them except that they are the followed by the same number, then we can conclude that they’re the same natural number.");
	this->dialog.push_back("It sounds a bit more complicated then it actually is, haha.");
	this->dialog.push_back("If we have any group of natural numbers together, then we also know that the group has a smallest natural number.");
	this->dialog.push_back("For example, if we have a set with the numbers 5, 9, and 12 in it, then we know 5 is the smallest number.");
	this->dialog.push_back("You might be thinking, /“Bob, if sets always have a smallest number, then surely they also have a largest number too!/”");
	this->dialog.push_back("But a set can have an infinite amount of natural numbers in it, and you can’t have a biggest number from an infinite amount of numbers.");
	this->dialog.push_back("Now maybe you’re thinking, /“Shucks, Bob, you got me. But why do I need to know this stuff anyway?/” Well, that’s cause it’s an important rule of natural numbers.");
	this->dialog.push_back("Mathematicians need all sorts of rules about numbers to be able to do stuff with them, even if they sound obvious to us.");
	this->dialog.push_back("If we didn’t have those rules, we would have never been able to get to the moon and see the Earth in all its glory.");
	this->dialog.push_back("Oh, but I’m rambling again. I hope you enjoyed learning about natural numbers, and I hope I see you again soon in the next lesson.");
}

void LessonNaturalNumbers::draw(const float dt)
{
	
	return;
}

LessonNaturalNumbers::~LessonNaturalNumbers() {

}

void LessonNaturalNumbers::update(const float dt)
{

}

void LessonNaturalNumbers::handleInput()
{

	return;
}