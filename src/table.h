#ifndef GC_TABLE_TABLE_H_
#define GC_TABLE_TABLE_H_

#include "row.h"

#include <string>
#include <vector>
#include <cstdint>

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

enum class BorderStyle : std::uint8_t {
    none	= 1 << 0,
    full	= 1 << 1,
    header	= 1 << 2,
    footer	= 1 << 3,
};

inline BorderStyle operator|(BorderStyle lhs, BorderStyle rhs) {
    return static_cast<BorderStyle>(static_cast<std::underlying_type_t<BorderStyle>>(lhs) |
                                    static_cast<std::underlying_type_t<BorderStyle>>(rhs));
}

inline BorderStyle operator&(BorderStyle lhs, BorderStyle rhs) {
    return static_cast<BorderStyle>(static_cast<std::underlying_type_t<BorderStyle>>(lhs) &
                                    static_cast<std::underlying_type_t<BorderStyle>>(rhs));
}

class Table {
public:
    Row &operator[](size_t index);
    const Row &operator[](size_t index) const;
	
	// Print the actuall table
    void print();
	
	// Set default alignment for cell content
    void set_alignment(Alignment alignment) noexcept { table_default_alignment_ = alignment; }
	// Set border style 
    void set_border_style(BorderStyle border_style) noexcept { table_border_style_ = border_style; }
	// Set a fixed maximum width for columns. Zero means "no limit" (columns use the widest cell)
	void set_max_column_width(size_t width) noexcept { max_column_width_ = width; }
	// Set custom border characters
    void set_border_chars(const std::string &vertical,
                          const std::string &horizontal,
                          const std::string &intersection) {
        border_vertical_ = vertical;
        border_horizontal_ = horizontal;
        border_intersection_ = intersection;
    }

    // Enable ANSI color for borders (supply prefix and suffix strings)
    void enable_border_color(const std::string &prefix, const std::string &suffix) {
        use_color_border_ = true;
        border_color_prefix_ = prefix;
        border_color_suffix_ = suffix;
    }

private:
    struct Context {
        size_t number_of_rows {0};
        size_t number_of_all_columns {0};

		// Effective width for each column after wrapping
		std::vector<size_t> column_widths;
    };

    Context compute_context_();

	// Prints a horizontal divider line using the custom border characters
    void print_horizontal_line_(const Context& ctx, bool include_new_line = true) const;

	// Adjust left/right spacing according to alignment
    void adjust_spacing_for_alignment_(size_t total_padding, size_t &left_spacing, size_t &right_spacing);

	// Default spacing inside each cell
    size_t default_left_spacing_ {1};
    size_t default_right_spacing_ {1};

	std::vector<Row> rows_;

	Alignment table_default_alignment_ {Alignment::center};
	BorderStyle table_border_style_ {BorderStyle::full};

    // Maximum column width. If nonzero, cells wider than this will be wrapped
	size_t max_column_width_ {0};

	// Custom border characters
	std::string border_vertical_ {"|"};
	std::string border_horizontal_ {"-"};
	std::string border_intersection_ {"+"};

    // ANSI color for borders
	bool use_color_border_ {false};
	std::string border_color_prefix_ {""};
	std::string border_color_suffix_ {""};
    
};

} // namespace cctable

#endif // GC_TABLE_TABLE_H_

