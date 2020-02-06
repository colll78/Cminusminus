#pragma once
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>


class CLInputStream {
public:
	CLInputStream(std::string f_name);
	CLInputStream(std::wstring f_name);
	int read();
	int read(std::vector<std::byte> &b);
	int read(std::vector<std::byte> &b, int off, int length);
	long long skip(long long n);
	void open();
	void close();
	const long read_unsigned_int();
private:
	std::wstring file_path;
	std::fstream file;
	volatile bool closed;
};