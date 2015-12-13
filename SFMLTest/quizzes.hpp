#pragma once

#ifndef DATA_QUIZZES_HPP
#define DATA_QUIZZES_HPP

#include <vector>
#include "quiz.hpp"

namespace Quizzes {
    static const Quiz QUIZ_01{1, // Quiz ID
            { // Questions
            // Question, <Answers>...
            {"Question One: Answer is the number '1' in English or numeric format.", "001", "01", "1", "One", "one"},
            {"Question Two: Answer is the number '2' in English or numeric format.", "002", "02", "2", "Two", "two"}

            }, { // Solutions

            {"Just type either \"001\", \"01\", \"1\", \"One\", or \"one\" (without the quotation marks)."},
            {"Just type either \"002\", \"02\", \"2\", \"Two\", or \"two\" (without the quotation marks)."}}
    };
    static const Quiz QUIZ_02{2, // Quiz ID
           { // Questions

           {"Question One: Answer is the number '1' in English or numeric format.", "001", "01", "1", "One", "one"},
           {"Question Two: Answer is the number '2' in English or numeric format.", "002", "02", "2", "Two", "two"}

           }, { // Solutions

           {"Just type either \"001\", \"01\", \"1\", \"One\", or \"one\" (without the quotation marks)."},
           {"Just type either \"002\", \"02\", \"2\", \"Two\", or \"two\" (without the quotation marks)."}}
    };
    static const Quiz QUIZ_03{3, // Quiz ID
          { // Questions

          {"Question One: Answer is the number '1' in English or numeric format.", "001", "01", "1", "One", "one"},
          {"Question Two: Answer is the number '2' in English or numeric format.", "002", "02", "2", "Two", "two"}

          }, { // Solutions

          {"Just type either \"001\", \"01\", \"1\", \"One\", or \"one\" (without the quotation marks)."},
          {"Just type either \"002\", \"02\", \"2\", \"Two\", or \"two\" (without the quotation marks)."}}
    };
    static const Quiz QUIZ_04{4, // Quiz ID
          { // Questions

          {"Question One: Answer is the number '1' in English or numeric format.", "001", "01", "1", "One", "one"},
          {"Question Two: Answer is the number '2' in English or numeric format.", "002", "02", "2", "Two", "two"}

          }, { // Solutions

          {"Just type either \"001\", \"01\", \"1\", \"One\", or \"one\" (without the quotation marks)."},
          {"Just type either \"002\", \"02\", \"2\", \"Two\", or \"two\" (without the quotation marks)."}}
    };
    static const Quiz QUIZ_05{5, // Quiz ID
          { // Questions

          {"Question One: Answer is the number '1' in English or numeric format.", "001", "01", "1", "One", "one"},
          {"Question Two: Answer is the number '2' in English or numeric format.", "002", "02", "2", "Two", "two"}

          }, { // Solutions

          {"Just type either \"001\", \"01\", \"1\", \"One\", or \"one\" (without the quotation marks)."},
          {"Just type either \"002\", \"02\", \"2\", \"Two\", or \"two\" (without the quotation marks)."}}
    };

    static const std::vector<Quiz> ALL_QUIZZES{QUIZ_01, QUIZ_02, QUIZ_03, QUIZ_04, QUIZ_05};
}

#endif //DATA_QUIZZES_HPP
