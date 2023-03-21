#include "cmd_arg_parser.h"
#include "filter_pipeline_factory.h"
#include "bitmap.h"

#include <cassert>
#include <iostream>


void Test1(int argc, char* argv[]) {
    std::cout << "number of args: " << argc << std::endl;
    for (int i = 0; i < argc; ++i) {
        std::cout << "arg[" << i << "] = " << argv[i] << std::endl;
    }
}

void Test2() {
    FilterDescriptor desc1{"blur", {"12", "23", "156"}};
}

// Создаём промежуточный объект и заполняем его создателями индивидуальных фильтров.
// Данный тест является прообразом статической конфигурации приложения, то есть
// в нём задаётся конкретный набор типов фильтров, которые приложение сможет использовать.
void Test3() {
    FilterPipelineFactory fpf;
    fpf.AddFilterMaker("blur", &FilterFactories::MakeBlurFilter);  // & не обязательно, ибо неявное приведение
    fpf.AddFilterMaker("crop", &FilterFactories::MakeCropFilter);
    FilterPipelineFactory::FilterFactory gear = fpf.GetFilterFactoryMaker("blur");
    assert(gear /*!= nullptr*/);
    FilterPipelineFactory::FilterFactory non_existing_gear = fpf.GetFilterFactoryMaker("alpha");
    assert(!non_existing_gear);
}

// Имеет один описатель фильтра, проверяем, что с его помощью можем создать объект фильтра
// по средствам промежуточного объекта.
void Test4() {
    FilterPipelineFactory fpf;
    fpf.AddFilterMaker("blur", &FilterFactories::MakeBlurFilter);
    fpf.AddFilterMaker("crop", &FilterFactories::MakeCropFilter);

    FilterDescriptor desc1{"blur", {"12", "23", "156"}};

    BaseFilter* filter = fpf.CreateFilter(desc1);
    assert(filter);
    filter->Apply();
    delete filter;
}

// Создаст фильтр из дескриптора руками.
void Test5() {
    FilterDescriptor desc1{"blur", {"12", "23", "156"}};
    BaseFilter* filter = FilterFactories::MakeBlurFilter(desc1);
    assert(filter);
    delete filter;

    FilterDescriptor desc2{"blurrrrr", {"12", "23", "156"}};
    try {
        BaseFilter* filter2 = FilterFactories::MakeBlurFilter(desc2);
    }
    catch (std::exception& e) {
        std::cerr << e.what();
    }
}

// Проверяем, что структуры правильно упаковываются (возникает ли проблема из-за padding)
void Test6() {
    Bitmap::TestHeader header = {0x55, 0xAAAA, 0x55555555}; // 0x - 16 ричное представление
    Bitmap::TestHeader2 header2 = {0x55, 0xAAAA, 0x55555555};
    // И тут padding пропал
}

// Тестим считывание файла
void Test7() {
    const char* filename = "../example.bmp";
    Bitmap bitmap{};
    if (!bitmap.Load(filename)) {
        std::cout << "Cannot find file with this name or some other mistake";
    }
}

// Тестим создание файла
void Test8() {
    const char* input_filename = "../example.bmp";
    Bitmap bitmap{};
    if (!bitmap.Load(input_filename)) {
        std::cout << "Cannot find file with this name or some other mistake";
    }

    const char* output_filename = "../output_example.bmp";
    if (!bitmap.CreateFile(output_filename)) {
        std::cout << "Cannot write into file with this name or some other mistake";
    }
}

int main(int argc, char* argv[]) {
//    Test1(argc, argv);
//    Test2();
//    Test3();
//    Test4();
//    Test5();
//    Test6();
//    Test7();
    Test8();
}
