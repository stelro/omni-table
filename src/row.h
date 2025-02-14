#ifndef GC_TABLE_ROW_H_
#define GC_TABLE_ROW_H_

#include "cell.h"

#include <vector>

namespace gctable {

class Row {
public:
	// Automatically resizes if index is out of range.
    Cell &operator[](size_t index);
    

    const std::vector<Cell>& get_cells() const { return cells_; };
	std::vector<Cell>& get_cells() { return cells_; }

	// TODO: (Optional) A simple print function; printing is now mainly handled by Table.
	void print() const;
private:
    std::vector<Cell> cells_;
};

} // namespace gctable

#endif // GC_TABLE_ROW_H_
