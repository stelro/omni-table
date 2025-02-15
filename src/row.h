#pragma once

#include <vector>
#include <initializer_list>

#include "cell.h"
#include "formatter.h"

namespace gctable {

class Row {
public:

	Row() = default;
	Row(std::initializer_list<Cell> cells);

	// Automatically resizes if index is out of range.
    Cell &operator[](std::size_t index);

    const auto& get_cells() const { return cells_; };
	std::vector<Cell>& get_cells() { return cells_; }
	
	void set_row_style(format::style style) {
		style_formatter_.add_style(style);
	}

	const auto& get_formatter() const { return style_formatter_; } 
	
private:
    std::vector<Cell> cells_;
	format::Formatter style_formatter_;
};

} // namespace gctable

