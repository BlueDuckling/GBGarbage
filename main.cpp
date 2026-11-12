#include "gb_cpu.h"
#include "timers.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip> // Para std::hex
#include <sstream>

static std::string hex8(uint8_t v) {
	std::stringstream ss;
	ss << std::hex << std::uppercase << std::setw(2)
		<< std::setfill('0') << (int)v;
	return ss.str();
}

static std::string hex16(uint16_t v) {
	std::stringstream ss;
	ss << std::hex << std::uppercase << std::setw(4)
		<< std::setfill('0') << v;
	return ss.str();
}
static void logMessage(const std::string& message) {
	std::ofstream logfile("log.txt", std::ios_base::app);
	if (logfile.is_open()) {
		logfile << message << std::endl;
	}
	else {
		std::cerr << "Error abriendo el archivo de log" << std::endl;
	}
}






void loadRom(unsigned char* mem_ptr);
void interruptHandler(GbCPU* cpu_ptr);
static void logMessage(const std::string& message);
int debug_counter = 0;
int main() {
	GbCPU gb_cpu;
	Timers timers(&gb_cpu);
	unsigned char* memory = gb_cpu.get_memory();
	loadRom(memory);
	gb_cpu.set_pc(gb_cpu.ROM_BANK_00_START);
	//Log
	std::stringstream ss;
	
	//gb_cpu.set_pc(0x0);
	std::cout << "Rom cargada" << std::endl;
	while (true) {
		while (!gb_cpu.is_halted()) {

			/*char buf[256]; // suficiente para toda la l�nea

			uint16_t pc = gb_cpu.get_pc();
			uint16_t sp = gb_cpu.get_sp();

			uint8_t a = gb_cpu.get_register(7);
			uint8_t f = gb_cpu.get_flags();
			uint8_t b = gb_cpu.get_register(0);
			uint8_t c = gb_cpu.get_register(1);
			uint8_t d = gb_cpu.get_register(2);
			uint8_t e = gb_cpu.get_register(3);
			uint8_t h = gb_cpu.get_register(4);
			uint8_t l = gb_cpu.get_register(5);

			uint8_t m0 = memory[pc];
			uint8_t m1 = memory[pc + 1];
			uint8_t m2 = memory[pc + 2];
			uint8_t m3 = memory[pc + 3];

			snprintf(buf, sizeof(buf),
				"A:%02X F:%02X B:%02X C:%02X "
				"D:%02X E:%02X H:%02X L:%02X "
				"SP:%04X PC:%04X "
				"PCMEM:%02X,%02X,%02X,%02X",
				a, f, b, c, d, e, h, l,
				sp, pc,
				m0, m1, m2, m3
			);

			logMessage(buf);*/



			if ((*(memory + gb_cpu.get_pc()) == 0xCB)) {
				gb_cpu.inc_pc();
				unsigned char row = (*(memory + gb_cpu.get_pc()) & 0xF0) >> 4;
				unsigned char column = (*(memory + gb_cpu.get_pc()) & 0x0F);
				gb_cpu.inc_pc();
				(gb_cpu.*(gb_cpu.prefix_instructions[row][column]))();
			}
			else {
				unsigned char row = (*(memory + gb_cpu.get_pc()) & 0xF0) >> 4;
				unsigned char column = (*(memory + gb_cpu.get_pc()) & 0x0F);
				gb_cpu.inc_pc();
				(gb_cpu.*(gb_cpu.instructions[row][column]))();
				if (row != 0 || column != 0) {
					//std::cout << std::hex << (int)row << " " << (int)column << std::endl;
				}
			}
			interruptHandler(&gb_cpu);
			timers.manageTIMERS(gb_cpu.cycles_used());

			//
			if (*(memory + 0xff02) == 0x81) {
				char c = (*(memory + 0xff01));
				std::cout << c;
				(*(memory + 0xff02)) = 0x0;

			}
		}
		timers.manageTIMERS(1);
		if (memory[gb_cpu.IF] != 0){
			interruptHandler(&gb_cpu);
			gb_cpu.resume();
		}

	}
}


//Carga la rom seleccionada en memoria
void loadRom(unsigned char* mem_ptr)
{

	std::ifstream gb_rom("roms/02-interrupts.gb", std::ios::binary);
	if (!gb_rom.is_open()) {
		std::cerr << "Error al abrir el archivo" << std::endl;
	}
	gb_rom.clear();
	gb_rom.seekg(0, std::ios::end);
	long rom_size = gb_rom.tellg();
	std::cout << rom_size << std::endl;

	gb_rom.seekg(0, std::ios::beg);
	//Las test rom sobrescribel el bootrom, asi que empieza en i=0. Luego camabiar a i=0x100
	for (long i=0; i < rom_size; ++i) {
		//std::cout << (int)gb_rom.peek() << std::endl;
		*(mem_ptr+i) = (char)gb_rom.get();
		//std::cout << i+100 << " " << (int)*(mem_ptr + i) << std::endl;
	}
	
	gb_rom.close();
}

void interruptHandler(GbCPU* cpu_ptr)
{
	unsigned char IF = (*cpu_ptr).get_memory()[(*cpu_ptr).IF];
	unsigned char IE = (*cpu_ptr).get_memory()[(*cpu_ptr).IE];
	if ((*cpu_ptr).interrupt_requested() && (*cpu_ptr).get_memory()[(*cpu_ptr).IE] != 0x00) {
		//VBlank
		if ((IE & 0b00000001) == 1 && (IF & 0b00000001) == 1) {
			//Se guarda el valor del PC en la pila
			unsigned char low_reg = (*cpu_ptr).get_pc() & 0x00FF;
			unsigned char high_reg = (((*cpu_ptr).get_pc() & 0xFF00) >> 8);
			(*cpu_ptr).set_sp((*cpu_ptr).get_sp() - 1);
			(*cpu_ptr).get_memory()[(*cpu_ptr).get_sp()] = high_reg;
			(*cpu_ptr).set_sp((*cpu_ptr).get_sp() - 1);
			(*cpu_ptr).get_memory()[(*cpu_ptr).get_sp()] = low_reg;
			//Salto a la posicion correspondiente:
			(*cpu_ptr).set_pc(0x40);
			(*cpu_ptr).get_memory()[(*cpu_ptr).IF] = (IF & 0b11111110); //Se baja el flag
		}
		else if (((IE & 0b00000010) >> 1) == 1&&((IF & 0b00000010)>>1) == 1) {
			//Se guarda el valor del PC en la pila
			unsigned char low_reg = (*cpu_ptr).get_pc() & 0x00FF;
			unsigned char high_reg = (((*cpu_ptr).get_pc() & 0xFF00) >> 8);
			(*cpu_ptr).set_sp((*cpu_ptr).get_sp() - 1);
			(*cpu_ptr).get_memory()[(*cpu_ptr).get_sp()] = high_reg;
			(*cpu_ptr).set_sp((*cpu_ptr).get_sp() - 1);
			(*cpu_ptr).get_memory()[(*cpu_ptr).get_sp()] = low_reg;
			//Salto a la posicion correspondiente:
			(*cpu_ptr).set_pc(0x48);
			(*cpu_ptr).get_memory()[(*cpu_ptr).IF] = (IF & 0b11111101); //Se baja el flag
		}
		else if (((IE & 0b00000100) >> 2) == 1&&((IF & 0b00000100) >> 2) == 1) {
			//Se guarda el valor del PC en la pila
			unsigned char low_reg = (*cpu_ptr).get_pc() & 0x00FF;
			unsigned char high_reg = (((*cpu_ptr).get_pc() & 0xFF00) >> 8);
			(*cpu_ptr).set_sp((*cpu_ptr).get_sp() - 1);
			(*cpu_ptr).get_memory()[(*cpu_ptr).get_sp()] = high_reg;
			(*cpu_ptr).set_sp((*cpu_ptr).get_sp() - 1);
			(*cpu_ptr).get_memory()[(*cpu_ptr).get_sp()] = low_reg;
			//Salto a la posicion correspondiente:
			(*cpu_ptr).set_pc(0x50);
			(*cpu_ptr).get_memory()[(*cpu_ptr).IF] = (IF & 0b11111011); //Se baja el flag
		}
		else if (((IE & 0b00001000) >> 3) == 1&&((IF & 0b00001000) >> 3) == 1) {
			//Se guarda el valor del PC en la pila
			unsigned char low_reg = (*cpu_ptr).get_pc() & 0x00FF;
			unsigned char high_reg = (((*cpu_ptr).get_pc() & 0xFF00) >> 8);
			(*cpu_ptr).set_sp((*cpu_ptr).get_sp() - 1);
			(*cpu_ptr).get_memory()[(*cpu_ptr).get_sp()] = high_reg;
			(*cpu_ptr).set_sp((*cpu_ptr).get_sp() - 1);
			(*cpu_ptr).get_memory()[(*cpu_ptr).get_sp()] = low_reg;
			//Salto a la posicion correspondiente:
			(*cpu_ptr).set_pc(0x50);
			(*cpu_ptr).get_memory()[(*cpu_ptr).IF] = (IF & 0b11110111); //Se baja el flag
		}
		else if (((IE & 0b00010000) >> 4) == 1&&((IF & 0b00010000) >> 4) == 1) {
			//Se guarda el valor del PC en la pila
			unsigned char low_reg = (*cpu_ptr).get_pc() & 0x00FF;
			unsigned char high_reg = (((*cpu_ptr).get_pc() & 0xFF00) >> 8);
			(*cpu_ptr).set_sp((*cpu_ptr).get_sp() - 1);
			(*cpu_ptr).get_memory()[(*cpu_ptr).get_sp()] = high_reg;
			(*cpu_ptr).set_sp((*cpu_ptr).get_sp() - 1);
			(*cpu_ptr).get_memory()[(*cpu_ptr).get_sp()] = low_reg;
			//Salto a la posicion correspondiente:
			(*cpu_ptr).set_pc(0x58);
			(*cpu_ptr).get_memory()[(*cpu_ptr).IF] = (IF & 0b11101111); //Se baja el flag
		}
		else if (((IE & 0b00100000) >> 5) == 1&&((IF & 0b00100000) >> 5) == 1) {
			//Se guarda el valor del PC en la pila
			unsigned char low_reg = (*cpu_ptr).get_pc() & 0x00FF;
			unsigned char high_reg = (((*cpu_ptr).get_pc() & 0xFF00) >> 8);
			(*cpu_ptr).set_sp((*cpu_ptr).get_sp() - 1);
			(*cpu_ptr).get_memory()[(*cpu_ptr).get_sp()] = high_reg;
			(*cpu_ptr).set_sp((*cpu_ptr).get_sp() - 1);
			(*cpu_ptr).get_memory()[(*cpu_ptr).get_sp()] = low_reg;
			//Salto a la posicion correspondiente:
			(*cpu_ptr).set_pc(0x60);
			(*cpu_ptr).get_memory()[(*cpu_ptr).IF] = (IF & 0b11011111); //Se baja el flag
		}
	}
}

/*static void logMessage(const std::string& message) {
	std::ofstream logfile("log.txt", std::ios_base::app); // Abrir en modo "append"
	if (logfile.is_open()) {
		logfile << message << std::endl;
		logfile.close();
	}
	else {
		std::cerr << "Error abriendo el archivo de log" << std::endl;
	}
}*/