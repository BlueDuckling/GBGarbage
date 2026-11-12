#pragma once
#include "gb_cpu.h"
class Timers
{
public:
	Timers(GbCPU* ptr);
	void manageTIMERS(int cycles_used);
	void manageDIV(int cycles_used);
	void manageTIMA(int cycles_used);
private:
	const int GB_FREQ = 4194304;
	const int DIV_FREQ = 16384;
	const int TIMA_FREQ_00 = 4096;
	const int TIMA_FREQ_01 = 262144;
	const int TIMA_FREQ_02 = 65536;
	const int TIMA_FREQ_03 = 16384;
	int DIV_counter = 0;
	int TIMA_counter = 0;
	GbCPU* cpu_ptr;

};

