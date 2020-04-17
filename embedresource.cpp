#include <iostream>
#include <algorithm>
#include <fstream>
#include <filesystem>


int main(int argc, char** argv)
{
    if (argc < 3)
    {
        fprintf(stderr, "USAGE: %s {sym} {rsrc}\n\n"
                        "  Creates {sym}.cpp from the contents of {rsrc}\n",
                argv[0]);

        return EXIT_FAILURE;
    }

    //std::ofstream debug_log("debug_log.txt");

    std::filesystem::path dst{argv[1]};
    std::filesystem::path src{argv[2]};


    std::string symbol_name = src.u8string();
    std::replace(symbol_name.begin(), symbol_name.end(), '.', '_');
    std::replace(symbol_name.begin(), symbol_name.end(), '-', '_');
    std::replace(symbol_name.begin(), symbol_name.end(), '/', '_');

    std::filesystem::create_directories(dst.parent_path());

    std::ofstream ofs{dst};
    std::ifstream ifs{src};

    ofs << "#include <stdlib.h>" << std::endl;
    ofs << "extern const char resource_" << symbol_name << "[] = {" << std::endl;

    size_t lineCount = 0;
    while (!ifs.eof())
    {
        char c;
        ifs.get(c);
        ofs << "0x" << std::hex << (c&0xff) << ", ";
        if (++lineCount == 10) {
            ofs << std::endl;
            lineCount = 0;
        }
    }


    ofs << "};" << std::endl;
    ofs << "extern const size_t resource_" << symbol_name << "_len = sizeof(resource_" << symbol_name << ");";

    return EXIT_SUCCESS;
}
