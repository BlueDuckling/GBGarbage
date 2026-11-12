#include "gb_cpu.h"
#include <iostream>
//TODO HALT


//     ┌-> Carry
//   ┌-+> Subtraction
//   | |
//  1111 0000
//  | |
//  └-+> Zero
//    └-> Half Carry

void GbCPU::set_flags_add_sp_8(unsigned short target, signed char value, unsigned char f_reg)
{
    unsigned short result = target + value;
    unsigned char upper_nibble_target = target & 0x0F;
    unsigned char upper_nibble_value = value & 0x0F;
    if ((target & 0xFF) + (value & 0xFF) > 0xFF) {
        f_reg = f_reg | 0b00010000;
    }
    if (upper_nibble_value + upper_nibble_target > 0x0F) {
        f_reg = f_reg | 0b00100000;
    }
    registers.f = f_reg;
}



void GbCPU::set_flags_add_8(unsigned char target, unsigned char value, unsigned char f_reg)
{
    unsigned char result = target + value;
    unsigned char upper_nibble_target = target & 0x0F;
    unsigned char upper_nibble_value = value & 0x0F;
    if (result == 0) {
        f_reg = f_reg | 0b10000000;

    }
    else {
        f_reg = f_reg & 0b01111111;
    }
    if (result < target) {
        f_reg = f_reg | 0b00010000;
    }
    else {
        f_reg = f_reg & 0b11101111;
    }
    if (upper_nibble_value + upper_nibble_target > 0x0F) {
        f_reg = f_reg | 0b00100000;
    }
    registers.f = f_reg;
}

void GbCPU::set_flags_adc(unsigned char target, unsigned char value, unsigned char f_reg) {
    unsigned char result = target + value+ get_carry();
    unsigned char lower_nibble_target = (target & 0x0F);
    unsigned char lower_nibble_value = (value & 0x0F);
    if (result == 0) {
        f_reg = f_reg | 0b10000000;

    }
    else {
        f_reg = f_reg & 0b01111111;
    }
    if (target + value + get_carry() > 0xFF) {
        f_reg = f_reg | 0b00010000;
    }
    else {
        f_reg = f_reg & 0b11101111;
    }
    if (lower_nibble_target + lower_nibble_value + get_carry() > 0x0F) {
        f_reg = f_reg | 0b00100000;
    }
    else {
        f_reg = f_reg & 0b11011111;
    }
    registers.f = f_reg & 0b10111111;
}

void GbCPU::set_flags_sbc(unsigned char target, unsigned char value, unsigned char f_reg)
{
    unsigned char result = target - value - get_carry();
    if (result == 0) {
        f_reg = f_reg | 0b10000000;

    }
    else {
        f_reg = f_reg & 0b01111111;
    }
    if (((target & 0x0F) - (value & 0x0F) - get_carry()) < 0) {
        f_reg = f_reg | 0b00100000;
    }
    else {
        f_reg = f_reg & 0b11011111;
    }
    if (target - value - get_carry() < 0) {
        f_reg = f_reg | 0b00010000;
    }
    else {
        f_reg = f_reg & 0b11101111;
    }
    registers.f = f_reg | 0b01000000;
}

void GbCPU::set_flags_inc_8(unsigned char target, unsigned char f_reg) {
    unsigned char result = target + 1;
    unsigned char upper_nibble_target = target & 0x0F;
    unsigned char upper_nibble_value = 1 & 0x0F;
    if (result == 0) {
        f_reg = f_reg | 0b10000000;

    }
    else {
        f_reg = f_reg & 0b01111111;
    }
    if (upper_nibble_value + upper_nibble_target > 0x0F) {
        f_reg = f_reg | 0b00100000;
    }
    else {
        f_reg = f_reg & 0b11011111;
    }
    registers.f = f_reg & 0b10111111;

}
void GbCPU::set_flags_add_16(unsigned short target, unsigned short value, unsigned char f_reg)
{
    unsigned short result = target + value;
    unsigned short upper_nibble_target = target & 0x0FFF;
    unsigned short upper_nibble_value = value & 0x0FFF;
    if (result < target) {
        f_reg = f_reg | 0b00010000;
    }
    else {
        f_reg = f_reg & 0b11101111;
    }
    if (upper_nibble_value + upper_nibble_target > 0x0FFF) {
        f_reg = f_reg | 0b00100000;
    }
    else {
        f_reg = f_reg & 0b11011111;
    }
    registers.f = f_reg & 0b10111111;
}

void GbCPU::set_flags_and(unsigned char result, unsigned char f_reg)
{
    f_reg = f_reg | 0b00100000;
    if (result == 0) {
        f_reg = f_reg | 0b10000000;

    }
    registers.f = f_reg;
}
void GbCPU::set_flags_sub_8(unsigned char target, unsigned char value, unsigned char f_reg)
{
    f_reg = f_reg | 0b01000000;
    unsigned char result = target - value;
    unsigned char lower_nibble_target = (target & 0x0F);
    unsigned char lower_nibble_value = (value) & 0x0F;
    if (result == 0) {
        f_reg = f_reg | 0b10000000;
    }
    else {
        f_reg = f_reg & 0b01111111;
    }
    if (value > target) {
        f_reg = f_reg | 0b00010000;
    }
    else {
        f_reg = f_reg & 0b11101111;
    }
    if (lower_nibble_target<lower_nibble_value) {
        f_reg = f_reg | 0b00100000;
    }
    else {
        f_reg = f_reg & 0b11011111;
    }
    f_reg = f_reg | 0b01000000;
    registers.f = f_reg;
}
void GbCPU::set_flags_bit_u3(unsigned char test_bit)
{
    if (test_bit == 0) {
        registers.f = registers.f | 0b10000000;
    }
    else { registers.f = registers.f & 0b01111111; }
    registers.f = registers.f | 0b00100000;
    registers.f = registers.f & 0b10111111;
}

void GbCPU::set_flags_dec_8(unsigned char target, unsigned char f_reg) {
    f_reg = f_reg | 0b01000000;
    unsigned char result = target - 1;
    unsigned char lower_nibble_target = (target & 0x0F);
    unsigned char lower_nibble_result= (target-1) & 0x0F;
    if (result == 0) {
        f_reg = f_reg | 0b10000000;

    }
    else {
        f_reg = f_reg & 0b01111111;
    }
    if (lower_nibble_target == 0 && (lower_nibble_result&0b00001000)== 0x08) {
        f_reg = f_reg | 0b00100000;
    }
    else {
        f_reg = f_reg & 0b11011111;
    }
    registers.f = f_reg | 0b01000000;
}

unsigned char GbCPU::get_carry() const
{
    return (registers.f & 0b00010000) >> 4;
}

unsigned char GbCPU::get_half_carry() const
{
    return (registers.f & 0b00100000) >> 5;
}

unsigned char GbCPU::get_sub() const
{
    return (registers.f & 0b01000000) >> 6;
}

unsigned char GbCPU::get_zero() const
{
    return (registers.f & 0b10000000) >> 7;
}

//INSTRUCCIONES

void GbCPU::ADC_R8()
{
    unsigned char reg_dir = memory[PC - 1] & 0x07;
    unsigned char reg_a = registers.a;
    unsigned char reg_x = get_register(reg_dir);
    registers.a = reg_a + reg_x + get_carry();
    set_flags_adc(reg_a, reg_x, registers.f); 
    reg_dir == 6 ? cycles = 8 : cycles = 4;
}

void GbCPU::ADC_N8()
{
    unsigned char value = memory[PC];
    unsigned char reg_a = registers.a;
    registers.a = reg_a+value+get_carry();
    set_flags_adc(reg_a, value, registers.f);
    PC = PC + 1;
    cycles = 8;
}

void GbCPU::ADD_R8()
{
    unsigned char reg_dir = memory[PC - 1] & 0x07;
    unsigned char reg_a = registers.a;
    unsigned char reg_x = get_register(reg_dir);
    set_flags_add_8(reg_a, reg_x, 0);
    reg_a += reg_x;
    registers.a = reg_a;
    reg_dir == 6 ? cycles = 8 : cycles = 4;
}

void GbCPU::ADD_N8()
{
    unsigned char value = memory[PC];
    unsigned char reg_a = registers.a;
    set_flags_add_8(reg_a, value, 0);
    reg_a += value;
    registers.a = reg_a;
    PC = PC + 1;
    cycles = 8;
}

void GbCPU::ADD_HL_R16()
{
    unsigned char reg_dir = (memory[PC - 1] & 0x30) >> 4;
    unsigned short hl = get_hl();
    unsigned short r16 = get_register_16(reg_dir);
    set_flags_add_16(hl, r16, registers.f);
    hl = hl + r16;
    set_hl(hl);
    cycles = 8;
}

void GbCPU::ADD_SP_E8() //Se supone que value es signed, pero igual imponerlo desde C++ da problemas, no se
{
    signed char value = memory[PC];
    unsigned short stack_pointer_lower = SP & 0x0F;
    set_flags_add_sp_8(SP, value, 0);
    SP += value;
    PC = PC + 1;
    cycles = 16;
}

void GbCPU::AND_A_R8()
{
    unsigned char reg_dir = memory[PC - 1] & 0x07;
    unsigned char reg_a = registers.a;
    unsigned char reg_x = get_register(reg_dir);
    unsigned char result = reg_a & reg_x;
    set_flags_and(result, 0);
    registers.a = result;
    reg_dir == 6 ? cycles = 8 : cycles = 4;
}

void GbCPU::AND_A_N8()
{
    unsigned char value = memory[PC];
    unsigned char reg_a = registers.a;
    unsigned char result = reg_a & value;
    set_flags_and(result, 0);
    registers.a = result;
    PC = PC + 1;
    cycles = 8;
}

void GbCPU::BIT_U3()
{
    unsigned char reg_dir = memory[PC - 1] & 0x07;
    unsigned char u3_index = (memory[PC - 1] & 0x38) >> 3;
    unsigned char reg_x = get_register(reg_dir);
    unsigned char test_bit = (reg_x >> u3_index) & 0x01;
    set_flags_bit_u3(test_bit);
    reg_dir == 6 ? cycles = 12 : cycles = 8;
}

typedef enum Condition { NZ, Z, NC, C } Condition;

Condition get_condition(unsigned char cond_index)
{
    Condition cc_array[4] = { NZ,Z,NC,C };
    return cc_array[cond_index];
}

void GbCPU::CALL_N16()
{
    PC = PC + 2;
    unsigned char low_reg = PC & 0x00FF;
    unsigned char high_reg = ((PC & 0xFF00) >> 8);
    SP = SP - 1;
    memory[SP] = high_reg;
    SP = SP - 1;
    memory[SP] = low_reg;
    PC = memory[PC-2] | (memory[PC - 1]<<8);
    cycles = 24;
}

void GbCPU::CALL_CC_N16()
{
    unsigned char cc_index = (memory[PC - 1] & 0x18) >> 3;
    Condition cc = get_condition(cc_index);
    switch (cc) {
    case NZ:
        if (get_zero() == 0) {
            CALL_N16();
        }
        else{ PC = PC + 2; }
        break;
    case Z:
        if (get_zero() == 1) {
            CALL_N16();
        }
        else { PC = PC + 2; }
        break;
    case NC:
        if (get_carry() == 0) {
            CALL_N16();
        }
        else { PC = PC + 2; }
        break;
    case C:
        if (get_carry() == 1) {
            CALL_N16();
        }
        else { PC = PC + 2; }
        break;
    default:
        PC = PC + 2;
        cycles = 12;
        break;
    }
    
}

void GbCPU::CCF()
{
    unsigned char f_reg = registers.f;
    f_reg = (f_reg ^ 0b00010000) & 0b10010000;
    registers.f = f_reg;
    cycles = 4;
}

void GbCPU::CP_A_R8()
{
    unsigned char reg_dir = memory[PC - 1] & 0x07;
    unsigned char reg_a = registers.a;
    unsigned char reg_x = get_register(reg_dir);
    set_flags_sub_8(reg_a, reg_x, registers.f);
    reg_dir == 6 ? cycles = 8 : cycles = 4;
}

void GbCPU::CP_A_N8()
{
    unsigned char value = memory[PC];
    unsigned char reg_a = registers.a;
    set_flags_sub_8(reg_a, value, registers.f);
    PC = PC + 1;
    cycles = 8;
}

void GbCPU::CPL()
{
    registers.a = ~registers.a;
    registers.f = registers.f | 0b01100000;
    cycles = 4;
}

void GbCPU::DAA()
{
    unsigned char sub_flag = get_sub();
    unsigned char carry_flag = get_carry();
    unsigned char half_flag = get_half_carry();
    unsigned char adjustment = 0;
    unsigned char reg_a = registers.a;
    if (sub_flag == 1) {
        if (half_flag == 1) {
            adjustment += 0x06;
        }
        if (carry_flag == 1) {
            adjustment += 0x60;
        }
        reg_a = reg_a - adjustment;
    }
    else {
        if (half_flag == 1 || (reg_a & 0x0F) > 0x09) {
            adjustment += 0x06;
        }
        if (carry_flag == 1 || reg_a > 0x0099) {
            adjustment += 0x60;
            registers.f = registers.f | 0b00010000;
        }
        else { registers.f = registers.f & 0b11101111; }
        reg_a = reg_a + adjustment;
    }
    registers.f = registers.f & 0b11011111;
    if(reg_a == 0){ registers.f = registers.f | 0b10000000;}
    else { registers.f = registers.f & 0b01111111; }
    registers.a = reg_a;
    cycles = 4;
}

void GbCPU::DEC_R8()
{
    unsigned char reg_dir = (memory[PC - 1] & 0x38) >> 3;
    unsigned char reg_x = get_register(reg_dir);
    set_flags_dec_8(reg_x, registers.f);
    reg_x = reg_x - 1;
    set_register(reg_dir, reg_x);
    reg_dir == 6 ? cycles = 12 : cycles = 4;
}

//La docu indica que DEC_R16 no afecta a las flags
void GbCPU::DEC_R16()
{
    unsigned char reg_dir = (memory[PC - 1] & 0x30) >> 4;
    unsigned short reg_x = get_register_16(reg_dir);
    reg_x = reg_x - 1;
    set_register_16(reg_dir, reg_x);
    cycles = 8;
}

void GbCPU::DI()
{
    IME_flag = 0;
    cycles = 4;
}

void GbCPU::EI()
{
    IME_flag = 1;
    cycles == 0? cycles = 4 :cycles = cycles + 4;
}

void GbCPU::HALT()
{
    halted = true;
}

void GbCPU::INC_R8()
{
    unsigned char reg_dir = (memory[PC - 1] & 0x38) >> 3;
    unsigned char reg_x = get_register(reg_dir);
    set_flags_inc_8(reg_x, get_flags());
    reg_x = reg_x + 1;
    set_register(reg_dir, reg_x);
    reg_dir == 6 ? cycles = 12 : cycles = 4;
}

//La docu indica que DEC_R16 no afecta a las flags
void GbCPU::INC_R16()
{
    unsigned char reg_dir = (memory[PC - 1] & 0x30) >> 4;
    unsigned short reg_x = get_register_16(reg_dir);
    reg_x = reg_x + 1;
    set_register_16(reg_dir, reg_x);
    cycles = 8;
}

void GbCPU::JP_N16()
{
    unsigned short value = (memory[PC + 1] << 8) | memory[PC];     //Little endian
    PC = value;
    cycles = 4;
}

void GbCPU::JP_HL()
{
    unsigned short value = get_hl();
    PC = value;
    cycles = 12;
}

void GbCPU::JP_CC_N16()
{
    unsigned char cc_index = (memory[PC - 1] & 0x18) >> 3;
    unsigned short value = (memory[PC + 1] << 8) | memory[PC];    //Little endian
    Condition cc = get_condition(cc_index);
    switch (cc) {
        case NZ:
            if (get_zero() == 0) {
                PC = value;
                cycles = 16;
            }
            else { PC = PC + 2; cycles = 12; }
            break;
        case Z:
            if (get_zero() == 1) {
                PC = value;
                cycles = 16;
            }
            else { PC = PC + 2; cycles = 12; }
            break;
        case NC:
            if (get_carry() == 0) {
                PC = value;
                cycles = 16;
            }
            else { PC = PC + 2; cycles = 12; }
            break;
        case C:
            if (get_carry() == 1) {
                PC = value;
                cycles = 16;
            }
            else { PC = PC + 2; cycles = 12; }
            break;
        default:
            PC = PC + 2;
            cycles = 12;
    }
}

void GbCPU::JR_N16()
{
    signed char offset = memory[PC]+1; //Quiza hay que sumarle 1 al offset, no se
    PC = PC + offset;
    cycles = 4;
}

void GbCPU::JR_CC_N16()
{
    unsigned char cc_index = (memory[PC - 1] & 0x18) >> 3;
    signed char offset = memory[PC];
    PC = PC + 1; //El salto se hace despues de la instruiccion entera (PC +2 + imm8)
    Condition cc = get_condition(cc_index);
    switch (cc) {
        case NZ:
            if (get_zero() == 0) {
                PC = PC + offset;
                cycles = 12;
            }
            else { cycles = 8; }
            break;
        case Z:
            if (get_zero() == 1) {
                PC = PC + offset;
                cycles = 12;
            }
            else { cycles = 8; }
            break;
        case NC:
            if (get_carry() == 0) {
                PC = PC + offset;
                cycles = 12;
            }
            else { cycles = 8; }
            break;
        case C:
            if (get_carry() == 1) {
                PC = PC + offset;
                cycles = 12;
            }
            else { cycles = 8; }
            break;
        default:
            PC = PC + offset;
            cycles = 8;
            break;
    }
}

void GbCPU::LD_R8_R8()
{
    unsigned char source_dir = memory[PC - 1] & 0x07;
    unsigned char destination_dir = (memory[PC - 1] & 0x38) >> 3;
    unsigned char source_reg = get_register(source_dir);
    if (source_dir == destination_dir) { NOP();}
    else{ set_register(destination_dir, source_reg); }
    source_dir == 6 ? cycles = 8 : cycles = 4;
    destination_dir == 6 ? cycles = 8 : cycles = 4;
}

void GbCPU::LD_R8_N8()
{
    unsigned char value = memory[PC];
    unsigned char reg_dir = (memory[PC - 1] & 0x38) >> 3;
    set_register(reg_dir, value);
    PC = PC + 1;
    reg_dir == 6 ? cycles = 12 : cycles = 8;
}

void GbCPU::LD_R16_N16()
{
    unsigned char reg_dir = (memory[PC - 1] & 0x30) >> 4;
    unsigned short value = (memory[PC + 1] << 8) | memory[PC];
    set_register_16(reg_dir, value);
    PC = PC + 2;
    cycles = 12;
}

void GbCPU::LD_R16_A()
{
    unsigned char reg_dir = (memory[PC - 1] & 0x30) >> 4;
    unsigned short memory_dir = get_register_16MEM(reg_dir);
    memory[memory_dir] = registers.a;
    cycles = 8;
}

void GbCPU::LD_N16_A()
{
    unsigned short memory_dir = (memory[PC + 1] << 8) | memory[PC];
    memory[memory_dir] = registers.a;
    PC = PC + 2;
    cycles = 16;
}

void GbCPU::LDH_N16_A()
{
    unsigned short offset = memory[PC];
    unsigned short memory_dir = 0xFF00 + offset;
    memory[memory_dir] = registers.a;
    PC = PC + 1;
    cycles = 12;
}

void GbCPU::LDH_C_A()
{
    unsigned short memory_dir = 0xFF00 + registers.c;
    memory[memory_dir] = registers.a;
    cycles = 8;
}

void GbCPU::LD_A_R16MEM()
{
    unsigned char reg_dir = (memory[PC - 1] & 0x30) >> 4;
    unsigned short memory_dir = get_register_16MEM(reg_dir);
    registers.a = memory[memory_dir];
    cycles = 8;
}

void GbCPU::LD_A_N16()
{
    unsigned short memory_dir = (memory[PC + 1] << 8) | memory[PC];
    registers.a = memory[memory_dir];
    PC = PC + 2;
    cycles = 16;
}

void GbCPU::LDH_A_N16()
{
    unsigned short offset = memory[PC];
    unsigned short memory_dir = 0xFF00 + offset;
    registers.a = memory[memory_dir];
    PC = PC + 1;
    cycles = 12;
}

void GbCPU::LDH_A_C()
{
    unsigned short memory_dir = 0xFF00 + registers.c;
    registers.a = memory[memory_dir];
    cycles = 8;
}

void GbCPU::LD_N16_SP()
{
    unsigned short memory_dir = (memory[PC + 1] << 8) | memory[PC];
    unsigned short value = SP & 0xFF;
    memory[memory_dir] = value;
    value = SP >> 8;
    memory[memory_dir + 1] = value;
    PC = PC + 2;
    cycles = 20;
}

void GbCPU::LD_HL_SP_E8()
{
    signed char value = memory[PC];
    unsigned short sp_value = SP;
    unsigned short new_sp = sp_value + value;
    set_flags_add_sp_8(sp_value, value, 0);
    //SP = new_sp;
    set_hl(new_sp);
    PC = PC + 1;
    cycles = 12;
}

void GbCPU::LD_SP_HL()
{
    SP = get_hl();
    cycles = 8;
}

void GbCPU::NOP()
{
    cycles = 4;
}

void GbCPU::OR_A_R8()
{
    unsigned char reg_dir = memory[PC - 1] & 0x07;
    unsigned char reg_a = registers.a;
    unsigned char reg_x = get_register(reg_dir);
    reg_a = reg_a | reg_x;
    if (reg_a == 0) { registers.f = 0x80; }
    else { registers.f = 0; }
    registers.a = reg_a;
    reg_dir == 6 ? cycles = 8 : cycles = 4;
}

void GbCPU::OR_A_N8()
{
    unsigned char value = memory[PC];
    unsigned char reg_a = registers.a;
    reg_a = reg_a | value;
    if (reg_a == 0) { registers.f = 0x80; }
    else { registers.f = 0; }
    registers.a = reg_a;
    cycles = 8;
    PC = PC + 1;
}

void GbCPU::POP_R16()
{
    unsigned char reg_dir = (memory[PC - 1] & 0x30) >> 4;
    unsigned char low_reg = memory[SP];
    SP = SP + 1;
    unsigned char high_reg = memory[SP];
    SP = SP + 1;
    unsigned short value = (high_reg<<8) | low_reg;
    //if (value == 0x9001) { value = 0x9000; }//Debugging
    set_register_16STK(reg_dir, value);
    cycles = 12;
}

void GbCPU::PUSH_R16()
{
    unsigned char reg_dir = (memory[PC - 1] & 0x30) >> 4;
    unsigned short value = get_register_16STK(reg_dir);
    unsigned char low_reg = value & 0x00FF;
    unsigned char high_reg = (value & 0xFF00)>>8;
    SP = SP - 1;
    memory[SP] = high_reg;
    SP = SP - 1;
    memory[SP] = low_reg;
    cycles = 16;
}

void GbCPU::RES_U3_R8()                         //Instruccion de prefijo
{
    unsigned char reg_dir = memory[PC - 1] & 0x07;
    unsigned char bit_number = (memory[PC - 1] & 0x38) >> 3;
    unsigned char reg_x = get_register(reg_dir);
    unsigned char mask = ~(0x01 << bit_number);
    reg_x = reg_x & mask;
    set_register(reg_dir, reg_x);
    reg_dir == 6 ? cycles = 16 : cycles = 8;
}

void GbCPU::RET()
{
    unsigned char low_reg = memory[SP];
    SP = SP + 1;
    unsigned char high_reg = memory[SP];
    SP = SP + 1;
    unsigned short value = (high_reg << 8)| low_reg;
    PC = value;
    cycles = 16;
}

void GbCPU::RET_CC()
{
    unsigned char cc_index = (memory[PC - 1] & 0x18) >> 3;
    Condition cc = get_condition(cc_index);
    switch (cc) {
        case NZ:
            if (get_zero() == 0) {
                RET();
                cycles = 20;
            }
            else { cycles = 8; }
            break;
        case Z:
            if (get_zero() == 1) {
                RET();
                cycles = 20;
            }
            else { cycles = 8; }
            break;
        case NC:
            if (get_carry() == 0) {
                RET();
                cycles = 20;
            }
            else { cycles = 8; }
            break;
        case C:
            if (get_carry() == 1) {
                RET();
                cycles = 20;
            }
            else { cycles = 8; }
            break;
        default:
            break;
            cycles = 8;
        }
}

void GbCPU::RETI()
{ 
    RET();
    EI();
    cycles = cycles + 4;
}

void GbCPU::RL_R8()             //Funcion de prefijo
{
    unsigned char reg_dir = memory[PC - 1] & 0x07;
    unsigned char reg_x = get_register(reg_dir);
    unsigned char carry = get_carry();
    unsigned char next_carry = (reg_x & 0x80) >> 7;
    reg_x = ((reg_x & 0x7F) << 1) | carry;
    registers.f = 0 | (next_carry << 4);
    if (reg_x == 0) { registers.f = registers.f | 0x80; }
    set_register(reg_dir, reg_x);
    reg_dir == 6 ? cycles = 16 : cycles = 8;
}

void GbCPU::RLA()
{
    unsigned char reg_a = registers.a;
    unsigned char carry = get_carry();
    unsigned char next_carry = (reg_a & 0x80) >> 7;
    reg_a = ((reg_a & 0x7F) << 1) | carry;
    registers.f = next_carry << 4;
    registers.a = reg_a;
    cycles = 4;
}

void GbCPU::RLC_R8()                              //Funcion de prefijo
{
    unsigned char reg_dir = memory[PC - 1] & 0x07;
    unsigned char reg_x = get_register(reg_dir);
    unsigned char next_carry = (reg_x & 0x80) >> 7;
    reg_x = ((reg_x & 0x7F) << 1) | next_carry;
    registers.f = 0 | (next_carry << 4);
    if (reg_x == 0) { registers.f = registers.f | 0x80; }
    set_register(reg_dir, reg_x);
    reg_dir == 6 ? cycles = 12 : cycles = 8;
}

void GbCPU::RLC_A()
{
    unsigned char reg_a = registers.a;
    unsigned char next_carry = (reg_a & 0x80) >> 7;
    reg_a = ((reg_a & 0x7F) << 1) | next_carry;
    registers.f = (0 | (next_carry << 4));
    registers.a = reg_a;
    cycles = 4;
}

void GbCPU::RR_R8()                           //Funcion de prefijo
{
    unsigned char reg_dir = memory[PC - 1] & 0x07;
    unsigned char reg_x = get_register(reg_dir);
    unsigned char carry = get_carry();
    unsigned char next_carry = reg_x & 0x01;
    reg_x = (reg_x >> 1) | (carry << 7);
    registers.f = 0 | (next_carry << 4);
    if (reg_x == 0) { registers.f = registers.f | 0x80; }
    set_register(reg_dir, reg_x);
    reg_dir == 6 ? cycles = 16 : cycles = 8;
}

void GbCPU::RR_A()
{
    unsigned char reg_a = registers.a;
    unsigned char carry = get_carry();
    unsigned char next_carry = reg_a & 0x01;
    reg_a = (reg_a >> 1) | (carry << 7);
    registers.f = 0 | (next_carry << 4);
    registers.a = reg_a;
    cycles = 4;
}

void GbCPU::RRC_R8()                          //Funcion de prefijo
{
    unsigned char reg_dir = memory[PC - 1] & 0x07;
    unsigned char reg_x = get_register(reg_dir);
    unsigned char next_carry = reg_x & 0x01;
    reg_x = (reg_x >> 1) | (next_carry << 7);
    registers.f = 0 | (next_carry << 4);
    if (reg_x == 0) { registers.f = registers.f | 0x80; }
    set_register(reg_dir, reg_x);
    reg_dir == 6 ? cycles = 16 : cycles = 8;
}

void GbCPU::RRC_A()
{
    unsigned char reg_a = registers.a;
    unsigned char next_carry = reg_a & 0x01;
    reg_a = (reg_a >> 1) | (next_carry << 7);
    registers.f = 0 | (next_carry << 4);
    registers.a = reg_a;
    cycles = 4;
}

void GbCPU::RST(){
    unsigned char target = ((memory[PC - 1] & 0x38) >> 3)*8;
    PC = PC + 1;
    unsigned char low_reg = (PC - 1) & 0x00FF;
    unsigned char high_reg = ((PC - 1) & 0xFF00) >> 8;
    SP = SP - 1;
    memory[SP] = high_reg;
    SP = SP - 1;
    memory[SP] = low_reg;
    PC = target;
    cycles = 16;
}

void GbCPU::SBC_A_R8()
{
    unsigned char reg_dir = memory[PC - 1] & 0x07;
    unsigned char reg_x = get_register(reg_dir);
    unsigned char carry = get_carry();
    unsigned char reg_a = registers.a;
    unsigned char value = reg_a - reg_x;
    set_flags_sbc(reg_a, reg_x, registers.f);
    value = value - carry;
    registers.a = value;
    reg_dir == 6 ? cycles = 8 : cycles = 4;
}

void GbCPU::SBC_A_N8()
{
    unsigned char reg_x = memory[PC];
    unsigned char carry = get_carry();
    unsigned char reg_a = registers.a;
    unsigned char value = reg_a - reg_x;
    set_flags_sbc(reg_a, reg_x, registers.f);
    value = value - carry;
    registers.a = value;
    PC = PC + 1;
    cycles = 8;
}

void GbCPU::SCF()
{
    registers.f = (registers.f & 0x80) | 0x10;
    cycles = 4;
}

void GbCPU::SET_U3_R8()               //Funcion de prefijo
{
    unsigned char reg_dir = memory[PC - 1] & 0x07;
    unsigned char reg_x = get_register(reg_dir);
    unsigned char bit_index = (memory[PC - 1] & 0x38) >> 3;
    reg_x = reg_x | (0x01 << bit_index);
    set_register(reg_dir, reg_x);
    reg_dir == 6 ? cycles = 16 : cycles = 8;
}

void GbCPU::SLA_R8()              //Funcion de prefijo
{
    unsigned char reg_dir = memory[PC - 1] & 0x07;
    unsigned char reg_x = get_register(reg_dir);
    unsigned char carry = (reg_x & 0x80) >> 3;
    reg_x = reg_x << 1;
    unsigned char f_reg = 0x00;
    if (reg_x == 0) { f_reg = 0x80; }
    f_reg = f_reg | carry;
    registers.f = f_reg;
    set_register(reg_dir, reg_x);
    reg_dir == 6 ? cycles = 16 : cycles = 8;
}

void GbCPU::SRA_R8()          //Funcion de prefijo
{
    unsigned char reg_dir = memory[PC - 1] & 0x07;
    unsigned char reg_x = get_register(reg_dir);
    unsigned char carry = (reg_x & 0x01) << 4;
    reg_x = (reg_x & 0x80) | (reg_x >> 1);          //b7 debe permanecer igual
    unsigned char f_reg = 0x00;
    if (reg_x == 0) { f_reg = 0x80; }
    f_reg = f_reg | carry;
    registers.f = f_reg;
    set_register(reg_dir, reg_x);
    reg_dir == 6 ? cycles = 16 : cycles = 8;
}

void GbCPU::SRL_R8()
{
    unsigned char reg_dir = memory[PC - 1] & 0x07;
    unsigned char reg_x = get_register(reg_dir);
    unsigned char carry = (reg_x & 0x01) << 4;
    reg_x = reg_x >> 1;
    unsigned char f_reg = 0x00;
    if (reg_x == 0) { f_reg = 0x80; }
    f_reg = (f_reg | carry);
    registers.f = f_reg;
    set_register(reg_dir, reg_x);
    reg_dir == 6 ? cycles = 16 : cycles = 8;
}

void GbCPU::STOP()
{
    std::cout << "STOP" << std::endl;
    is_stopped = true;
}

void GbCPU::SUB_A_R8()
{
    unsigned char reg_dir = memory[PC - 1] & 0x07;
    unsigned char reg_x = get_register(reg_dir);
    unsigned char reg_a = registers.a;
    unsigned char value = reg_a - reg_x;
    set_flags_sub_8(reg_a, reg_x,registers.f);
    registers.a = value;
    reg_dir == 6 ? cycles = 8 : cycles = 4;
}

void GbCPU::SUB_A_N8()
{
    unsigned char reg_x = memory[PC];
    unsigned char reg_a = registers.a;
    unsigned char value = reg_a - reg_x;
    set_flags_sub_8(reg_a, reg_x, registers.f);
    registers.a = value;
    PC = PC + 1;
    cycles = 8;
}

void GbCPU::SWAP_R8()             //Funcion de prefijo
{
    unsigned char reg_dir = memory[PC - 1]&0x07;
    unsigned char reg_x = get_register(reg_dir);
    unsigned char upper = reg_x & 0xF0;
    unsigned char lower = reg_x & 0x0F;
    reg_x = (lower << 4) | (upper >> 4);
    registers.f = 0x00;
    if (reg_x == 0) { registers.f = registers.f | 0x80; }
    set_register(reg_dir, reg_x);
    reg_dir == 6 ? cycles = 16 : cycles = 8;
}

void GbCPU::XOR_A_R8()
{
    unsigned char reg_dir = (memory[PC - 1])&0x07;
    unsigned char reg_x = get_register(reg_dir);
    unsigned char reg_a = registers.a;
    reg_a = reg_a ^ reg_x;
    registers.f = 0x00;
    if (reg_a == 0) { registers.f = registers.f | 0x80; }
    registers.a = reg_a;
    reg_dir == 6 ? cycles = 8 : cycles = 4;
}

void GbCPU::XOR_A_N8()
{
    unsigned char value = memory[PC];
    unsigned char reg_a = registers.a;
    reg_a = reg_a ^ value;
    registers.f = 0x00;
    if (reg_a == 0) { registers.f = registers.f | 0x80; }
    registers.a = reg_a;
    PC = PC + 1;
    cycles = 8;
}














