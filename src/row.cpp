#include "row.h"

#include <iostream>

namespace gctable {
Cell &Row::operator[](size_t index) {

    if (index >= cells_.size()) {
        cells_.resize(index + 1);
    }

    return cells_[index];
}

void Row::print() const {
    for (const auto &i : cells_) {
        //TODO: temporarily, this eventually will be replaced with proper printing and 
        //  provider either to stream or file
        std::cout << i.content << " ";
    }
}

} // namespace gctable
