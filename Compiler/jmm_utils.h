#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>

int float_to_int_bits(float f);
long long double_to_long_bits(double d);
std::vector<std::byte> string_to_bytes(std::string str);

void ltrim(std::string& s);
void rtrim(std::string& s);
void trim(std::string& s);
std::string ltrim_copy(std::string s);
std::string rtrim_copy(std::string s);

namespace jmm_string_utils {

    void replace_all(std::string& str, const std::string& from, const std::string& to);
    void replace_all(std::wstring& str, const std::wstring& from, const std::wstring& to);

    template<typename predicate_t> void split(std::vector<std::string>& v, std::string str, predicate_t pred) {
        char* str_index = str.data();
        char* p = str_index;
        while (str_index) {
            if (!p) {
                return;
            }
            char* temp = str_index = p;
            while (pred(*temp) && *temp) {
                temp++, str_index++;
            }
            char* temp2 = p = str_index;
            while (!pred(*temp2) && *temp2) {
                temp2++, p++;
            }
            if (p == str_index) {
                p = 0;
                continue;
            }
            p = *p ? *p = 0, p + 1 : 0;
            v.push_back(std::string(str_index));
        }
    }

    template<typename predicate_t> void split(std::vector<std::wstring>& v, std::wstring str, predicate_t pred) {
        wchar_t* str_index = str.data();
        wchar_t* p = str_index;
        while (str_index) {
            if (!p) {
                return;
            }
            wchar_t* temp = str_index = p;
            while (pred(*temp) && *temp) {
                temp++, str_index++;
            }
            wchar_t* temp2 = p = str_index;
            while (!pred(*temp2) && *temp2) {
                temp2++, p++;
            }
            if (p == str_index) {
                p = 0;
                continue;
            }
            p = *p ? *p = 0, p + 1 : 0;
            v.push_back(std::wstring(str_index));
        }
    }

    template<class string_type>
	class is_any_of {
	public:
		is_any_of(std::string str) : str(std::move(str)) {}
        is_any_of(std::wstring str) : str(std::move(str)) {};
		is_any_of(const char* str) : str(str) {}
		is_any_of(const wchar_t* str) : str(str) {}
        is_any_of(const char c) : str(1, c) {}
        is_any_of(const wchar_t c) : str(1, c) {}

		bool operator() (char c) {
            for (auto* s = str.data(); s != "\0"; s++) {
                if (*s == c) {
                    return true;
                }
            }
            return false;
        }

        bool operator() (wchar_t c) {
            for (auto* s = str.data(); s != L"\0"; s++) {
                if (*s == c) {
                    return true;
                }
            }
            return false;
        }
	private:
		string_type str;
	};
    /*
    template <typename char_type>
    class is_any_of {
    public:
        using string_type = std::basic_string<char_type>;
        is_any_of(string_type str);
        is_any_of(char_type c);

        bool operator() (char_type c) const;
    private:
        string_type str;
    }; 
    
    auto is_any_of(const char* char_set) {
        return [chars(std::string(char_set))](const char c){
            return chars.find(c) != std::string::npos;
        };
    }
    */


}

namespace jmm_system_utils {
    std::string get_env_variable(const std::string& to_find);
    std::string console_exec_to_string(const std::string& command);
    std::wstring console_exec_to_string(const std::wstring& command);
    void all_ext_in_dir(std::vector<std::wstring>& container, const std::wstring& root, const std::wstring extension = L".jar");
    enum {
        _java_home, _java_class_path
    };
    static std::unordered_map<int, std::wstring> system_properties_map;

}

namespace jmm_java_utils {
    bool is_java_identifier_start(char c);
    bool is_java_identifier_part(char c);
}