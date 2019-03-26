#pragma once

#include <string>
#include <stdexcept>

class size_mismatch : public std::logic_error {
public:
    explicit size_mismatch(const std::string& what_arg) : std::logic_error(what_arg) {};

    explicit size_mismatch(const char* what_arg) : std::logic_error(what_arg) {};
};