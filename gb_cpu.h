#pragma once
class GbCPU
{
public:
	GbCPU();
    //Mapa de memoria
    const unsigned short ROM_BANK_00_START = 0x100; //0x0000, pero los 100 primeros es el bootstrap
    const unsigned short ROM_BANK_00_END = 0x3FFF;
    const unsigned short ROM_BANK_NN_START = 0x4000;
    const unsigned short ROM_BANK_NN_END = 0x7FFF;
    const unsigned short VRAM_START = 0x8000;
    const unsigned short TILES_BLOCK_0 = 0x8000;
    const unsigned short TILES_BLOCK_1 = 0x8800;
    const unsigned short TILES_BLOCK_2 = 0x9000;
    const unsigned short TILEMAP_1 = 0x9800;
    const unsigned short VRAM_END = 0x9FFF;
    const unsigned short EXT_RAM_START = 0xA000;
    const unsigned short EXT_RAM_END = 0xBFFF;
    const unsigned short WRAM_00_START = 0xC000;
    const unsigned short WRAM_00_END = 0xCFFF;
    const unsigned short WRAM_01_START = 0xD000;
    const unsigned short WRAM_01_END = 0xDFFF;
    const unsigned short ECHO_RAM_START = 0xE000; //Zona prohibida. Clona toda la WRAM
    const unsigned short ECHO_RAM_END = 0xFDFF;
    const unsigned short OAM_START = 0xFE00;
    const unsigned short OAM_END = 0xFE9F;
    const unsigned short NOT_USABLE_START = 0xFFA0;  //Zona prohibida.
    const unsigned short NOT_USABLE_END = 0xFEFF;   //Zona prohibida.
    const unsigned short IO_START = 0xFF00;
    const unsigned short DIV_TIMER = 0xFF04;
    const unsigned short TIMA_TIMER = 0xFF05;
    const unsigned short TMA = 0xFF06;
    const unsigned short TAC = 0xFF07;
    const unsigned short IF = 0xFF0F;
    const unsigned short IO_END = 0xFF7F;
    const unsigned short HRAM_START = 0xFF80;
    const unsigned short HRAM_END = 0xFFFE;
    const unsigned short IE = 0xFFFF;


//La GameBoy permite combinar 2 registros, dando lugar as� a un registro virtual de 2 bytes
//af,bc,de,hl
//Como no son registros "reales" habr� que obtenerlos/escribirlos a partir de una funci�n
    unsigned short get_bc() const; //Devuelve un valor de 16bits al juntar los valores de los registros b y c
    void set_bc(unsigned short virtual_register); //Separa un valor de 16 bits en 2 y los asigna a los registors

    unsigned short get_af() const; //Devuelve un valor de 16bits al juntar los valores de los registros a y f
    void set_af(unsigned short virtual_register); //Separa un valor de 16 bits en 2 y los asigna a los registors a y f

    unsigned short get_de(); //Devuelve un valor de 16bits al juntar los valores de los registros d y e
    void set_de(unsigned short virtual_register); //Separa un valor de 16 bits en 2 y los asigna a los registors d y e

    unsigned short get_hl(); //Devuelve un valor de 16bits al juntar los valores de los registros h y l
    void set_hl(unsigned short virtual_register); //Separa un valor de 16 bits en 2 y los asigna a los registors h y l

    unsigned char get_register(unsigned char reg_dir); //Devuelve el registro correspondiente a la direccion
    unsigned short get_register_16(unsigned char reg_dir);
    unsigned short get_register_16MEM(unsigned char reg_dir);
    unsigned short get_register_16STK(unsigned char reg_dir);
    unsigned short manage_hl_mem16(unsigned char reg_dir); //Devuelve el valor hl y luego incrementa/decrementa el registro (NO EL VALOR OBTENIDO)
    

    void set_register(unsigned char reg_dir, unsigned char value);
    void set_register_16(unsigned char reg_dir, unsigned short value);
    void set_register_16MEM(unsigned char reg_dir, unsigned short value);
    void set_register_16STK(unsigned char reg_dir, unsigned short value);

    void set_flags_add_8(unsigned char target, unsigned char value, unsigned char f_reg); //Funcion que ha de ejecutarse cada suma
    void set_flags_add_sp_8(unsigned short target, signed char value, unsigned char f_reg);
    //void set_flags_add_sp_r8(unsigned short target, signed char value, unsigned char f_reg);
    void set_flags_add_16(unsigned short target, unsigned short value, unsigned char f_reg); //Funcion que ha de ejecutarse cada suma
    void set_flags_adc(unsigned char target, unsigned char value, unsigned char f_reg);
    void set_flags_sbc(unsigned char target, unsigned char value, unsigned char f_reg);
    void set_flags_and(unsigned char result, unsigned char f_reg); //Funcion que ha de ejecutarse cada suma
    void set_flags_bit_u3(unsigned char test_bit);
    void set_flags_sub_8(unsigned char target, unsigned char value, unsigned char f_reg); //Funcion que ha de ejecutarse cada resta
    void set_flags_inc_8(unsigned char target, unsigned char f_reg);
    void set_flags_dec_8(unsigned char target, unsigned char f_reg);

    unsigned char get_carry() const;
    unsigned char get_half_carry() const;
    unsigned char get_sub() const;
    unsigned char get_zero() const;
    unsigned char get_flags() const;

    

    unsigned char* get_memory();
    

    void ADC_R8();
    void ADC_N8();
    void ADD_R8();
    void ADD_N8();
    void ADD_HL_R16();
    void ADD_SP_E8();

    void AND_A_R8();
    void AND_A_N8();

    void BIT_U3();
  

    void CALL_N16();
    void CALL_CC_N16();

    void CCF();

    void CP_A_R8();
    void CP_A_N8();

    void CPL();

    void DAA();

    void DEC_R8();
    void DEC_R16();

    void DI();
    void EI();

    void HALT();

    void INC_R8();
    void INC_R16();

    void JP_N16();
    void JP_HL();
    void JP_CC_N16();
    void JR_N16();
    void JR_CC_N16();

    void LD_R8_R8();
    void LD_R8_N8();
    void LD_R16_N16();
    void LD_R16_A();
    void LD_N16_A();
    void LDH_N16_A();
    void LDH_C_A();
    void LD_A_R16MEM();
    void LD_A_N16();
    void LDH_A_N16();
    void LDH_A_C();
    void LD_N16_SP();
    void LD_HL_SP_E8();
    void LD_SP_HL();

    void NOP();

    void OR_A_R8();
    void OR_A_N8();

    void POP_R16();
    void PUSH_R16();

    void RES_U3_R8();

    void RET();
    void RET_CC();
    void RETI();

    void RL_R8();
    void RLA();
    void RLC_R8();
    void RLC_A();

    void RR_R8();
    void RR_A();
    void RRC_R8();
    void RRC_A();

    void RST();

    void SBC_A_R8();
    void SBC_A_N8();

    void SCF();

    void SET_U3_R8();

    void SLA_R8();
    void SRA_R8();
    void SRL_R8();

    void STOP();

    void SUB_A_R8();
    void SUB_A_N8();

    void SWAP_R8();

    void XOR_A_R8();
    void XOR_A_N8();

    //Matrices Instrucciones (https://gbdev.io/gb-opcodes/optables/)
    //Las celdas en blanco quedar representadas con un NOP en mi implemtentacion
    //Igual convendria extraer los punteros ya que se repiten varios, no se
    //Creo que LDH_A_N16 esta mal, deberia haber N8 tambien?
    
    //Lo siento
    void (GbCPU::*instructions[16][16])() = {
        {&GbCPU::NOP,&GbCPU::LD_R16_N16,&GbCPU::LD_R16_A,&GbCPU::INC_R16,&GbCPU::INC_R8,&GbCPU::DEC_R8,&GbCPU::LD_R8_N8,&GbCPU::RLC_A,&GbCPU::LD_N16_SP,&GbCPU::ADD_HL_R16,&GbCPU::LD_A_R16MEM,&GbCPU::DEC_R16,&GbCPU::INC_R8,&GbCPU::DEC_R8,&GbCPU::LD_R8_N8,&GbCPU::RRC_A},
        {&GbCPU::STOP,&GbCPU::LD_R16_N16,&GbCPU::LD_R16_A,&GbCPU::INC_R16,&GbCPU::INC_R8,&GbCPU::DEC_R8,&GbCPU::LD_R8_N8,&GbCPU::RLA,&GbCPU::JR_N16,&GbCPU::ADD_HL_R16,&GbCPU::LD_A_R16MEM,&GbCPU::DEC_R16,&GbCPU::INC_R8,&GbCPU::DEC_R8,&GbCPU::LD_R8_N8,&GbCPU::RR_A},
        {&GbCPU::JR_CC_N16,&GbCPU::LD_R16_N16,&GbCPU::LD_R16_A,&GbCPU::INC_R16,&GbCPU::INC_R8,&GbCPU::DEC_R8,&GbCPU::LD_R8_N8,&GbCPU::DAA,&GbCPU::JR_CC_N16,&GbCPU::ADD_HL_R16,&GbCPU::LD_A_R16MEM,&GbCPU::DEC_R16,&GbCPU::INC_R8,&GbCPU::DEC_R8,&GbCPU::LD_R8_N8,&GbCPU::CPL},
        {&GbCPU::JR_CC_N16,&GbCPU::LD_R16_N16,&GbCPU::LD_R16_A,&GbCPU::INC_R16,&GbCPU::INC_R8,&GbCPU::DEC_R8,&GbCPU::LD_R8_N8,&GbCPU::SCF,&GbCPU::JR_CC_N16,&GbCPU::ADD_HL_R16,&GbCPU::LD_A_R16MEM,&GbCPU::DEC_R16,&GbCPU::INC_R8,&GbCPU::DEC_R8,&GbCPU::LD_R8_N8,&GbCPU::CCF},
        {&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8},
        {&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8},
        {&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8},
        {&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::HALT,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8,&GbCPU::LD_R8_R8},
        {&GbCPU::ADD_R8,&GbCPU::ADD_R8,&GbCPU::ADD_R8,&GbCPU::ADD_R8,&GbCPU::ADD_R8,&GbCPU::ADD_R8,&GbCPU::ADD_R8,&GbCPU::ADD_R8,&GbCPU::ADC_R8,&GbCPU::ADC_R8,&GbCPU::ADC_R8,&GbCPU::ADC_R8,&GbCPU::ADC_R8,&GbCPU::ADC_R8,&GbCPU::ADC_R8,&GbCPU::ADC_R8},
        {&GbCPU::SUB_A_R8,&GbCPU::SUB_A_R8,&GbCPU::SUB_A_R8,&GbCPU::SUB_A_R8,&GbCPU::SUB_A_R8,&GbCPU::SUB_A_R8,&GbCPU::SUB_A_R8,&GbCPU::SUB_A_R8,&GbCPU::SBC_A_R8,&GbCPU::SBC_A_R8,&GbCPU::SBC_A_R8,&GbCPU::SBC_A_R8,&GbCPU::SBC_A_R8,&GbCPU::SBC_A_R8,&GbCPU::SBC_A_R8,&GbCPU::SBC_A_R8},
        {&GbCPU::AND_A_R8,&GbCPU::AND_A_R8,&GbCPU::AND_A_R8,&GbCPU::AND_A_R8,&GbCPU::AND_A_R8,&GbCPU::AND_A_R8,&GbCPU::AND_A_R8,&GbCPU::AND_A_R8,&GbCPU::XOR_A_R8,&GbCPU::XOR_A_R8,&GbCPU::XOR_A_R8,&GbCPU::XOR_A_R8,&GbCPU::XOR_A_R8,&GbCPU::XOR_A_R8,&GbCPU::XOR_A_R8,&GbCPU::XOR_A_R8},
        {&GbCPU::OR_A_R8,&GbCPU::OR_A_R8,&GbCPU::OR_A_R8,&GbCPU::OR_A_R8,&GbCPU::OR_A_R8,&GbCPU::OR_A_R8,&GbCPU::OR_A_R8,&GbCPU::OR_A_R8,&GbCPU::CP_A_R8,&GbCPU::CP_A_R8,&GbCPU::CP_A_R8,&GbCPU::CP_A_R8,&GbCPU::CP_A_R8,&GbCPU::CP_A_R8,&GbCPU::CP_A_R8,&GbCPU::CP_A_R8},
        {&GbCPU::RET_CC,&GbCPU::POP_R16,&GbCPU::JP_CC_N16,&GbCPU::JP_N16,&GbCPU::CALL_CC_N16,&GbCPU::PUSH_R16,&GbCPU::ADD_N8,&GbCPU::RST,&GbCPU::RET_CC,&GbCPU::RET,&GbCPU::JP_CC_N16,&GbCPU::NOP,&GbCPU::CALL_CC_N16,&GbCPU::CALL_N16,&GbCPU::ADC_N8,&GbCPU::RST},
        {&GbCPU::RET_CC,&GbCPU::POP_R16,&GbCPU::JP_CC_N16,&GbCPU::NOP,&GbCPU::CALL_CC_N16,&GbCPU::PUSH_R16,&GbCPU::SUB_A_N8,&GbCPU::RST,&GbCPU::RET_CC,&GbCPU::RETI,&GbCPU::JP_CC_N16,&GbCPU::NOP,&GbCPU::CALL_CC_N16,&GbCPU::NOP,&GbCPU::SBC_A_N8,&GbCPU::RST},
        {&GbCPU::LDH_N16_A,&GbCPU::POP_R16,&GbCPU::LDH_C_A,&GbCPU::NOP,&GbCPU::NOP,&GbCPU::PUSH_R16,&GbCPU::AND_A_N8,&GbCPU::RST,&GbCPU::ADD_SP_E8,&GbCPU::JP_HL,&GbCPU::LD_N16_A,&GbCPU::NOP,&GbCPU::NOP,&GbCPU::NOP,&GbCPU::XOR_A_N8,&GbCPU::RST},
        {&GbCPU::LDH_A_N16,&GbCPU::POP_R16,&GbCPU::LDH_A_C,&GbCPU::DI,&GbCPU::NOP,&GbCPU::PUSH_R16,&GbCPU::OR_A_N8,&GbCPU::RST,&GbCPU::LD_HL_SP_E8,&GbCPU::LD_SP_HL,&GbCPU::LD_A_N16,&GbCPU::EI,&GbCPU::NOP,&GbCPU::NOP,&GbCPU::CP_A_N8,&GbCPU::RST}
    };

    void (GbCPU::* prefix_instructions[16][16])() = {
        {&GbCPU::RLC_R8,&GbCPU::RLC_R8,&GbCPU::RLC_R8,&GbCPU::RLC_R8,&GbCPU::RLC_R8,&GbCPU::RLC_R8,&GbCPU::RLC_R8,&GbCPU::RLC_R8,&GbCPU::RRC_R8,&GbCPU::RRC_R8,&GbCPU::RRC_R8,&GbCPU::RRC_R8,&GbCPU::RRC_R8,&GbCPU::RRC_R8,&GbCPU::RRC_R8,&GbCPU::RRC_R8},
        {&GbCPU::RL_R8,&GbCPU::RL_R8,&GbCPU::RL_R8,&GbCPU::RL_R8,&GbCPU::RL_R8,&GbCPU::RL_R8,&GbCPU::RL_R8,&GbCPU::RL_R8,&GbCPU::RR_R8,&GbCPU::RR_R8,&GbCPU::RR_R8,&GbCPU::RR_R8,&GbCPU::RR_R8,&GbCPU::RR_R8,&GbCPU::RR_R8,&GbCPU::RR_R8},
        {&GbCPU::SLA_R8,&GbCPU::SLA_R8,&GbCPU::SLA_R8,&GbCPU::SLA_R8,&GbCPU::SLA_R8,&GbCPU::SLA_R8,&GbCPU::SLA_R8,&GbCPU::SLA_R8,&GbCPU::SRA_R8,&GbCPU::SRA_R8,&GbCPU::SRA_R8,&GbCPU::SRA_R8,&GbCPU::SRA_R8,&GbCPU::SRA_R8,&GbCPU::SRA_R8,&GbCPU::SRA_R8},
        {&GbCPU::SWAP_R8,&GbCPU::SWAP_R8,&GbCPU::SWAP_R8,&GbCPU::SWAP_R8,&GbCPU::SWAP_R8,&GbCPU::SWAP_R8,&GbCPU::SWAP_R8,&GbCPU::SWAP_R8,&GbCPU::SRL_R8,&GbCPU::SRL_R8,&GbCPU::SRL_R8,&GbCPU::SRL_R8,&GbCPU::SRL_R8,&GbCPU::SRL_R8,&GbCPU::SRL_R8,&GbCPU::SRL_R8},
        {&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3},
        {&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3},
        {&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3},
        {&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3,&GbCPU::BIT_U3},
        {&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8},
        {&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8},
        {&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8},
        {&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8,&GbCPU::RES_U3_R8},
        {&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8},
        {&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8},
        {&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8},
        {&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8,&GbCPU::SET_U3_R8},
    };

    void inc_pc();
    unsigned short get_pc() const;
    void set_pc(unsigned short pc_value);
    unsigned short get_sp() const;
    void set_sp(unsigned short sp_value);
    bool get_stop() const;
    bool is_halted() const;
    void resume();
    bool interrupt_requested();
    int cycles_used();
private:
    //8 registros de un byte
    struct Registers{
        unsigned char a;
        unsigned char b;
        unsigned char c;
        unsigned char d;
        unsigned char e;
        unsigned char f;
        unsigned char h;
        unsigned char l;
    };
    static Registers registers;
    static unsigned char memory[0xFFFF]; //65535 bytes, aka 64 mB 
    unsigned short SP = 0; //Stack pointer
    unsigned short PC = ROM_BANK_00_START; //Program pointer
    unsigned char IME_flag = 0; //Flag maestra de interrupciones. Un unico bit
    unsigned char WAKE = 0;
    bool is_stopped = false;
    bool halted = false;
    int cycles = 0;

};

