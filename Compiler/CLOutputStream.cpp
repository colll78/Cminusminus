#define _CRT_SECURE_NO_WARNINGS 1
#include "CLOutputStream.h"
#include "jmm_utils.h"
#include "iostream"
//#include <cstring>
//#include <cerrno>

CLOutputStream::CLOutputStream() : buf(8192), buf_count(0), cle_output_bytes(32), count(0), bytes_written(0) , closed(true){
	
}

CLOutputStream::CLOutputStream(std::wstring f_name) : buf(8192), buf_count(0), cle_output_bytes(32), count(0), bytes_written(0) {
	closed = false;
	file_path = f_name;
	file.open(file_path, std::fstream::binary | std::fstream::out);
	//if (!file.is_open()) {
	  //std::cout << std::strerror(errno) << '\n'; // displays "Permission denied"
  
	//}
	std::cout << (file.is_open() ? "True" : "False");
}

void CLOutputStream::write(std::vector<std::byte> b, int off, int len) {
	if (len >= buf.size()) {
		flush_buffer();
		for (int i = 0; i < len; i++) {
			CLOutputStream::_write(b[off + i]);
		}
		return;
	}
	if (len > buf.size() - buf_count) {
		flush_buffer();
	}
	for (int i = 0; i < len; i++) {
		buf.push_back(b[off + i]);
		buf_count++;
	}
}

void CLOutputStream::write(std::vector<std::byte> b) {
	write(b, 0, b.size());
}

void CLOutputStream::_write(std::byte b) {
	if (!file_path.empty()) {
		file.write(reinterpret_cast<const char*>(b), 1);
	} else {
		CLOutputStream::cle_output_bytes.push_back(b);
	}
	count++;
}

void CLOutputStream::write(std::byte b) {
	if (buf_count >= buf.size()) {
		flush_buffer();
	}
	buf.push_back(b);
	buf_count++;
}

void CLOutputStream::write(int b) {
	write((std::byte) b);
}

void CLOutputStream::write_int(int v) {
	write((v >> 24) & 0xFF);
	write((v >> 16) & 0xFF);
	write((v >> 8) & 0xFF);
	write((v >> 0) & 0xFF);
}

void CLOutputStream::write_int(long long v) {
	long mask = 0xFF;
	write((std::byte)(mask & (v >> 24)));
	write((std::byte)(mask & (v >> 16)));
	write((std::byte)(mask & (v >> 8)));
	write((std::byte)(mask & v));
}

void CLOutputStream::write_boolean(bool v) {
	write(v ? (std::byte) 1 : (std::byte) 0);
}

void CLOutputStream::write_byte(int v) {
	write((std::byte) v);
}

void CLOutputStream::write_short(int v) {
	write((std::byte)((v >> 8) & 0xFF));
	write((std::byte)((v >> 0) & 0xFF));
}

void CLOutputStream::write_char(int v) {
	write((std::byte) v);
}

void CLOutputStream::write_long(long long v) {
	std::vector<std::byte> long_buffer(8);
	long_buffer[0] = (std::byte)(v >> 56);
	long_buffer[1] = (std::byte)(v >> 48);
	long_buffer[2] = (std::byte)(v >> 40);
	long_buffer[3] = (std::byte)(v >> 32);
	long_buffer[4] = (std::byte)(v >> 24);
	long_buffer[5] = (std::byte)(v >> 16);
	long_buffer[6] = (std::byte)(v >> 8);
	long_buffer[7] = (std::byte)(v >> 0);
	write(long_buffer, 0, 8);
}

void CLOutputStream::write_float(float f){
	write_int(float_to_int_bits(f));
}

void CLOutputStream::write_double(double d) {
	write_long(double_to_long_bits(d));
}

void CLOutputStream::write_bytes(std::string str) {
	int len = str.length();
	for (int i = 0; i < len; i++) {
		write((std::byte)str.at(i));
	}
}

void CLOutputStream::write_chars(std::string str) {
	int len = str.length();
	for (int i = 0; i < len; i++) {
		int v = str[i];
		write((v >> 8) & 0xFF);
		write((v >> 0) & 0xFF);
	}
}

void CLOutputStream::write_UTF(std::string str) {
	int strlen = str.length();
	int utflen = 0;
	int c, count = 0;

	for (int i = 0; i < strlen; i++) {
		c = str[i];
		if ((c >= 0x0001) && (c <= 0x007F)) {
			utflen++;
		}
		else if (c > 0x07FF) {
			utflen += 3;
		}
		else {
			utflen += 2;
		}
	}

	if (utflen > 65535) {
		std::cout << "Encoded string too long: " << utflen << " bytes.\n";
	}

	if (bytearr.size() < (utflen + 2)) {
		bytearr.resize((utflen * 2) + 2);
	}

	bytearr[count++] = (std::byte) ((utflen >> 8) & 0xFF);
	bytearr[count++] = (std::byte) ((utflen >> 0) & 0xFF);

	int i;
	for (i = 0; i < strlen; i++) {
		c = str[i];
		if (!((c >= 0x0001) && (c <= 0x007F))) break;
		bytearr[count++] = (std::byte) c;
	}
	for (; i < strlen; i++) {
		c = str[i];
		if ((c >= 0x0001) && (c <= 0x007F)) {
			bytearr[count++] = (std::byte) c;
		}
		else if (c > 0x07FF) {
			bytearr[count++] = (std::byte) (0xE0 | ((c >> 12) & 0x0F));
			bytearr[count++] = (std::byte) (0x80 | ((c >> 6) & 0x3F));
			bytearr[count++] = (std::byte) (0x80 | ((c >> 0) & 0x3F));
		}
		else {
			bytearr[count++] = (std::byte) (0xC0 | ((c >> 6) & 0x1F));
			bytearr[count++] = (std::byte) (0x80 | ((c >> 0) & 0x3F));
		}
		write(bytearr, 0, utflen + 2);
	}
}

void CLOutputStream::open(){
	if (closed) {
		file.open(file_path, std::fstream::binary);
		closed = false;
	}
}

void CLOutputStream::close(){
	if (!closed) {
		file.close();
		closed = true;
	}
}

int CLOutputStream::size() {
	return CLOutputStream::count;
}

void CLOutputStream::reset() {
	CLOutputStream::count = 0;
}

void  CLOutputStream::flush_buffer() {
	if (CLOutputStream::buf_count > 0) {
		for (int i = 0; i < buf_count; i++) {
			// writing from buffer to cl_output
			CLOutputStream::_write(buf[i]);
		}
		buf_count = 0;
	}
}

std::vector<std::byte> CLOutputStream::to_byte_array() {
	return std::vector<std::byte>(cle_output_bytes);
}