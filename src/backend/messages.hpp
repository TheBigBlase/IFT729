#ifndef MESSAGES_HPP
#define MESSAGES_HPP

#include "value_types.hpp"

constexpr value_t string_to_int(const char *s, value_t depth) {
	return !s[depth]
			   ? 0
			   : static_cast<int>((string_to_int(s, depth + 1) * 2) ^ s[depth]);
}

constexpr value_t string_to_int(const char *s) { return string_to_int(s, 0); }

enum messages {
	PX		= string_to_int(static_cast<const char *>("PX")),
	MSSG		= string_to_int(static_cast<const char *>("MSSG")),
	WIN		= string_to_int(static_cast<const char *>("WIN")),
	JOIN	= string_to_int(static_cast<const char *>("JOIN")),
	NEWROOM	= string_to_int(static_cast<const char *>("NEWROOM")),
	LEAVE	= string_to_int(static_cast<const char *>("LEAVE")),
	LOOSE	= string_to_int(static_cast<const char *>("LOOSE"))
};

#endif
