#include "gb_cpu.h"
#include <array>
#include <iostream>
#include <cstring>
unsigned char GbCPU::memory[0xFFFF]; //65535 bytes, aka 64 mB 
GbCPU::Registers GbCPU::registers{};

GbCPU::GbCPU() {
    std::memset(memory, 0, sizeof(memory));
    memory[0xFF44] = 0x90;
    registers = { 0x01, 0, 0x13, 0, 0xD8, 0xB0, 0x01, 0x4D };
    SP = 0xFFFE;
}
unsigned char* GbCPU::get_memory(){
    unsigned char* memory_ptr = memory;
    return memory_ptr;
}


unsigned short GbCPU::get_bc() const
{
    unsigned short bc;
    bc = (registers.b << 8) | registers.c;
    return bc;
}

void GbCPU::set_bc(unsigned short virtual_register)
{
    registers.b = (virtual_register & 0XFF00) >> 8;
    registers.c = (virtual_register & 0x00FF);
}

unsigned short GbCPU::get_af() const
{
    unsigned short af;
    af = (registers.a << 8) | registers.f;
    return af;
}

void GbCPU::set_af(unsigned short virtual_register)
{
    registers.a = (virtual_register & 0XFF00) >> 8;
    registers.f = (virtual_register & 0x00F0); //se ignoran los lsb de f
}

unsigned short GbCPU::get_de()
{
   unsigned short de;
   de = (registers.d << 8) | registers.e;
   return de;
}

void GbCPU::set_de(unsigned short virtual_register)
{
    registers.d = (virtual_register & 0XFF00) >> 8;
    registers.e = (virtual_register & 0x00FF);
}

unsigned short GbCPU::get_hl()
{
    unsigned short hl;
    hl = (registers.h << 8) | registers.l;
    return hl;
}

void GbCPU::set_hl(unsigned short virtual_register)
{
    registers.h = (virtual_register & 0XFF00) >> 8;
    registers.l = (virtual_register & 0x00FF);
}

unsigned char GbCPU::get_register(unsigned char reg_dir)
{
    switch (reg_dir) {
        case 0x00:
            return registers.b;
        case 0x01:
            return registers.c;
        case 0x02:
            return registers.d;
        case 0x03:
            return registers.e;
        case 0x04:
            return registers.h;
        case 0x05:
            return registers.l;
        case 0x06:
            return memory[get_hl()];
        case 0x07:
            return registers.a;
        default:
            return registers.a;
    }
}

unsigned short GbCPU::get_register_16(unsigned char reg_dir)
{
    switch (reg_dir) {
        case 0x00:
            return get_bc();
        case 0x01:
            return get_de();
        case 0x02:
            return get_hl();
        case 0x03:
            return SP;
        default:
            return get_bc();
    }
}

unsigned short GbCPU::get_register_16MEM(unsigned char reg_dir) 
//Acceder al registro hl con este proceso incrementa/decrementa su valor tras obtener el dato
{
    switch (reg_dir) {
        case 0x00:
            return get_bc();
        case 0x01:
            return get_de();
        case 0x02:
            return manage_hl_mem16(reg_dir);
        case 0x03:
            return manage_hl_mem16(reg_dir);
        default:
            return get_bc();
    }
}
unsigned short GbCPU::manage_hl_mem16(unsigned char reg_dir)
{
    unsigned short hl = get_hl();
    unsigned short new_hl;
    switch (reg_dir) {
        case 2:
            new_hl = hl + 1;
            set_hl(new_hl);
            break;
        case 3:
            new_hl = hl - 1;
            set_hl(new_hl);
            break;
        default:
            break;
    }
    return hl;
}

unsigned short GbCPU::get_register_16STK(unsigned char reg_dir)
{
    switch (reg_dir) {
        case 0x00:
            return get_bc();
        case 0x01:
            return get_de();
        case 0x02:
            return get_hl();
        case 0x03:
            return get_af();
        }
}

void GbCPU::set_register(unsigned char reg_dir, unsigned char value)
{
    switch (reg_dir) {
        case 0x00:
            registers.b = value;
            break;
        case 0x01:
            registers.c = value;
            break;
        case 0x02:
            registers.d = value;
            break;
        case 0x03:
            registers.e = value;
            break;
        case 0x04:
            registers.h = value;
            break;
        case 0x05:
            registers.l = value;
            break;
        case 0x06:
            memory[get_hl()] = value;
            break;
        case 0x07:
            registers.a = value;
            break;
        }
}

void GbCPU::set_register_16(unsigned char reg_dir, unsigned short value)
{
    switch (reg_dir) {
        case 0x00:
            set_bc(value);
            break;
        case 0x01:
            set_de(value);
            break;
        case 0x02:
            set_hl(value);
            break;
        case 0x03:
            SP = value;
            break;
        }
}
void GbCPU::set_register_16MEM(unsigned char reg_dir, unsigned short value)
{
    switch (reg_dir) {
    case 0x00:
        set_bc(value);
        break;
    case 0x01:
        set_de(value);
        break;
    case 0x02:
        set_hl(value);
        manage_hl_mem16(reg_dir);
        break;
    case 0x03:
        set_hl(value);
        manage_hl_mem16(reg_dir);
        break;
    default:
        break;
    }
}

void GbCPU::set_register_16STK(unsigned char reg_dir, unsigned short value)
{
    switch (reg_dir) {
        case 0x00:
            set_bc(value);
            break;
        case 0x01:
            set_de(value);
            break;
        case 0x02:
            set_hl(value);
            break;
        case 0x03:
            set_af(value);
            break;
        }
}

void GbCPU::inc_pc(){
    PC += 1;
}

unsigned short GbCPU::get_pc() const
{
    return PC;
}

void GbCPU::set_pc(unsigned short pc_value)
{
    PC = pc_value;
}

bool GbCPU::get_stop() const
{
    return is_stopped;
}

bool GbCPU::is_halted() const
{
    return halted;
}

void GbCPU::resume()
{
    halted = false;
}



bool GbCPU::interrupt_requested()
{
    return IME_flag;
}

int GbCPU::cycles_used()
{
    return cycles;
}

unsigned char GbCPU::get_flags() const {
    return registers.f;
}

unsigned short GbCPU::get_sp() const
{
    return SP;
}

void GbCPU::set_sp(unsigned short sp_value)
{
    SP = sp_value;
}

