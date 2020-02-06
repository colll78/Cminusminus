#pragma once
#ifndef JMM_GLOBAL_MACROS
#define JMM_GLOBAL_MACROS
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
const char os_path_separator = ';';

#elif __linux__
const char os_path_separator = ':';

#elif __unix___
const char os_path_separator = ':';

#endif

#endif // JMM_GLOBAL_MACROS
