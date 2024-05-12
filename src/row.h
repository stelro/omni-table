#ifndef GC_TABLE_ROW_H_
#define GC_TABLE_ROW_H_

#include "cell.h"

#include <vector>

namespace gctable {

struct Row {
public:
    Cell &operator[](size_t index);
    void print() const;

    std::vector<Cell> get_cells() const;

public:
    std::vector<Cell> cells;
};

} // namespace gctable

#endif // GC_TABLE_ROW_H_