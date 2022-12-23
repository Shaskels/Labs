#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

namespace af {
	const int TwoBytes = 2;
	const int FourBytes = 4;
	const int SAMPLE_RATE = 44100;
	enum Bytes {
		FirstByte,
		SecondByte,
		ThirdByte,
		FourthByte
	};
	class AudioFile {
		std::ifstream* in;
		uint32_t readOut;
		uint32_t chunkSize;
		uint32_t subChunk1Size;
		uint16_t audioFormat;
		uint16_t numChannels;
		uint32_t sampleRate;
		uint32_t byteRate;
		uint16_t BlockAlign;
		uint16_t bitsPerSample;
		uint16_t subChunkList;
		uint32_t subChunk2Size;
		std::vector<int16_t> list;
		std::vector<int16_t> samples;
	public:
		AudioFile();
		int load(std::string);
		int save(std::string);
		void writeToFile(std::string);
		std::vector<int16_t> getSamples();
		int getSubChunk2Size();
		void writeNewSamples(std::vector<int16_t>);
		int readSamples();
		void closeIn();

	};
}