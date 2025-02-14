#include "row.h"

namespace gctable {
Cell &Row::operator[](std::size_t index) {

    if (index >= cells_.size()) {
        cells_.resize(index + 1);
    }

    return cells_[index];
}

} // namespace gctable
