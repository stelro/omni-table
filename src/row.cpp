#include "row.h"

#include <iostream>

namespace gctable {
Cell &Row::operator[](size_t index) {

    if (index >= cells.size()) {
        cells.resize(index + 1);
    }
    return cells[index];
}

std::vector<Cell> Row::get_cells() const { return cells; }

void Row::print() const {
    for (const auto &i : cells) {
        //TODO: temporarily, this eventually will be replaced with proper printing and 
        //  provider either to stream or file
        std::cout << i.content << " ";
    }
}

} // namespace gctable