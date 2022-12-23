
#include <iostream>
#include <string>
#include <vector>
#include "Input.h"
#include "Ñonverter.h"

void showHelp() {
    std::vector<con::ConverterFactory*> factory;
    factory.push_back(new con::MuteTheIntervalFactory);
    factory.push_back(new con::MixerFactory);
    factory.push_back(new con::ReversFactory);
    for (int i = 0; i < factory.size(); i++) {
        std::vector<std::string> s = (*factory[i]).Reference();
        for (int j = 0; j < s.size(); j++) {
            std::string t = s[j];
            std::cerr << t;
        }
    }
}
int np::Input::GetProgramOptions(const int argc, const char* const argv[]) {
    err::Errors r;
    if (argc < 4) {
        std::cerr << r.SaveFileErr << std::endl;
        return err::ERROR_VALUE;
    }
    std::vector<std::string> sours;

    for (int i = 1; i < argc; i++) {
        sours.push_back(argv[i]);
    }

    for (int i = 0; i < sours.size(); i++) {
        if (sours[i].find("-h") != std::string::npos) {
            showHelp();
        }
        else if (sours[i].find("-c") != std::string::npos) continue;
        else if (sours[i].find("[") != std::string::npos) {
            if (sours[i][sours[i].size() - 1] != ']') {
                std::cerr << r.CommandLineErr << std::endl;
                return err::ERROR_VALUE;
            }
            sours[i].pop_back();
            sours[i].erase(0, 1);
            Input::files.push_back(sours[i]);
        }
    }
    return err::SUCCESS;
}

std::string np::Input::getFileName(int n) {
    return files[n];
}

int np::Input::getFilesSize() {
    return files.size();
}