#include "jmm_utils.h"
#include <string>
#include <algorithm>
#include <filesystem>

int float_to_int_bits(float f){
    static_assert(sizeof(float) == sizeof(unsigned int), "Sizes must match");
    int ret;
    memcpy(&ret, &f, sizeof(float));
    return ret;
}

long long double_to_long_bits(double d) {
    static_assert(sizeof(double) == sizeof(long long), "Sizes must match");
    long long ret;
    memcpy(&ret, &d, sizeof(double));
    return ret;
}

std::vector<std::byte> string_to_bytes(std::string str){
    std::vector<std::byte> string_bytes(str.size() + 1);
    std::transform(str.begin(), str.end(), string_bytes.begin(), [](char c) { return std::byte(c); });
    return string_bytes;
}

void ltrim(std::string& s){
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

void rtrim(std::string& s){
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

void trim(std::string& s){
    ltrim(s);
    rtrim(s);
}

std::string ltrim_copy(std::string s){
    ltrim(s);
    return s;
}

std::string rtrim_copy(std::string s){
    rtrim(s);
    return s;
}

namespace jmm_string_utils {

	void replace_all(std::string& str, const std::string& from, const std::string& to){
        size_t start_pos = 0;
        int index_adv = to.length();
        int from_len = from.length();
        while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from_len, to);
            start_pos += index_adv; // Handles case where 'to' is a substring.
        }
	}

    void replace_all(std::wstring& str, const std::wstring& from, const std::wstring& to){
        size_t start_pos = 0;
        int index_adv = to.length();
        int from_len = from.length();
        while ((start_pos = str.find(from, start_pos)) != std::wstring::npos) {
            str.replace(start_pos, from_len, to);
            start_pos += index_adv; // Handles case where 'to' is a substring.
        }
    }

}

namespace jmm_system_utils {
    std::string get_env_variable(const std::string& to_find) {
        std::string env_var_data = "";
        size_t required_size;
        getenv_s(&required_size, 0, 0, "PATH");
        if (required_size == 0) {
            return env_var_data;
        }
        char* PATH_data = (char*)malloc(required_size * sizeof(char));
        if (!PATH_data) {
            return env_var_data;
        }
        getenv_s(&required_size, PATH_data, required_size, "PATH");
        env_var_data.assign(PATH_data);
        return env_var_data;
    }

    std::string console_exec_to_string(const std::string& command) {
        char buffer[500];
        std::string result = "";

        // Open pipe to file
        FILE* pipe = _popen(command.c_str(), "r");
        if (!pipe) {
            return result;
        }

        // read till end of process:
        while (!feof(pipe)) {
            // use buffer to read and add to result
            if (fgets(buffer, 500, pipe) != NULL)
                result += buffer;
            break;
        }

        _pclose(pipe);
        return result;
    }

    std::wstring console_exec_to_string(const std::wstring& command){
        wchar_t buffer[500];
        std::wstring result = L"";

        // Open pipe to file
        FILE* pipe = _wpopen(command.c_str(), L"r");
        if (!pipe) {
            return result;
        }

        // read till end of process:
        while (!feof(pipe)) {
            // use buffer to read and add to result
            if (fgetws(buffer, 500, pipe) != NULL)
                result += buffer;
            break;
        }

        _pclose(pipe);
        return result;
    }

    void all_ext_in_dir(std::vector<std::wstring>& container, const std::wstring& root, const std::wstring extension){
        if (!std::filesystem::exists(root) || !std::filesystem::is_directory(root)) return;
        for (auto& p : std::filesystem::recursive_directory_iterator(root)){
            if (p.path().extension() == extension)
                container.push_back(p.path().wstring());
        }
    }    

    void populate_system_properties() {
        std::wstring test = jmm_system_utils::console_exec_to_string(L"java -verbose");
        size_t found = test.find(L"opened:");
        if (found != std::wstring::npos) {
            size_t end_pos = test.find(L'\n', found);
            if (end_pos != std::wstring::npos) {
                std::wstring file_sep(1, std::filesystem::path::preferred_separator);
                std::filesystem::path java_home = test.substr(found + 8, end_pos);
                /*java_home.make_preferred();
                java_home /= L"lib";
                java_home /= L"rt.jar";*/
                jmm_system_utils::system_properties_map[jmm_system_utils::_java_home] = java_home;
            }
        }
        /* */
    }
}

namespace jmm_java_utils {
    bool is_java_identifier_start(char c) {
        if (isalpha(c) || jmm_string_utils::is_any_of<std::string>("_$")(c)) {
            return true;
        }
        return false;
    }

    bool is_java_identifier_part(char c){
        return (isalpha(c) || isdigit(c) || jmm_string_utils::is_any_of<std::string>("_$")(c));
    }
}