#pragma once

#include "formatter.h"

#include <string>

namespace omni {

class Cell {
public:
	
	// Just a simple struct to hold all the formating styles/preferences for this particular cell
	struct CellFormat {
		format::Formatter style_formatter;
		bool style_formatter_set {false};
		bool skip_border {false};
	};

    Cell() = default;
    Cell(const std::string &c) : content_(c) {}
    Cell(std::string_view c) : content_(c) {}
    Cell(const char *c) : content_(c) {}
    Cell(int c) : content_(std::to_string(c)) {}
    Cell(float c) : content_(std::to_string(c)) {}
    Cell(double c) : content_(std::to_string(c)) {}

	void set_cell_style(format::style style) {
		cell_format_.style_formatter_set = true;
    	cell_format_.style_formatter.add_style(style);
    }

	void set_skip_border(bool flag) { cell_format_.skip_border = flag; }
	bool skip_border() const { return cell_format_.skip_border; }

	const std::string& get_content() const { return content_; }
	bool is_formatter_set() const { return cell_format_.style_formatter_set; } 
	format::Formatter get_formatter() const { return cell_format_.style_formatter; }

	const CellFormat& get_cell_format() const { return cell_format_; }

private:
    std::string content_;
    CellFormat cell_format_;
};

} // namespace omni 
