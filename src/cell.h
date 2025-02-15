#pragma once

#include "formatter.h"

#include <string>

namespace gctable {

class Cell {
public:
    Cell() = default;
    Cell(const std::string &c) : content_(c) {}
    Cell(std::string_view c) : content_(c) {}
    Cell(const char *c) : content_(c) {}
    Cell(int c) : content_(std::to_string(c)) {}
    Cell(float c) : content_(std::to_string(c)) {}
    Cell(double c) : content_(std::to_string(c)) {}

	void set_cell_style(format::style style) {
		style_formatter_set_ = true;
    	style_formatter_.add_style(style);
    }

	const std::string& get_content() const { return content_; }
	bool is_formatter_set() const { return style_formatter_set_; } 
	format::Formatter get_formatter() const { return style_formatter_; }

private:
    std::string content_;
    format::Formatter style_formatter_;
	bool style_formatter_set_ {false};
};

} // namespace gctable
