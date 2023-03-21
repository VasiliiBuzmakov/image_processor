#pragma once

#include <cstdint>
#include <iostream>

class Bitmap {
    // Структуры просто на поиграться с padding:
public:
    struct TestHeader {
        unsigned char field1; // __attribute__((__packed__));
        unsigned short field2; //__attribute__((__packed__));
        unsigned long field3; //__attribute__((__packed__));
    };
    struct TestHeader2 {
        unsigned char field1; // __attribute__((__packed__));
        unsigned short field2; //__attribute__((__packed__));
        unsigned long field3; //__attribute__((__packed__));
    } __attribute__((__packed__));

public:
    struct BMPHeader {
        uint16_t signature;
        uint32_t file_size;
        uint32_t dummy;
        uint32_t bitarray_offset;
    } __attribute__((__packed__));

    struct DIBHeader {
        uint32_t dib_header_size;
        uint32_t width;  // Ширина
        uint32_t height;  // Высота
        uint64_t dummy;  // Это же нам не нужно?
        uint32_t raw_bitmap_data_size;  // (including padding)
        uint64_t dummy2;  // Это же нам не нужно?
        uint64_t dummy3;  // Это же нам не нужно?
    }; __attribute__((__packed__));

protected:
    BMPHeader bmp_header_;
    DIBHeader dib_header_;

public:
    // Загружает файл из переданного потока чтения (функция под этой как раз возвращает поток)
    bool Load(std::istream& stream);

    // Загружает файл с картинкой по имени в поток
    bool Load(const char* file_name);

    // Создаёт по имени файла bmp файл и загружает туда что-то.
    bool CreateFile(const char* file_name);

    // Мы можем не иметь права записывать что-то на диск или не иметь какой-то папки
    // поэтому делим create file в виде двух функций, по аналогии с load.
    bool CreateFile(std::ofstream& stream);
};