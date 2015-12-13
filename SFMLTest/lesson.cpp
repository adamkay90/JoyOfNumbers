#include "lesson.hpp"

uint64_t Lesson::get_id() const  {
    return id_;
}

std::vector<std::vector<std::string>>::size_type Lesson::number_of_sections() const  {
    return sections_.size();
}

const std::vector<std::string> &Lesson::get_section(const std::vector<std::vector<std::string>>::size_type section_id) const  {
    static const std::vector<std::string> NULL_SECTION{"ERROR: Invalid section_id passed to get_section call!"};
    return (section_id >= sections_.size())? NULL_SECTION : sections_[section_id];
}
