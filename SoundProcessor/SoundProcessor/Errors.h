#pragma once
#include <map>
#include <string>

namespace err {
	int const ERROR_VALUE = 0;
	int const SUCCESS = 1;
	class Errors {
	public:
		std::string openErr = "Error! File could not be opened";
		std::string ChunkSizeErr = "Error! Failed to get ChunkSize";
		std::string FormatErr = "Error! Failed to get Format";
		std::string Subchunk1IDErr =  "Error! Failed to get Subchunk1ID";
		std::string Subchunk1SizeErr = "Error! Failed to get Subchunk1Size";
		std::string AudioFormatErr = "Error! Failed to get AudioFormat";
		std::string NumChannelsErr = "Error! Failed to get NumChannels";
		std::string SampleRateErr = "Error! Failed to get SampleRate";
		std::string ByteRateErr = "Error! Failed to get ByteRate";
		std::string BlockAlignErr = "Error! Failed to get BlockAlign";
		std::string BitsPerSampleErr = "Error! Failed to get BitsPerSample";
		std::string DataErr = "Error! Failed to get data";
		std::string subChunk2SizeErr = "Error! Failed to get subChunk2Size";
		std::string SamplesErr = "Error! Failed to get samples";
		std::string RIFFErr = "Error! Failed to get RIFF";
		std::string NoRIFFErr = "Error! The file does not start with a RIFF";
		std::string WAVEErr = "Error! Failed to get WAVE";
		std::string NoWAVEErr = "Error! The file does not have WAVE";
		std::string IncorArguments = "Error! Incorrect argument values";
		std::string ConfFileErr = "Error! The configuration file cannot be opened";
		std::string ConfFileArg = "Error! Few configuration file arguments";
		std::string ConverterErr = "Error! There is no such converter";
		std::string SaveFileErr = "Error! Unable to save file";
		std::string CommandLineArgErr = "Error! Few command line arguments";
		std::string CommandLineErr = "Error! Incorrect command line input format";
		/*std::map <int, std::string> errors = {
		{1, "Error! File could not be opened"},
		{3, "Error! Failed to get ChunkSize"},
		{4, "Error! Failed to get Format"},
		{5, "Error! Failed to get Subchunk1ID"},
		{6, "Error! Failed to get Subchunk1Size"},
		{7, "Error! Failed to get AudioFormat"},
		{8, "Error! Failed to get NumChannels"},
		{9, "Error! Failed to get SampleRate"},
		{10, "Error! Failed to get ByteRate"},
		{11, "Error! Failed to get BlockAlign"},
		{12, "Error! Failed to get BitsPerSample"},
		{13, "Error! Failed to get data"},
		{14, "Error! Failed to get subChunk2Size"},
		{15, "Error! Failed to get samples"},
		{16, "Error! Failed to get RIFF"},
		{17,"Error! The file does not start with a RIFF"},
		{18, "Error! Failed to get WAVE"},
		{19,"Error! The file does not have WAVE"},
		{20,"Error! Incorrect argument values"},
		{21,"Error! The configuration file cannot be opened"},
		{22,"Error! Few configuration file arguments"},
		{23,"Error! There is no such converter" },
		{24,"Error! Unable to save file"},
		{25, "Error! Few command line arguments"},
		{26, "Error! Incorrect command line input format"}
		};*/
	};
}