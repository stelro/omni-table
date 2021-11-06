#include <algorithm>
#include <array>
#include <cassert>
#include <cstdarg>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

/*
 * TODOs:
 *
 * - add offset spaces on each cell to be aligned with the longest string in a cell
 *   + Measure and save the longest line of the column
 *   - Add offset accordingly to each other column cell
 * - print spacing characters on each row
 * - print spacing characters on each column
 *
 */

#define NDEBUG

class Logger {
public:
    enum class LogLevel { trace = 0, debug, info, warning, error, critical, off };

    template <typename... Args>
    void error(Args &&...args) {
        print_internal_(LogLevel::error, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void warning(Args &&...args) {
        print_internal_(LogLevel::warning, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void debug(Args &&...args) {
        print_internal_(LogLevel::debug, std::forward<Args>(args)...);
    }

private:
    const char *get_loglevel_str_(LogLevel level) {
        switch(level) {
            case LogLevel::trace:
                return "trace";
            case LogLevel::debug:
                return "debug";
            case LogLevel::info:
                return "info";
            case LogLevel::warning:
                return "warning";
            case LogLevel::error:
                return "error";
            case LogLevel::critical:
                return "critical";
            case LogLevel::off:
                return "";
        }
    }

    void print_internal_(LogLevel level, const char *format, ...) {

#if defined(NDEBUG)
        if(level == LogLevel::debug)
            return;
#endif
        va_list args;
        va_start(args, format);
        // Fix this
        std::ostringstream oss;
        oss << "(" << get_loglevel_str_(level) << "): ";
        fprintf(stderr, "%s", oss.str().c_str());
        vfprintf(stderr, format, args);
        va_end(args);
    }
};

template <size_t ROWS, size_t COLUMNS>
class ctable {
public:
    template <typename... Columns>
    void add_row(Columns... columns) {
        static_assert(sizeof...(columns) <= COLUMNS,
                      "You have added more columns that it's allowd.");

        logger_.debug("call - add_row()\n");

        // std::forward?
        row_insertion_initial_size_ = sizeof...(columns);

        logger_.debug("row insertion initial size: %zu\n", row_insertion_initial_size_);

        const auto row_size = add_row_internal_(sizeof...(columns), columns...);
        length_of_the_longest_row_ = std::max(length_of_the_longest_row_, row_size);

        current_row_index_++;
    }

    void print() {
        logger_.debug("call - print()\n\n\n");

        if(data_.empty())
            return;
        const size_t n_extra_horizontal_symbs = ROWS + (1); // 1 for the last

        for(size_t row = 0; row < data_.size(); ++row) {

            print_n_horizontal_symobols_(length_of_the_longest_row_ + n_extra_horizontal_symbs);
            new_line_();

            print_n_vertical_symobols_(1);

            for(size_t col = 0; col < data_[row].size(); ++col) {

                const auto cell = data_[row][col];
                const auto longest_cell = longest_cell_in_column[col];

                if(cell.empty()) {
                    print_n_spaces_(longest_cell);
                    print_n_vertical_symobols_(1);
                    continue;
                }

                auto cell_size = cell.size();
                
                printf("%s", cell.c_str());
                print_n_spaces_((longest_cell - cell_size));
                print_n_vertical_symobols_(1);
            }

            new_line_();
        }

        print_n_horizontal_symobols_(length_of_the_longest_row_ + n_extra_horizontal_symbs);
    }

    void print_log_info() {
        logger_.debug("call - log_info()\n");
        for(size_t i = 0; i < longest_cell_in_column.size(); ++i) {
            logger_.debug("row: (%d) the size of the longset cell is: (%zu)\n", i,
                          longest_cell_in_column[i]);
        }
    }

private:
    Logger logger_;

    std::array<std::array<std::string, ROWS>, COLUMNS> data_;
    std::array<size_t, ROWS> longest_cell_in_column{};

    char vertical_split_symobl_ = '|';
    char horizontal_split_symobl_ = '-';

    // Keeps track of the row_insertion size, upon add_row call
    // It will reset every time on row_call invocation
    size_t row_insertion_initial_size_{0};

    // Keep track of the current row index, that will help in consecutive "add_row" calls
    size_t current_row_index_{0};

    size_t length_of_the_longest_row_{0};

    void print_space_() {
        printf(" ");
    }

    void print_n_spaces_(size_t n) {
        for(size_t i = 0; i < n; ++i) {
            print_space_();
        }
    }

    void new_line_() {
        printf("\n");
    }

    template <typename... Columns>
    size_t add_row_internal_([[maybe_unused]] size_t _,
                             const std::string &first_column,
                             Columns... columns) {

        const size_t index = sizeof...(columns);
        auto row_size = add_row_internal_(index, first_column);
        row_size += add_row_internal_(0, columns...);

        return row_size;
    }

    // TODO(rstemac): Better parameter naming, index it's not real index of the array
    // it's the index of the variadic args
    size_t add_row_internal_(size_t index, const std::string &cell) {

        const size_t offset = (row_insertion_initial_size_ != 1) ? 1 : 0;
        const size_t array_coll_index = row_insertion_initial_size_ - index - offset;

        longest_cell_in_column[array_coll_index] =
            std::max(longest_cell_in_column[array_coll_index], cell.size());

        data_[current_row_index_][array_coll_index] = cell;

        logger_.debug("cell (%s) has array column index: (%zu)\n", cell.c_str(), array_coll_index);

        // Returns the cell size + offest it needs to full fill the whole cell
        // We are returning this size here, instead of sum the longest_cell_in_col * columns,
        // because this size may be change if the cells are not having padding
        return (longest_cell_in_column[array_coll_index] - cell.size()) + cell.size();
    }

    void print_n_horizontal_symobols_(size_t n) {
        for(size_t i = 0; i < n; ++i) {
            printf("%c", horizontal_split_symobl_);
        }
    }

    void print_n_vertical_symobols_(size_t n) {
        for(size_t i = 0; i < n; ++i) {
            printf("%c", vertical_split_symobl_);
        }
    }
};

int main() {

    /* How we want to manage the ctable?
     *
     * ctable<4,4> table;
     *
     * table.add_row("column1", "column2", "column3", "column4");
     *
     * table.add_column("row1", "row2", "row3", "row4"); // this is debatable
     * table.add_cell_to_position<1,3>("column3"); // Adds "column3" to the first row, and 3d column
     *
     * table.print();
     *
     */

    ctable<4, 4> table;

    table.add_row("col", "onetwothree", "twelve", "sixs");    // 11 is the longest (1)
    table.add_row("column5", "column6666");                   // 10 is the longest (1)
    table.add_row("column7");                                 // 7 is the longest (0)
    table.add_row("six", "a", "b", "c");                      // 3 is the longest (0)

    table.print();

    std::cout << '\n';

    // table.print_log_info();


    return 0;
}
