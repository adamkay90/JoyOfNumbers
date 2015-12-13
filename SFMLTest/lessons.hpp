#pragma once

#ifndef CS_3505_EDUCATION_TOOL_LESSONS_HPP
#define CS_3505_EDUCATION_TOOL_LESSONS_HPP

#include <vector>
#include "lesson.hpp"

namespace Lessons {
    // Whole Numbers
    static const Lesson LESSON_01{1, // Lesson ID
          { // Sections
			  { "Lesson 1: Natural Numbers" },
			  { "Hi, and welcome to the Joy of Numbers. I’m your host, Bob Ross. \nI’m so glad you could join me today to learn about one of life’s most fascinating topics." },
			  { "Today, we’re going to talk about natural numbers. You probably\nknow a lot about natural numbers already, and you don’t even know it yet." },
			  { "Let’s get started, shall we?" },
			  { "Natural numbers are, to put it simply, numbers you can count on your fingers and toes. \nOne, two, three, those are all natural numbers." },
			  { "Of course, we can’t forget little old zero! That’s a natural number too." },
			  { "Every natural number is followed by another natural number. 1 is followed by 2, 100 is followed by 101. This goes on and on." },
			  { "Since zero is the smallest of the natural numbers, it doesn’t follow any other natural number. It’s at the front of the line." },
			  { "If we have two natural numbers, but we don’t know anything about them except that they are the followed by the same number, then we can conclude that they’re the same natural number." },
			  { "It sounds a bit more complicated then it actually is, haha." },
			  { "If we have any group of natural numbers together, then we also know that the group has a smallest natural number." },
			  { "For example, if we have a set with the numbers 5, 9, and 12 in it, then we know 5 is the smallest number." },
			  { "You might be thinking, /“Bob, if sets always have a smallest number, then surely they also have a largest number too!/”" },
			  { "But a set can have an infinite amount of natural numbers in it, and you can’t have a biggest number from an infinite amount of numbers." },
			  { "Now maybe you’re thinking, /“Shucks, Bob, you got me. But why do I need to know this stuff anyway?/” Well, that’s cause it’s an important rule of natural numbers." },
			  { "Mathematicians need all sorts of rules about numbers to be able to do stuff with them, even if they sound obvious to us." },
			  { "If we didn’t have those rules, we would have never been able to get to the moon and see the Earth in all its glory." },
			  { "Oh, but I’m rambling again. I hope you enjoyed learning about natural numbers, and I hope I see you again soon in the next lesson." }
          }
    };
    // Integers
    static const Lesson LESSON_02{2, // Lesson ID
          { // Sections

          {"Section One: Whole Numbers VS Integers", "Sign", "Comparisons..."},
          {"Section Two: Bias", "Explanation..."},
          {"Section Three: Two's Complement", "Explanation..."}

          }
    };
    // Rational and Real Numbers
    static const Lesson LESSON_03{3, // Lesson ID
          { // Sections

          {"Section One: Decimal Expansion", "Explanation..."},
          {"Section Two: Binary Expansion", "Explanation..."},
          {"Section Three: Floating Point", "Explanation..."}

          }
    };
    // Number Representation In Computers
    static const Lesson LESSON_04{4, // Lesson ID
          { // Sections

          {"Section One: Why We Use Binary / Base 2", "Explanation..."},
          {"Section Two: Data + Context", "Explanation..."},
          {"Section Three: Accuracy Issues", "Explanation..."}

          }
    };

    static const std::vector<Lesson> ALL_LESSONS{LESSON_01, LESSON_02, LESSON_03, LESSON_04};
}

#endif //CS_3505_EDUCATION_TOOL_LESSONS_HPP
