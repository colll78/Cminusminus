#pragma once
#include "CLInputStream.h"
#include <filesystem>
#include <optional> 

class CLPath {
public:
	CLPath(std::wstring path, std::wstring extdir);
	std::optional<CLInputStream> load_class(std::wstring name);
private:
	std::vector<std::wstring> dirs;
	std::vector<std::wstring> load_class_path(std::filesystem::path class_path);
};