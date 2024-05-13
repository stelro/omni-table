#ifndef GC_TABLE_TABLE_H_
#define GC_TABLE_TABLE_H_

#include "row.h"

#include <string>
#include <string_view>
#include <vector>

/*
 * table[0][0] = "cell 1"
 * table[0][1] = "cell 2"
 * table[0][2] = "cell 3"
 *
 * table[1][0] = "cell 4"
 * table[1][1] = "cell 5"
 * table[1][2] = "cell 6"
 *
 *	cell 1 | cell 2 | cell 3 |
 *	cell 4 | cell 5 | cell 6 |
 */

namespace gctable {

enum class Alignment { center, left, right };

enum class BorderStyle : uint8_t {
    none = 1 << 0,
    full_border = 1 << 1,
    header = 1 << 2,
    footer = 1 << 3,
};

inline BorderStyle operator|(BorderStyle lhs, BorderStyle rhs) {
    return static_cast<BorderStyle>(static_cast<std::underlying_type_t<BorderStyle>>(lhs) |
                                    static_cast<std::underlying_type_t<BorderStyle>>(rhs));
}

inline BorderStyle operator&(BorderStyle lhs, BorderStyle rhs) {
    return static_cast<BorderStyle>(static_cast<std::underlying_type_t<BorderStyle>>(lhs) &
                                    static_cast<std::underlying_type_t<BorderStyle>>(rhs));
}

static constexpr auto vertical_spacing = '|';
static constexpr auto horizontal_spacing = '-';


class Table {
public:
    Row &operator[](size_t index);

    void print();

    void set_alignment(Alignment alignment) noexcept { table_default_alignment_ = alignment; }
    void set_border_style(BorderStyle border_style) noexcept { table_border_style_ = border_style; }

private:
    struct Context {
        size_t longest_row{0};
        size_t nr_of_rows{0};
        size_t nr_of_all_columns{0};
    };

    Context prepare_for_printing_();

    void print_horizontal_border_line_(size_t length, bool include_new_line = true) const;
    void adjust_spacing_for_alignment_(size_t total_padding, size_t &left_spacing,
                                       size_t &right_spacing);

    size_t default_left_spacing_{1};
    size_t default_right_spacing_{1};

    std::vector<Row> rows_;
    std::vector<size_t> columns_sizes_;

    Alignment table_default_alignment_{Alignment::center};
    BorderStyle table_border_style_{BorderStyle::full_border};
};

} // namespace cctable

#endif // GC_TABLE_TABLE_H_

