#pragma once
#include"gb_cpu.h"
class PPU
{
public:
	PPU(GbCPU* ptr);

private:
	GbCPU* cpu_ptr;
};

