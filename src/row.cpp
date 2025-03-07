#include "row.h"

#include <stdexcept>

namespace omni {

Row::Row(std::initializer_list<Cell> r) { cells_.insert(cells_.end(), r.begin(), r.end()); }

Cell &Row::operator[](std::size_t index) {

    if (index >= cells_.size()) {
        cells_.resize(index + 1);
    }

    return cells_[index];
}

void Row::merge_and_center(std::size_t start_pos, std::size_t end_pos) {
	if (start_pos > end_pos || end_pos >= cells_.size()) {
		throw std::runtime_error("Merge and center invalid range.");
	}

	(void)start_pos; (void)end_pos;

	// Remove the content from every cell, except the first one 
	// In merge and center, the consecutive columns are merged to the first one
	// And only the content from the first one is preserved.
	// cells_.erase(cells_.begin() + static_cast<int>(start_pos), cells_.begin() + static_cast<int>(end_pos) + 1);
	for (std::size_t i = start_pos; i < end_pos; ++i) {
		cells_[i] = Cell();
	}
}

} // namespace omni 
