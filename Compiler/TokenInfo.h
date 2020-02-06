#pragma once
#include "TokenInfo.h"
#include <string>
#include <unordered_map>

class token_kind {
public:
	const enum class token_desc {
		EOF_TK,
		IF,
		ELSE,
		INT,
		BOOLEAN,
		CHAR,
		CLASS,
	};

	constexpr token_kind(token_desc tk_knd);
	operator token_desc() const;

	std::string get_image();


private:
	token_desc tk_enum;
	static const std::unordered_map<token_desc, std::string> token_map;
};
