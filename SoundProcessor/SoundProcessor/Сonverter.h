#pragma once

namespace con {
	class Converter {
	public:
		int start2 = 0;
		std::vector<int16_t> samples2;
		virtual int ChangeSamples(std::vector<int16_t>&, int, int) = 0;
	};
	class MuteTheInterval : public Converter {
		int ChangeSamples(std::vector<int16_t>& samples, int start, int end);
	};
	class Mixer : public Converter {
		int ChangeSamples(std::vector<int16_t>& samples1, int start1, int end1);
	};
	class Revers : public Converter {
		int ChangeSamples(std::vector<int16_t>& samples, int start, int end);
	};
	class ConverterFactory {
	public:
		virtual Converter* MakeConverter() = 0;
	};
	class MuteTheIntervalFactory : public ConverterFactory {
	public:
		Converter* MakeConverter();
	};
	class MixerFactory : public ConverterFactory {
	public:
		Converter* MakeConverter();
	};
	class ReversFactory : public ConverterFactory {
	public:
		Converter* MakeConverter();
	};
}