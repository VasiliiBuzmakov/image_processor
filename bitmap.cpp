#include "bitmap.h"

#include <fstream>

bool Bitmap::Load(const char* file_name) {
    std::fstream file;
    file.open(file_name, std::ios_base::in | std::ios_base::binary); // Открываем файл на чтение как бинарный
    if (!file.is_open()) {
        return false;
        // TODO обработать эту ситуацию
    }
    Load(file);
    return true;
}

// TODO Проверки, что поток не сломался, правильный файл итп.
// if(stream) - поток неявно может быть приведён к логическому выражению.
// Если этот if возвращает false - поток сломался (мы не можем из него больше читать).
// Работать это может так: while(std::getline(stream, line)) {...}.
// if(stream) не проверяет, закончился ли файл, поэтому пишут так:
// while(std::getline(stream, line) && !stream.eof()) {...}
// eof - end of file.
bool Bitmap::Load(std::istream& stream) {
    // TODO Никак не обрабатывается ситуация со сломанным потоком (assert?)
    stream.read(reinterpret_cast<char*> (&bmp_header_), sizeof(bmp_header_));
    stream.read(reinterpret_cast<char*> (&dib_header_), sizeof(dib_header_));
    return true;
}

bool Bitmap::CreateFile(const char* file_name) {
    std::ofstream file;
    file.open(file_name, std::ios_base::out | std::ios_base::binary); // Открываем файл на вписывание как бинарный
    if (!file.is_open()) {
        return false;
        // TODO обработать эту ситуацию
    }
    CreateFile(file);
    return true;
}

bool Bitmap::CreateFile(std::ofstream& stream) {
    stream.write(reinterpret_cast<char*> (&bmp_header_), sizeof(bmp_header_));
    stream.write(reinterpret_cast<char*> (&dib_header_), sizeof(dib_header_));
    return true;
}
