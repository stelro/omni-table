#pragma once

#include <type_traits>
#include <string>

namespace gctable::format {

enum class style : int {
	none		= 0 << 0,
	bold		= 1 << 1,
	faint		= 1 << 2,
	italic		= 1 << 3,
	underline	= 1 << 4,

	black		= 1 << 5,
	red			= 1 << 6,
	green		= 1 << 7,
	yellow		= 1 << 8,
	blue		= 1 << 9,
	magenta		= 1 << 10,
	cyan		= 1 << 11,
	white		= 1 << 12,
};

inline style operator|(style lhs, style rhs) {
        return static_cast<style>(
            static_cast<std::underlying_type_t<style>>(lhs) |
            static_cast<std::underlying_type_t<style>>(rhs)
        );
    }

inline style operator&(style lhs, style rhs) {
	return static_cast<style>(
		static_cast<std::underlying_type_t<style>>(lhs) &
		static_cast<std::underlying_type_t<style>>(rhs)
	);
}

template <typename E>
constexpr auto to_underlying(E e) noexcept {
	return static_cast<std::underlying_type_t<E>>(e);
}

class Formatter {
public:

	void add_style(style s) {
		flags_ |= to_underlying(s);
		compute_style_prefix_();
	}

	auto get_style_prefix() const { return prefix_; }
	auto get_style_suffix() const { return suffix_; }

private:
	using underlying_t = std::underlying_type_t<style>;
	underlying_t flags_ {0};
	const std::string suffix_ {"\033[0m"};
	std::string prefix_;

	void compute_style_prefix_();
};

} // namespace gctable::format
