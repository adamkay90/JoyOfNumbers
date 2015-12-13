#pragma once

#ifndef DATA_LESSON_HPP
#define DATA_LESSON_HPP

#include <cstdint>
#include <string>
#include <vector>

class Lesson {
public:
    inline Lesson(const uint64_t id, const std::vector<std::vector<std::string>> sections) : id_(id), sections_(sections) {}

    uint64_t get_id() const ;
    std::vector<std::vector<std::string>>::size_type number_of_sections() const ;
    const std::vector<std::string> &get_section(const std::vector<std::vector<std::string>>::size_type section_id) const ;
private:
    uint64_t id_;
    const std::vector<std::vector<std::string>> sections_;
};

#endif //DATA_LESSON_HPP
