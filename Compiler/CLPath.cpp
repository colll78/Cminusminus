#include "CLPath.h"
#include "jmm_utils.h"
#include "jmm_global_macros.h"


CLPath::CLPath(std::wstring path, std::wstring extdir){
	if (path.empty()) {
		return;
	}
	/* To do: finish */
}

std::optional<CLInputStream> CLPath::load_class(std::wstring name){
	std::optional<CLInputStream> reader = std::nullopt;
	for (int i = 0; i < dirs.size(); i++) {
		std::wstring dir = dirs.at(i);
		std::filesystem::path file_path = dirs.at(i);
		if (std::filesystem::is_directory(file_path)) {
			file_path.make_preferred();
			//jmm_string_utils::replace_all(fp_string, std::wstring(L"/"), std::wstring(1, std::filesystem::path::preferred_separator));
			file_path.replace_extension(".class");
			reader = CLInputStream(file_path.wstring());
		}
		else if (std::filesystem::is_regular_file(file_path)) {
			/* TODO: handle zip files.*/
		}
	}
	return reader;
}

std::vector<std::wstring> CLPath::load_class_path(std::filesystem::path class_path){
	std::vector<std::wstring> container;
	jmm_string_utils::split(container, class_path, jmm_string_utils::is_any_of<std::wstring>(os_path_separator));

    std::wstring test = jmm_system_utils::console_exec_to_string(L"java -verbose");
    size_t found = test.find(L"opened:");
    if (found != std::wstring::npos) {
        size_t end_pos = test.find(L'\n', found);
        if (end_pos != std::wstring::npos) {
			std::wstring file_sep(1, std::filesystem::path::preferred_separator);
			std::filesystem::path java_home = test.substr(found + 8, end_pos);
			java_home.make_preferred();
			java_home /= L"lib";
			java_home /= L"rt.jar";
            container.push_back(java_home.wstring());
        }
    }
	return container;
}

