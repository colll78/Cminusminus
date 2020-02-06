#include "TokenInfo.h"

constexpr token_kind::token_kind(token_desc tk_knd) : tk_enum(tk_knd) {}

token_kind::operator token_desc() const { return token_kind::tk_enum; }

std::string token_kind::get_image() {
	if (token_map.count(token_kind::tk_enum) > 0) {
		token_kind::token_map.at(token_kind::tk_enum);
	}
	return "";  
}

const std::unordered_map<token_kind::token_desc, std::string> token_kind::token_map = {
		{token_kind::token_desc::EOF_TK, "EOF_TK"},
		{token_kind::token_desc::IF, "IF"},
		{token_kind::token_desc::ELSE, "ELSE"},
	};