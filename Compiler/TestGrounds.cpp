#include <iostream>
#include <typeinfo>
#include <stdexcept>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <filesystem>
#include "jmm_global_macros.h"
#include <cassert>

std::string get_env_variable(const std::string &to_find) {
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

std::string console_exec_to_string(std::string command) {
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

char* format_boot_path(const char* format_string, const char* home, int home_len) {
    int formatted_path_len = 0;
    const char* p;
    for (p = format_string; *p != 0; p++) {
        if (*p == '%') formatted_path_len += home_len - 1;
        ++formatted_path_len;
    }

    char* formatted_path = (char*)malloc(formatted_path_len + 1 * sizeof(char));
    if (formatted_path == NULL) {
        return NULL;
    }

    char* q = formatted_path;
    for (p = format_string; *p != 0; p++) {
        switch (*p) {
        case '%':
            strcpy_s(q, formatted_path_len, home);
            q += home_len;
            break;
        case '/':
            *q++ = std::filesystem::path::preferred_separator;
            break;
        case ':':
            *q++ = os_path_separator;
        default:
            *q++ = *p;
        }
    }
    *q = '\0';
    assert((q - formatted_path) == formatted_path_len, "formatted_path size botched");
    return formatted_path;
}

int main() {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    std::string test = console_exec_to_string("java -verbose");
    size_t found = test.find("opened:");
    if (found != std::string::npos) {
        size_t end_pos = test.find('\n', found);
        if (end_pos != std::string::npos) {
            std::cout << test.substr(found + 8, end_pos);
        }
    }

    std::string type_descriptor("[java/util/ArrayList;");
    std::cout << type_descriptor.substr(1, type_descriptor.length()-2);
    std::cout << "\n" << type_descriptor.back();
    std::cout << "\n" << type_descriptor[type_descriptor.size()-1];

#elif __linux__

#elif __unix___
    
#endif
}