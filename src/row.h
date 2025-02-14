#pragma once

#include "cell.h"

#include <vector>

namespace gctable {

class Row {
public:
	// Automatically resizes if index is out of range.
    Cell &operator[](std::size_t index);

    const std::vector<Cell>& get_cells() const { return cells_; };
	std::vector<Cell>& get_cells() { return cells_; }
private:
    std::vector<Cell> cells_;
};

} // namespace gctable

