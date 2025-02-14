#include "formatter.h"

#include <vector>
#include <sstream>

namespace gctable::format {

void Formatter::compute_style_prefix_() {
	std::vector<int> codes;
	
	// Modification codes
	if (flags_ & to_underlying(style::none)) codes.push_back(0);
	if (flags_ & to_underlying(style::bold)) codes.push_back(1);
	if (flags_ & to_underlying(style::faint)) codes.push_back(2);
	if (flags_ & to_underlying(style::italic)) codes.push_back(3);
	if (flags_ & to_underlying(style::underline)) codes.push_back(4);


	// Color codes
	if (flags_ & to_underlying(style::black)) codes.push_back(30);
	if (flags_ & to_underlying(style::red)) codes.push_back(31);
	if (flags_ & to_underlying(style::green)) codes.push_back(32);
	if (flags_ & to_underlying(style::yellow)) codes.push_back(33);
	if (flags_ & to_underlying(style::blue)) codes.push_back(34);
	if (flags_ & to_underlying(style::magenta)) codes.push_back(35);
	if (flags_ & to_underlying(style::cyan)) codes.push_back(36);
	if (flags_ & to_underlying(style::white)) codes.push_back(37);

	std::ostringstream oss;
	oss << "\033[";
	for (size_t i = 0; i < codes.size(); ++i) {
		oss << codes[i];
		if (i + 1 != codes.size()) {
			oss << ';';
		}
	}
	oss << "m";
	prefix_ = oss.str();
}

} // namespace gctable::format
