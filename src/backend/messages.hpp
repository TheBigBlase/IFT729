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
	WIN		= string_to_int(static_cast<const char *>("WIN")),
	MSG		= string_to_int(static_cast<const char *>("MSG")),
	JOIN	= string_to_int(static_cast<const char *>("JOIN")),
	LEAVE	= string_to_int(static_cast<const char *>("LEAVE")),
	LOOSE	= string_to_int(static_cast<const char *>("LOOSE")),
	RECONN	= string_to_int(static_cast<const char *>("RECONN")),
	NEWROOM	= string_to_int(static_cast<const char *>("NEWROOM")),
	ROOMLIST= string_to_int(static_cast<const char *>("ROOMLIST")),
};

#endif
