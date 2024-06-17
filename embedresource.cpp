#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <filesystem>


int main(int argc, char** argv)
{
    if (argc < 3) {
        std::cerr << "USAGE: " << argv[0] << " {sym} {rsrc}" << std::endl << std::endl
            << "  Creates {sym}.c from the contents of {rsrc}" << std::endl;
        return EXIT_FAILURE;
    }

    //std::string sym(argv[2]);

    std::filesystem::path dst{ argv[1] };
    std::filesystem::path src{ argv[2] };

    std::string sym = dst.stem().stem().u8string();

    //std::replace(sym.begin(), sym.end(), '.', '_');
    std::replace(sym.begin(), sym.end(), '-', '_');
    //std::replace(sym.begin(), sym.end(), '/', '_');
    //std::replace(sym.begin(), sym.end(), '\\', '_');

    std::ifstream ifs{src};
    std::ofstream ofs{dst};

    std::filesystem::create_directories(dst.parent_path());

    ofs << "#include <iostream>" << std::endl;
    ofs << "extern const char resource_" << sym << "[] = {" << std::endl;

    size_t lineCount = 0;
    while (true)
    {
        char c;
        ifs.get(c);
        if (ifs.eof())
            break;

        ofs << "0x" << std::hex << (c & 0xff) << ", ";
        if (++lineCount == 10) {
            ofs << std::endl;
            lineCount = 0;
        }
    }

    ofs << "};" << std::endl;
    ofs << "extern const size_t resource_" << sym << "_len = sizeof(resource_" << sym << ");";

    return EXIT_SUCCESS;
}
