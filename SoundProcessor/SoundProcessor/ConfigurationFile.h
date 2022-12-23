#pragma once
#include <vector>
#include <string>
#include "Errors.h"
namespace configs {
	class ConfigurationFile {
	public:
		std::vector<std::string> Converters;
		std::vector<int> Times;
		std::vector<int> Links;

		int getConfigs(std::string file, ConfigurationFile& conf);
	};
}