#include "table.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>

namespace detail {

// wrap a single segment (without newlines) into lines not exeeding max_width.
// If a word is longer than max_width, it is split.
std::vector<std::string> wrap_segment(const std::string& segment, size_t max_width) {

	std::vector<std::string> wrapped;
	std::istringstream iss(segment);
	std::string word;
	std::string line;

	while (iss >> word) {
		// if a single word is longer than max_width, split it
		while (word.size() > max_width) {

			if (!line.empty()) {
				wrapped.push_back(line);
				line.clear();
			}

			wrapped.push_back(word.substr(0, max_width));
			word = word.substr(max_width);
		}

		if (line.empty()) {
			line = word;
		}
		else if ((line.size() + 1 + word.size()) <= max_width) {
			line += " " + word;
		} 
		else {
			wrapped.push_back(line);
			line = word;
		}
	}

	if (!line.empty()) {
		wrapped.push_back(line);
	}

	return wrapped;
}

// Wrap text (which may contain new lines) into lines not exceeding max_width.
std::vector<std::string> wrap_text(const std::string& text, size_t max_width) {
	std::vector<std::string> lines; 
	std::size_t start = 0;

	while (start < text.size()) {
		std::size_t pos = text.find('\n', start);
		std::string segment = (pos == std::string::npos) ? text.substr(start) : text.substr(start, pos - start);
		auto seg_lines = wrap_segment(segment, max_width);
		// preserve empty lines
		if (seg_lines.empty()) {
			seg_lines.push_back("");
		}

		lines.insert(lines.end(), seg_lines.begin(), seg_lines.end());

		if (pos == std::string::npos) {
			break;
		}
		
		start = pos + 1;
	}

	return lines;
}

} // namespace detail

namespace gctable {

Row &Table::operator[](size_t index) {
    if (index >= rows_.size()) {
        rows_.resize(index + 1);
    }
    return rows_[index];
}

const Row &Table::operator[](size_t index) const {
	return rows_[index];
}

void Table::print_horizontal_line_(const Context& ctx, bool include_new_line) const {

	if (table_border_style_ == BorderStyle::none) return;

	if (use_color_border_) {
		std::cout << style_formatter_.get_style_prefix();
	}

	std::cout << border_intersection_;
    for (size_t width : ctx.column_widths) {
		size_t pad = width + default_left_spacing_ + default_right_spacing_;
		for (size_t i = 0; i < pad; ++i) {
			std::cout << border_horizontal_;
		}
		std::cout << border_intersection_;
	}

	if (use_color_border_) {
		std::cout << style_formatter_.get_style_suffix();
	}

	if (include_new_line) {
		std::cout << '\n';
	}
}

// Computes effective column widths by processing each cell's content through wrap_text_.
// If max_column_width_ is set greater than 0, each cell is wrapped to that limit.
Table::Context Table::compute_context_() {

    Context ctx;
	
	for (const auto& row : rows_) {
		
		const auto& cells = row.get_cells();
		ctx.number_of_rows++;
		ctx.number_of_all_columns = std::max(ctx.number_of_all_columns, cells.size());

		if (cells.size() > ctx.column_widths.size()) {
			ctx.column_widths.resize(cells.size(), 0);
		}

		for (std::size_t j = 0; j < cells.size(); ++j) {

			// determine the wrapping limit
			const std::size_t wrap_limit (max_column_width_ > 0 ? max_column_width_ : cells[j].content.size());
			// wrap the cell content
			auto wrapped = detail::wrap_text(cells[j].content, wrap_limit);
			// compute the maximum line length in this cell
			std::size_t effective_width = 0;
			for (const auto& line : wrapped) {
				effective_width = std::max(effective_width, line.size());
			}
			// if a maximum_column_width_ is set, enusre the effective width does not exceed it
			if (max_column_width_ > 0) {
				effective_width = std::min(effective_width, max_column_width_);
			}
			ctx.column_widths[j] = std::max(ctx.column_widths[j], effective_width);
		}
	}

    return ctx;
}

void Table::adjust_spacing_for_alignment_(size_t total_padding, size_t &cell_left_pad,
                                          size_t &cell_right_pad) {
    switch (table_default_alignment_) {
    case Alignment::right:
		cell_left_pad = 0;
		cell_right_pad = total_padding;
        break;
    case Alignment::left:
		cell_left_pad = total_padding;
		cell_right_pad = 0;
        break;
    case Alignment::center:
		cell_left_pad = total_padding / 2;
		cell_right_pad = total_padding - cell_left_pad;
        break;
    default:
		cell_left_pad = 0;
		cell_right_pad = total_padding;
        break;
    }
}

void Table::print() {

	Context ctx = compute_context_();

	// Print the top border
	if (table_border_style_ != BorderStyle::none) {
		print_horizontal_line_(ctx);
	}

	for (std::size_t row_index = 0; row_index < ctx.number_of_rows; ++row_index) {
		
		const auto& cells = rows_[row_index].get_cells();

		// format each row individually
		const auto row_formatter = rows_[row_index].get_formatter();

		// for each column in the row, get the wrapped lines
		std::vector<std::vector<std::string>> cell_lines(ctx.number_of_all_columns);
		std::size_t row_height = 0;
		for (std::size_t col = 0; col < ctx.number_of_all_columns; ++col) {
			if (col < cells.size()) {
				const std::size_t wrap_limit = ctx.column_widths[col];
				cell_lines[col] = detail::wrap_text(cells[col].content, wrap_limit);
			}
			else {
				cell_lines[col] = {""};
			}

			row_height = std::max(row_height, cell_lines[col].size());
		}

		std::vector<std::pair<bool, format::Formatter>> cell_formatters(ctx.number_of_all_columns);
		for (std::size_t col = 0; col < ctx.number_of_all_columns; ++col) {
			if (col < cells.size())
				cell_formatters[col] = {cells[col].style_formatter_set, cells[col].style_formatter_};
		}

		// print each "line" of the row
		for (std::size_t line_index = 0; line_index < row_height; ++line_index) {

			if (use_color_border_) {
				std::cout << style_formatter_.get_style_prefix();
			}
			std::cout << border_vertical_;
			if (use_color_border_) {
				std::cout << style_formatter_.get_style_suffix();
			}
			
			for (std::size_t col = 0; col < ctx.number_of_all_columns; ++col) {

				// compute vertical offset for vertical centering, if enabled
				std::size_t offset = 0;
				if (vertical_centering_enabled_) {
					offset = (row_height > cell_lines[col].size() ? (row_height - cell_lines[col].size()) / 2 : 0);
				}

				const std::string& cell_line =
					(line_index >= offset && (line_index - offset) < cell_lines[col].size())
					? cell_lines[col][line_index - offset] : "";
				const std::size_t content_length = cell_line.size();
				const std::size_t total_padding = (ctx.column_widths[col] > content_length ? ctx.column_widths[col] - content_length : 0);
				
				size_t cell_left_pad = 0, cell_right_pad = 0;
				adjust_spacing_for_alignment_(total_padding, cell_left_pad, cell_right_pad);

				// pad cell_line to exactly the column width
				std::string padded = cell_line;
				padded.append(ctx.column_widths[col] - content_length, ' ');
					
				// If style formatter has been set for individual cell, then overwrite the row formatter
				const std::string format_prefix = (cell_formatters[col].first ? cell_formatters[col].second.get_style_prefix() 
						: row_formatter.get_style_prefix());
				const std::string format_suffix = (cell_formatters[col].first ? cell_formatters[col].second.get_style_suffix()
						: row_formatter.get_style_suffix());

				std::cout << format_prefix 
					<< std::string(default_right_spacing_, ' ')
					<< std::string(cell_left_pad, ' ')
					<< cell_line 
					<< std::string(cell_right_pad, ' ')
					<< std::string(default_right_spacing_, ' ')
					<< format_suffix; 

				if (use_color_border_) {
					std::cout << style_formatter_.get_style_prefix();
				}
				std::cout << border_vertical_;
				if (use_color_border_) {
					std::cout << style_formatter_.get_style_suffix();
				}

			}
			std::cout << '\n';
		}

		// print divider after each row
		if (table_border_style_ != BorderStyle::none) {
			print_horizontal_line_(ctx);
		}
	}
}

} // namespace cctable
