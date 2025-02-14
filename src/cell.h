#pragma once

#include <string>

namespace gctable {

struct Cell {
    Cell() = default;
    Cell(const std::string &c) : content(c) {}
    Cell(std::string_view c) : content(c) {}
    Cell(const char *c) : content(c) {}
    Cell(int c) : content(std::to_string(c)) {}
    Cell(float c) : content(std::to_string(c)) {}
    Cell(double c) : content(std::to_string(c)) {}

    std::string content;
};

} // namespace gctable
