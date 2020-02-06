#pragma once
#ifndef CLOUTPUTSTREAM_H
#define CLOUTPUTSTREAM_H
#include <string>
#include <vector>

class CLOutputStream {
public:
    CLOutputStream();
    CLOutputStream(int buf_size);
    void write(std::vector<std::byte> b, int off, int len);
    void write(std::vector<std::byte> b);
    void write(std::byte b);
    void write(int b);
    void write_int(long long v);
    void write_int(int v);
    void write_boolean(bool v);
    void write_byte(int v);
    void write_short(int v);
    void write_char(int v);
    void write_long(long long v);
    void write_float(float f);
    void write_double(double d);
    void write_bytes(std::string str);
    void write_chars(std::string str);
    void write_UTF(std::string str);

    int size();
    void reset();
    void flush_buffer();
    std::vector<std::byte> to_byte_array();


private:
    void _write(std::byte b);
    int bytes_written;
    int buf_count;
    int count;
    std::vector<std::byte> cle_output_bytes;
    std::vector<std::byte> bytearr;
    std::vector<std::byte> buf;

};

#endif 