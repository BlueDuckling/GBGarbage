#include "timers.h"
#include "gb_cpu.h"
#include <iostream>
Timers::Timers(GbCPU* ptr)
{
	cpu_ptr = ptr;
}

void Timers::manageTIMERS(int cycles_used)
{
	manageDIV(cycles_used);
	if ((((*cpu_ptr).get_memory()[(*cpu_ptr).TAC]&0x04) >>2)==1) {
		if ((*cpu_ptr).get_memory()[(*cpu_ptr).TIMA_TIMER] < (*cpu_ptr).get_memory()[(*cpu_ptr).TMA]) {
			(*cpu_ptr).get_memory()[(*cpu_ptr).TIMA_TIMER] = (*cpu_ptr).get_memory()[(*cpu_ptr).TMA];
		}
		manageTIMA(cycles_used);
	}
}

void Timers::manageDIV(int cycles_used)
{
	DIV_counter = DIV_counter + cycles_used;
	if (DIV_counter >= GB_FREQ / DIV_FREQ) {
		int increment = DIV_counter / (GB_FREQ / DIV_FREQ);
		DIV_counter = 0;
		(*cpu_ptr).get_memory()[(*cpu_ptr).DIV_TIMER] += increment;
	}
}

void Timers::manageTIMA(int cycles_used)
{
	TIMA_counter = TIMA_counter + cycles_used;
	int mode = TIMA_FREQ_00;
	int count = 1024;
	switch (((*cpu_ptr).get_memory()[(*cpu_ptr).TAC] & 0x03)) {
	case 0:
		count = GB_FREQ/TIMA_FREQ_00;
		break;
	case 1:
		count = GB_FREQ / TIMA_FREQ_01;
		break;
	case 2:
		count = GB_FREQ / TIMA_FREQ_02;
		break;
	case 3:
		count = GB_FREQ / TIMA_FREQ_03;
		break;
	}
	if (TIMA_counter >= count) {
		int increment = TIMA_counter / count;
		unsigned char prev_tima = (*cpu_ptr).get_memory()[(*cpu_ptr).TIMA_TIMER];
		TIMA_counter = 0;
		(*cpu_ptr).get_memory()[(*cpu_ptr).TIMA_TIMER] += increment;
		if ((*cpu_ptr).get_memory()[(*cpu_ptr).TIMA_TIMER] < prev_tima) { //Desbordamiento
			(*cpu_ptr).get_memory()[(*cpu_ptr).TIMA_TIMER] = (*cpu_ptr).get_memory()[(*cpu_ptr).TMA];
			(*cpu_ptr).get_memory()[(*cpu_ptr).IF] = (*cpu_ptr).get_memory()[(*cpu_ptr).IF] | 0x04;
		}
	}

}
