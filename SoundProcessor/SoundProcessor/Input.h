#pragma once

#include <boost/program_options.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "Errors.h"
namespace po = boost::program_options;
namespace np {
     class Input {
         std::vector<std::string> files;
     public:
         int GetProgramOptions(const int, const char* const []);
         std::string getFileName(int);
         int getFilesSize();
     };
}
/*    class Input {
    public:

        std::vector<std::string> files;

        int GetProgramOptions(const int, const char* const[]);
    };
}
    void showHelp(po::options_description desc) {
        std::cout << "Some help" << std::endl;
    }
    int np::Input::GetProgramOptions(const int argc, const char* const argv[]) {
        po::options_description desc("Allowed options");
        desc.add_options()
            ("-h", "Show help")
            ("-c", po::value<std::vector<std::string>>(&(files)), "File name");
        po::variables_map args;
        po::positional_options_description pos;
        if (argc == 1) {
            showHelp(desc);
        }
        try {
            po::store(po::parse_command_line(argc, argv, desc), args);
            po::notify(args);
            if (args.find("-h") != args.end())
                showHelp(desc);
            pos.add("input", -1);
            //po::store(po::command_line_parser(argc, argv).options(desc).positional(pos), pos);
        }
        catch (po::error const& e) {
            std::cerr << e.what() << '\n';
            return 1;
        }
        return 0;
    }*/