#include "CLInputStream.h"
#include <array>

CLInputStream::CLInputStream(std::string f_name){
	closed = false;
	file.open(f_name, std::fstream::binary);
	file_path.assign(f_name.begin(), f_name.end());
}

CLInputStream::CLInputStream(std::wstring f_name){
	closed = false;
	file.open(f_name, std::fstream::binary);
	file_path = f_name;
}

int CLInputStream::read(){
	int b;
	if (!file.eof()) {
		file.read((char*)&b, 1);
		return b;
	}
	return -1;
}

int CLInputStream::read(std::vector<std::byte> &b){
	return read(b, 0, b.size());
}

int CLInputStream::read(std::vector<std::byte> &b, int off, int length){
	if (!file.eof()) {
		if (off + length < b.size()) {
			file.read((char*)&b[off], length);
			return length;
		}
		else {
			int j = 0;
			for (int index = off; index < b.size() && j < length; index++, j++) {
				file.read((char*)&b[index], 1);
			}
			return j;
		}
	}
	return -1;
}

long long CLInputStream::skip(long long n){
	if (file.good()) {
		file.ignore(n);
		return n;
	}
	return -1; 
}

void CLInputStream::open(){
	if (closed) {
		file.open(file_path, std::fstream::binary);
		closed = false;
	}
}

void CLInputStream::close(){
	if (!closed) {
		closed = true;
		file.close();
	}
}


const long CLInputStream::read_unsigned_int(){
	std::vector<std::byte> b;
	long long mask = 0xFF, l;
	read(b);
	l = ((unsigned char(b[0]) & mask) << 24) | ((unsigned char(b[1]) & mask) << 16)
		| ((unsigned char(b[2]) & mask) << 8) | (unsigned char(b[3]) & mask);
	return l;
}
