#include "AudioFile.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Errors.h"

af::AudioFile::AudioFile(){
	in = NULL;
	numChannels = 1;
	sampleRate = 44100;
	byteRate = 16;
	samples.resize(0);
	bitsPerSample = 16;
	subChunk2Size = 0;
}
int16_t convertToIntTwoBytes(char* buf) {
	int16_t n;
	unsigned char b1 = buf[af::FirstByte];
	unsigned char b2 = buf[af::SecondByte];
	n = (b2 << 8) | b1;
	return n;
}
int32_t convertToIntFourBytes(char* buf) {
	int32_t n;
	unsigned char b1 = buf[af::FirstByte];
	unsigned char b2 = buf[af::SecondByte];
	unsigned char b3 = buf[af::ThirdByte];
	unsigned char b4 = buf[af::FourthByte];
	n = (b4 << 24) | (b3 << 16) | (b2 << 8) | b1;
	return n;
}
int af::AudioFile::readSamples() {
	int16_t sample;
	char* bigBuffer = new char[af::SAMPLE_RATE * af::TwoBytes];

	err::Errors r;
	try{
		samples.erase(samples.begin(), samples.end());
		if (!(*in).read(bigBuffer, std::min(sampleRate * af::TwoBytes, readOut)))
			throw r.SamplesErr;
		for (int i = 0; i < std::min(sampleRate * af::TwoBytes, readOut); i+=2) {
			char buf[af::TwoBytes] = { bigBuffer[i], bigBuffer[i + 1] };
			sample = convertToIntTwoBytes(buf);
			(samples).push_back(sample);
		}
		readOut = readOut - sampleRate * af::TwoBytes;
	}
	catch (std::string s) {
		(*in).close();
		std::cerr << s << std::endl;
		return 1;
	}
	delete bigBuffer;
	return 0;
}
int af::AudioFile::load(std::string fileName) {
	err::Errors r;
	in = new std::ifstream(fileName, std::ios_base::binary);
	//in.open(fileName, std::ios_base::binary);
	try {
		if (!(*in).good()) throw r.openErr;
		char buf[af::FourBytes] = { 0 };
		if (!(*in).read(buf, af::FourBytes)) throw r.NoRIFFErr; // RIFF
		if (buf[0] != 'R' || buf[1] != 'I' || buf[2] != 'F' || buf[3] != 'F')
			throw r.NoRIFFErr;

		if (!(*in).read(buf, af::FourBytes)) throw r.ChunkSizeErr;
		chunkSize = convertToIntFourBytes(buf);

		if (!(*in).read(buf, af::FourBytes)) throw r.NoWAVEErr; // WAVE
		if (buf[0] != 'W' || buf[1] != 'A' || buf[2] != 'V' || buf[3] != 'E')
			throw 19;

		if (!(*in).read(buf, af::FourBytes)) throw r.Subchunk1IDErr;
		if (!(*in).read(buf, af::FourBytes)) throw r.Subchunk1SizeErr;
		subChunk1Size = convertToIntFourBytes(buf);

		if (!(*in).read(buf, af::TwoBytes)) throw r.AudioFormatErr;
		audioFormat = convertToIntTwoBytes(buf);

		if (!(*in).read(buf, af::TwoBytes)) throw r.NumChannelsErr;
		numChannels = convertToIntTwoBytes(buf);

		if (!(*in).read(buf, af::FourBytes)) throw r.SampleRateErr;
		sampleRate = convertToIntFourBytes(buf);

		if (!(*in).read(buf, af::FourBytes)) throw r.ByteRateErr;
		byteRate = convertToIntFourBytes(buf);

		if (!(*in).read(buf, af::TwoBytes)) throw r.BlockAlignErr;
		BlockAlign = convertToIntTwoBytes(buf);
		if (!(*in).read(buf, af::TwoBytes)) throw r.BitsPerSampleErr;
		bitsPerSample = convertToIntTwoBytes(buf);

		int16_t lst;
		if (!(*in).read(buf, af::FourBytes)) throw r.DataErr;
		while (buf[0] != 'd' && buf[1] != 'a' && buf[2] != 't' && buf[3] != 'a') {
			if (!(*in).read(buf, af::FourBytes)) throw r.DataErr;
			subChunkList = convertToIntFourBytes(buf);
			for (int i = 0; i < subChunkList / af::TwoBytes; i++) {
				if (!(*in).read(buf, af::TwoBytes)) throw r.DataErr;
				lst = convertToIntTwoBytes(buf);
				list.push_back(lst);
			}
			if (!(*in).read(buf, af::FourBytes)) throw r.DataErr;
		}
		if (!(*in).read(buf, af::FourBytes)) throw r.subChunk2SizeErr;
		subChunk2Size = convertToIntFourBytes(buf);

		readOut = subChunk2Size;
		readSamples();
		//in.close();
	}
	catch (std::string i) {
		//Errors r;
		(*in).close();
		std::cerr << i << std::endl;
		return err::ERROR_VALUE;
	}
	return err::SUCCESS;
}
void addBack(std::vector<uint8_t>& buf, int n) {
	for (int i = 0; i < n; i++) {
		buf.push_back(0);
	}
}
void convert32ToChar(std::vector<uint8_t>& buf, int32_t x, int startIndex) {
	addBack(buf, af::FourBytes);
	buf[startIndex + af::FourthByte] = (x >> 24) & 0xFF;
	buf[startIndex + af::ThirdByte] = (x >> 16) & 0xFF;
	buf[startIndex + af::SecondByte] = (x >> 8) & 0xFF;
	buf[startIndex + af::FirstByte] = x & 0xFF;
}
void convert16ToChar(std::vector<uint8_t>& buf, int16_t x, int startIndex) {
	addBack(buf, af::TwoBytes);
	buf[startIndex + af::SecondByte] = (x >> 8) & 0xFF;
	buf[startIndex + af::FirstByte] = x & 0xFF;
}
void convertStringToChar(std::vector<uint8_t>& buf, std::string x, int startIndex) {
	addBack(buf, af::FourBytes);
	for (int i = 0; i < af::FourBytes; i++) {
		buf[startIndex + i] = (uint8_t)x[i];
	}
}
void af::AudioFile::writeToFile(std::string fileName) {
	err::Errors r;
	std::vector<uint8_t> buf;
	for (int i = 0; i < samples.size(); i++) {
		convert16ToChar(buf, samples[i], i * af::TwoBytes);
	}
	std::ofstream out(fileName, std::ios::binary | std::ios_base::out | std::ios_base::app);
	if (!out) throw r.SaveFileErr;
	for (int i = 0; i < buf.size(); i++) {
		char x = (char)buf[i];
		out.write(&x, sizeof(char));
	}
	out.close();
}

int af::AudioFile::save(std::string fileName) {
	err::Errors r;
	try {
		std::vector<uint8_t> buf;
		convertStringToChar(buf, "RIFF", 0);
		if (chunkSize == 0) throw r.ChunkSizeErr;
		convert32ToChar(buf, chunkSize, 4);
		convertStringToChar(buf, "WAVE", 8);
		convertStringToChar(buf, "fmt ", 12);
		if (subChunk1Size == 0) throw r.Subchunk1SizeErr;
		convert32ToChar(buf, subChunk1Size, 16);
		if (audioFormat == 0) throw r.AudioFormatErr;
		convert16ToChar(buf, audioFormat, 20);
		if (numChannels == 0) throw r.NumChannelsErr;
		convert16ToChar(buf, numChannels, 22);
		if (sampleRate == 0) throw r.SampleRateErr;
		convert32ToChar(buf, sampleRate, 24);
		if (byteRate == 0) throw r.ByteRateErr;
		convert32ToChar(buf, byteRate, 28);
		if (BlockAlign == 0) throw r.BlockAlignErr;
		convert16ToChar(buf, BlockAlign, 32);
		if (bitsPerSample == 0) throw r.BitsPerSampleErr;
		convert16ToChar(buf, bitsPerSample, 34);
		convertStringToChar(buf, "LIST", 36);
		convert32ToChar(buf, subChunkList, 40);
		for (int i = 0; i < subChunkList / 2; i++) {
			convert16ToChar(buf, list[i], 44 + i * 2);
		}
		convertStringToChar(buf, "data", 44 + subChunkList);
		if (subChunk2Size == 0) throw r.subChunk2SizeErr;
		convert32ToChar(buf, subChunk2Size, 48 + subChunkList);
		std::ofstream out(fileName, std::ios::binary);
		for (int i = 0; i < buf.size(); i++) {
			char x = (char)buf[i];
			out.write(&x, sizeof(char));
		}
	}
	catch (std::string i) {
		std::cerr << i << std::endl;
		return err::ERROR_VALUE;
	}
	return err::SUCCESS;
}

std::vector<int16_t> af::AudioFile::getSamples() {
	return samples;
}
int af::AudioFile::getSubChunk2Size() {
	return subChunk2Size;
}
void af::AudioFile::writeNewSamples(std::vector<int16_t> samp) {
	samples = samp;
}
void af::AudioFile::closeIn() {
	in->close();
}