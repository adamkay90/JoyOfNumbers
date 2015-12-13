#pragma once

#ifndef DATA_QUIZ_HPP
#define DATA_QUIZ_HPP

#include <cstdint>
#include <string>
#include <vector>

class Quiz {
public:
    inline Quiz(const uint64_t id, const std::vector<std::vector<std::string>> questions_and_answers, const std::vector<std::vector<std::string>> solutions)
            : id_(id), questions_and_answers_{questions_and_answers}, solutions_{solutions} {}

    uint64_t get_id() const ;
    std::vector<std::vector<std::string>>::size_type number_of_questions() const ;
    const std::string &get_question(const std::vector<std::vector<std::string>>::size_type question_id) const ;
    bool answer_question(const std::vector<std::vector<std::string>>::size_type question_id, const std::string &answer) const ;
    const std::vector<std::string> &get_solution(const std::vector<std::vector<std::string>>::size_type question_id) const ;
private:
    const uint64_t id_;
    const std::vector<std::vector<std::string>> questions_and_answers_;
    const std::vector<std::vector<std::string>> solutions_;
};

#endif //DATA_QUIZ_HPP
