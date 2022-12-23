#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "ConfigurationFile.h"
std::string STOP_SYMBOL = "!";
char LINK = '$';
char DELETE = '0';
bool isDigit(std::string s) {
	for (int i = 0; i < s.size(); i++) {
		if (!isdigit(s[i]))
			return false;
	}
	return true;
}
int makeInt(std::string s) {
	int t = 0;
	int level = 1;
	for (int i = 0; i < s.size(); i++) {
		t = (s[i] - '0') + t * 10;
	}
	return t;
}

int configs::ConfigurationFile::getConfigs(std::string file, ConfigurationFile& conf) {
	err::Errors r;
	std::ifstream f(file);
	if (!f) {
		std::cerr << r.ConfFileErr << std::endl;
		return err::ERROR_VALUE;
	}
	std::string str;
	std::string c;
	int i = 0;
	f >> c;
	while (c != STOP_SYMBOL) {
		try {
			f.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			if (c == "#")
				getline(f, str, '\n');
			else {
				if (isDigit(c))
					conf.Times.push_back(makeInt(c));
				else if (c[0] == LINK) {
					c[0] = DELETE;
					conf.Links.push_back(makeInt(c));
				}
				else {
					conf.Converters.push_back(c);
				}
			}
			f >> c;
		}
		catch (const std::ios_base::failure& fail) {
			std::cerr << fail.what() << '\n';
			return err::ERROR_VALUE;
		}
	}
	return err::SUCCESS;
}