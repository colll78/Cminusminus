#include <string>
#include <iostream>
#include <unordered_map>
#include <fstream>

class char_reader {
private:
    std::string file_name;
    bool skipLT = false;

public:
    static const char EOFCH = (char) -1;
    int line_number = 0;
    std::ifstream src_file;

    char_reader(std::string file_name) {
        this->file_name = file_name;
        src_file.open(file_name);
    }

    char nextChar() {
        char c;
        if (src_file.eof()) {
            return EOFCH;
        }
        else {
            src_file.get(c);
            if (skipLT) {
                if (c == '\n') {
                    src_file.get(c);
                }
                skipLT = false;
            }
            switch (c) {
            case '\r':
                skipLT = true;
            case '\n':
                this->line_number++;
                break;
            }
        }
        return c;
    }

    std::string get_file_name() { return this->file_name; }

    int get_line() { return this->line_number; }

    ~char_reader() {
        src_file.close();
    }
};

class scanner {
public:
    const char EOFCH = char_reader::EOFCH;

private:
    char_reader input;
    std::unordered_map<std::string, std::string> reserved;
    char ch;

};

//int main()
//{
//    std::cout << "Hello World!\n";
//    std::cout << sizeof(long) << "\n";
//}