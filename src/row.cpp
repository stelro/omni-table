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

} // namespace gctable
