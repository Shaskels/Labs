
#include <iostream>
#include <fstream>
#include "Processor.h"

int const MIN_SIZE_MUTE = 2;
int const MIN_SIZE_MIX = 1;

int main(int argc, char* argv[])
{
	np::Input in;
	if (in.GetProgramOptions(argc, argv) == 0)
		return 0;
	std::vector<af::AudioFile> files;
	configs::ConfigurationFile config;
	if (config.getConfigs(in.getFileName(0), config) == 0)
		return 0;
	if (pr::CreateFiles(in, files) == 0)
		return 0;
	if (pr::Processing(in, files, config) == 0)
		return 0;
}