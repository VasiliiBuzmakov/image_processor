#include "cmd_arg_parser.h"

bool CmdLineParser::Parse(int argc, char* argv[]) {
    if (argc < MIN_PARAM_NUM) {
        return false; // Недостаточно параметров
    }

    input_file_name_ = argv[INPUT_FILE_NAME_POS_];
    output_file_name_ = argv[OUTPUT_FILE_NAME_POS_];
    return false;
}

