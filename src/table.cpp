#include "table.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>

namespace cctable {

Cell &Row::operator[](size_t index) {

    if (index >= cells.size()) {
        cells.resize(index + 1);
    }
    return cells[index];
}

std::vector<Cell> Row::get_cells() const { return cells; }

void Row::print() const {
    for (const auto &i : cells) {
        std::cout << i.content << " ";
    }
}

Row &Table::operator[](size_t index) {
    if (index >= rows_.size()) {
        rows_.resize(index + 1);
    }
    return rows_[index];
}

void Table::print_horizontal_border_line(size_t length, bool include_new_line) const {
    std::cout << std::string(length, horizontal_spacing);
    if (include_new_line) {
        std::cout << '\n';
    }
}

Table::Context Table::prepare_for_printing_() {

    Context ctx;

    for (const auto &row : rows_) {
        std::vector<Cell> cells = row.get_cells();
        for (size_t cell = 0; cell < cells.size(); ++cell) {
            // Save the maximum length of the Cell in that column,
            // for example:
            //  0: | cell 1 |
            //  1: | cell 2 |
            //  2: | cell 3 long |
            //  3: | cell |
            //
            // In the column above, we have 4 rows, and the longest cell in length is
            // cell number 2 (2nd row).
            //
            if (cell >= columns_sizes_.size()) {
                columns_sizes_.resize(cell + 1);
            }
            columns_sizes_[cell] = std::max(columns_sizes_[cell], cells[cell].content.size());
        }

        ctx.nr_of_rows++;
        ctx.nr_of_all_columns = std::max(ctx.nr_of_all_columns, cells.size());
    }

    ctx.longest_row =
        std::accumulate(columns_sizes_.begin(), columns_sizes_.end(), 0, [&](size_t a, size_t b) {
            // Add one extra byte for the vertical border line
            // Add left and right spacing in each cell
            return (a + b) + 1 + default_left_spacing_ + default_right_spacing_;
        });

    std::cout << "ctx.longest_row: " << ctx.longest_row << '\n';

    return std::move(ctx);
}

void Table::adjust_spacing_for_alignment_(size_t total_padding, size_t &left_spacing,
                                          size_t &right_spacing) {
    switch (table_default_alignment_) {
    case Alignment::right:
        left_spacing += total_padding;
        break;
    case Alignment::left:
        right_spacing += total_padding;
        break;
    case Alignment::center:
        left_spacing += total_padding / 2;
        right_spacing += total_padding - total_padding / 2; // Adjust for odd padding
        break;
    default:
        break;
    }
}

void Table::print() {

    const Context ctx = prepare_for_printing_();

    // Add one extra byte for the border line at the begining of the row
    size_t border_length = ctx.longest_row + 1;

    std::cout << "nr_of_rows: " << ctx.nr_of_rows << std::endl;
    std::cout << "nr_of_cells: " << ctx.nr_of_all_columns << std::endl;

    if (table_border_style_ & BorderStyle::full_border)
        print_horizontal_border_line(border_length);

    for (size_t row = 0; row < ctx.nr_of_rows; ++row) {

        auto cells = rows_[row].get_cells();

        std::cout << vertical_spacing;
        for (size_t cell = 0; cell < ctx.nr_of_all_columns; ++cell) {

            size_t left_spacing = default_left_spacing_;
            size_t right_spacing = default_right_spacing_;

            if (cell < cells.size()) {
                size_t context_size = cells[cell].content.size();
                size_t total_padding = columns_sizes_[cell] - context_size;

                adjust_spacing_for_alignment_(total_padding, left_spacing, right_spacing);

                std::cout << std::string(left_spacing, ' ') << cells[cell].content
                          << std::string(right_spacing, ' ');
            } else {
                std::cout << std::string(columns_sizes_[cell] + left_spacing + right_spacing, ' ');
            }

            std::cout << vertical_spacing;
        }

        std::cout << "\n";
        print_horizontal_border_line(border_length);
    }
}

} // namespace cctable
