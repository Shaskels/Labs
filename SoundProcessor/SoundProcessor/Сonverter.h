#pragma once
#include <vector>
#include <string>
namespace con {
	const int SAMPLE_RATE = 44100;
	class Converter {
	public:
		std::vector<int16_t> samples2;
		virtual int ChangeSamples(std::vector<int16_t>&) = 0;
	};
	class MuteTheInterval : public Converter {
		int ChangeSamples(std::vector<int16_t>& samples);
	};
	class Mixer : public Converter {
		int ChangeSamples(std::vector<int16_t>& samples1);
	};
	class Revers : public Converter {
		int ChangeSamples(std::vector<int16_t>& samples);
	};
	class ConverterFactory {
	public:
		virtual Converter* MakeConverter() = 0;
		virtual std::vector<std::string> Reference() = 0;
	};
	class MuteTheIntervalFactory : public ConverterFactory {
	public:
		Converter* MakeConverter();
		std::vector<std::string> Reference();
	};
	class MixerFactory : public ConverterFactory {
	public:
		Converter* MakeConverter();
		std::vector<std::string> Reference();
	};
	class ReversFactory : public ConverterFactory {
	public:
		Converter* MakeConverter();
		std::vector<std::string> Reference();
	};
}