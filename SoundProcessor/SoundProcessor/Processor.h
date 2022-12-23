#pragma once
#include "Ñonverter.h"
#include "ConfigurationFile.h"
#include "AudioFile.h"
#include "Input.h"
#include <vector>
namespace pr {
	const int OffsetTwo = 2;
	const int OffsetOne = 1;
	int const START = 0;
	int const END = 1;
	class Processor {
	public:
		virtual void ProcType(std::vector<af::AudioFile>&, configs::ConfigurationFile&, int) = 0;
	};
	class MuteProc : public Processor {
		void ProcType(std::vector<af::AudioFile>&, configs::ConfigurationFile&, int);
	};
	class MixProc : public Processor {
		void ProcType(std::vector<af::AudioFile>&, configs::ConfigurationFile&, int);
	};
	class ReversProc : public Processor {
		void ProcType(std::vector<af::AudioFile>&, configs::ConfigurationFile&, int);
	};

	class ProcFactory {
	public:
		virtual Processor* MakeProc() = 0;
		virtual std::string GetProcName() = 0;
	};
	class MuteProcFactory : public ProcFactory {
		Processor* MakeProc();
		std::string GetProcName();
	};
	class MixProcFactory : public ProcFactory {
		Processor* MakeProc();
		std::string GetProcName();
	};
	class ReversProcFactory : public ProcFactory {
		Processor* MakeProc();
		std::string GetProcName();
	};
	int CreateFiles(np::Input, std::vector<af::AudioFile>&);
	int Processing(np::Input, std::vector<af::AudioFile>&, configs::ConfigurationFile&);
}

