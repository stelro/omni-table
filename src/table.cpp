#include "table.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>

namespace gctable {

Row &Table::operator[](size_t index) {
    if (index >= rows_.size()) {
        rows_.resize(index + 1);
    }
    return rows_[index];
}

void Table::print_horizontal_border_line_(size_t length, bool include_new_line) const {

    if (length < 1) return ;

    std::putc('+', stdout);
    for (size_t i = 1; i < length - 1; i++) {
        std::putc(horizontal_spacing, stdout);
    }
    std::putc('+', stdout);

    if (include_new_line) {
        std::cout << '\n';
    }
}

void Table::print_horizontal_line_with_divider_(char divider, bool include_new_line) const {

    std::putc(divider, stdout);
    auto pad = default_left_spacing_ + default_right_spacing_;
    for (const auto& col_length : columns_sizes_) {
        for (size_t i = 0; i < (col_length + pad); i++) {
            std::putc(horizontal_spacing, stdout);
            if ((i + 1) == (col_length + pad)) {
                std::putc(divider, stdout);
            }
        }
    }

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
        std::accumulate(columns_sizes_.begin(), columns_sizes_.end(), 0uz, [&](size_t a, size_t b) {
            // Add one extra byte for the vertical border line
            // Add left and right spacing in each cell
            return (a + b) + 1uz + default_left_spacing_ + default_right_spacing_;
        });

    std::cout << "ctx.longest_row: " << ctx.longest_row << '\n';

    return ctx;
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
    
    print_horizontal_line_with_divider_();

    std::vector<std::vector<size_t>> vecs;

    for (size_t row = 0; row < ctx.nr_of_rows; ++row) {

        auto cells = rows_[row].get_cells();

        std::vector<size_t> format_cross_position (ctx.nr_of_all_columns);

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
                format_cross_position[cell] = context_size + left_spacing + right_spacing;
            } else {
                std::cout << std::string(columns_sizes_[cell] + left_spacing + right_spacing, ' ');
                format_cross_position[cell] = columns_sizes_[cell] + left_spacing + right_spacing;

            }

            std::cout << vertical_spacing;

        } // for cells

        std::cout << "\n";
        print_horizontal_line_with_divider_();
    } // for rows
}

} // namespace cctable
