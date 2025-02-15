#pragma once

#include "formatter.h"

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

	void set_cell_style(format::style style) {
		style_formatter_set = true;
    	style_formatter_.add_style(style);
    }

    std::string content;

    format::Formatter style_formatter_;
	bool style_formatter_set {false};

	int num = 1;
};

} // namespace gctable
