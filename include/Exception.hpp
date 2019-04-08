#pragma once

#include <string>
#include <stdexcept>

class size_mismatch : public std::logic_error {
public:
    explicit size_mismatch(const std::string& what_arg) : std::logic_error(what_arg) {};

    explicit size_mismatch(const char* what_arg) : std::logic_error(what_arg) {};
};

class does_not_converge : public std::runtime_error {
public:
    explicit does_not_converge(const std::string& what_arg) : std::runtime_error(what_arg) {};

    explicit does_not_converge(const char* what_arg) : std::runtime_error(what_arg) {};
};