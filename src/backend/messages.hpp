#ifndef MESSAGES_HPP
#define MESSAGES_HPP

#ifndef VALUE_T
#define VALUE_T

using value_t = int;

#endif


constexpr value_t string_to_int(const char *s, value_t depth) {
	return !s[depth] ? 0 : (string_to_int(s, depth + 1) * 42) ^ s[depth];
}

constexpr value_t string_to_int(const char *s) {
	return string_to_int(s, 0);
}

enum messages { 
	PX		= string_to_int(static_cast<const char *>("PX")),
	MSG		= string_to_int(static_cast<const char *>("MSG")),
	JOIN	= string_to_int(static_cast<const char *>("JOIN")),
	LEAVE	= string_to_int(static_cast<const char *>("LEAVE")),
	WIN		= string_to_int(static_cast<const char *>("WIN")),
	LOOSE	= string_to_int(static_cast<const char *>("LOOSE"))
};

#endif
