#pragma once

#ifndef CS_3505_EDUCATION_TOOL_LESSONS_HPP
#define CS_3505_EDUCATION_TOOL_LESSONS_HPP

#include <vector>
#include "lesson.hpp"

namespace Lessons {
    // Whole Numbers
    static const Lesson LESSON_01{1, // Lesson ID
          { // Sections

          {"Section One: Unsigned Integers"},
          {"Section Two: Convert Decimals To Binary", "Instructions..."}

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
