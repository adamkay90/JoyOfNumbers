#include <algorithm>
#include "quiz.hpp"

uint64_t Quiz::get_id() const  {
    return id_;
}

std::vector<std::vector<std::string>>::size_type Quiz::number_of_questions() const {
    return questions_and_answers_.size();
}

const std::string &Quiz::get_question(const std::vector<std::vector<std::string>>::size_type question_id) const {
    static const std::string NULL_QUESTION{"ERROR: Invalid question_id passed to get_question call!"};
    return (question_id >= questions_and_answers_.size())? NULL_QUESTION : questions_and_answers_[question_id][0];
}

bool Quiz::answer_question(const std::vector<std::vector<std::string>>::size_type question_id, const std::string &answer) const {
    return question_id >= questions_and_answers_.size()? false :
           std::find(questions_and_answers_[question_id].cbegin(), questions_and_answers_[question_id].cend(), answer) != questions_and_answers_[question_id].cend();
}

const std::vector<std::string> &Quiz::get_solution(const std::vector<std::vector<std::string>>::size_type question_id) const  {
    static const std::vector<std::string> NULL_SOLUTION{"ERROR: Invalid question_id passed to get_solution call!"};
    return (question_id >= solutions_.size())? NULL_SOLUTION : solutions_[question_id];
}
