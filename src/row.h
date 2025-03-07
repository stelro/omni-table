#pragma once

#include <initializer_list>
#include <vector>

#include "cell.h"
#include "formatter.h"

namespace omni {

class Row {
public:
    Row() = default;
    Row(std::initializer_list<Cell> cells);

    // Automatically resizes if index is out of range.
    Cell &operator[](std::size_t index);

    const auto &get_cells() const { return cells_; };
    std::vector<Cell> &get_cells() { return cells_; }

    void set_row_style(format::style style) { style_formatter_.add_style(style); }

    void merge_and_center(std::size_t start_pos, std::size_t end_pos);
    // todo: merge_and_center
    // todo: merge_across (merge the whole row)
    // todo: merge_selected (merge the selected cells into one row)
    // todo: unmerge (unmerge / re-border)
    // void merge(std::size_t start_pos, std::size_t end_pos);

    const auto &get_formatter() const { return style_formatter_; }

private:
    std::vector<Cell> cells_;
    format::Formatter style_formatter_;
};

} // namespace omni 
