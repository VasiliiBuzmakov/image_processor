#pragma once

#include <string_view>
#include <vector>

struct FilterDescriptor {
    std::string_view filter_name;
    std::vector<std::string_view> filter_params;
};

class CmdLineParser {
public:
    static const int MIN_PARAM_NUM = 3;
    static const int INPUT_FILE_NAME_POS_ = 1;
    static const int OUTPUT_FILE_NAME_POS_ = 2;
public:
    bool Parse(int argc, char* argv[]);  // enum для разных случаев пользовательского ввода
    std::string_view GetInputFileName() const { return input_file_name_; }

protected:
    std::string_view input_file_name_;
    std::string_view output_file_name_;
};
