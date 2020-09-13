#include <iostream>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <string>


int main(int argc, char** argv)
{
    if (argc < 3)
    {
        fprintf(stderr, "USAGE: %s {sym} {rsrc}\n\n"
                        "  Creates {sym}.cpp from the contents of {rsrc}\n",
                argv[0]);

        return EXIT_FAILURE;
    }

    std::filesystem::path dst{argv[1]};
    std::filesystem::path src{argv[2]};

    std::string symbol_name = dst.stem().stem().u8string();

    std::replace(symbol_name.begin(), symbol_name.end(), '-', '_');
    //std::replace(symbol_name.begin(), symbol_name.end(), '.', '_');
    //std::replace(symbol_name.begin(), symbol_name.end(), '/', '_');

    /*
    std::string logfilename = std::string("embed_resource_debug_") + symbol_name + std::string(".txt");
    std::ofstream debug_log(logfilename);

    auto exists = std::filesystem::exists(src);
 
    debug_log << "exists " << exists << '\n';
    debug_log << "argv[0] " << argv[0] << '\n';
    debug_log << "src.string() " << src.string() << '\n';
    debug_log << "dst.parent_path() " << dst.parent_path() << '\n';
    debug_log << "dst.string() " << dst.string() << '\n';
    debug_log << "symbol_name " << symbol_name << '\n';

    debug_log.close();
    */

    std::filesystem::create_directories(dst.parent_path());

    std::ofstream ofs{dst};
    std::ifstream ifs{src};

    ofs << "#include <iostream>" << std::endl;
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
