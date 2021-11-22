
void CPU::gen_RLC_n(uint8_t& numToRLC) {
    flags.C = ((numToRLC & 0x80) != 0);
    numToRLC = numToRLC << 1;
    numToRLC = numToRLC | flags.C;
    flags.Z = (numToRLC == 0);
    flags.N = false;
    flags.H = false;
}

void CPU::gen_RRC_n(uint8_t& numToRRC) {
    flags.C = numToRRC & 0x01;
    numToRRC = numToRRC >> 1;
    numToRRC = numToRRC | (flags.C << 7);
    flags.Z = (numToRRC == 0);
    flags.N = false;
    flags.H = false;
}

void CPU::gen_RL_n(uint8_t& numToRL) {
    bool oldC = flags.C;
    flags.C = ((numToRL & 0x80) != 0);
    numToRL = numToRL << 1;
    numToRL = numToRL | oldC;
    flags.Z = (numToRL == 0);
    flags.N = false;
    flags.H = false;
}

void CPU::gen_RR_n(uint8_t& numToRL) {
    bool oldC = flags.C;
    flags.C = numToRL & 0x01;
    numToRL = numToRL >> 1;
    numToRL = numToRL | (oldC << 7);
    flags.Z = (numToRL == 0);
    flags.N = false;
    flags.H = false;
}

void CPU::gen_SLA_n(uint8_t& numToSLA) {
    flags.C = (numToSLA & 0x80) != 0;
    numToSLA = numToSLA << 1;
    flags.Z = (numToSLA == 0);
    flags.N = false;
    flags.H = false;
}

void CPU::gen_SRA_n(uint8_t& numToSRA) {
    flags.C = numToSRA & 0x01;
    uint8_t oldMSB = numToSRA & 0x80;
    numToSRA = numToSRA >> 1;
    numToSRA = numToSRA | oldMSB;
    flags.Z = (numToSRA == 0);
    flags.N = false;
    flags.H = false;
}

void CPU::gen_SWAP_n(uint8_t& numToSWAP) {
    uint8_t upperNibble = (numToSWAP & 0xF0) >> 4;
    numToSWAP = numToSWAP << 4;
    numToSWAP = numToSWAP | upperNibble;
    flags.Z = (numToSWAP == 0);
    flags.N = false;
    flags.H = false;
    flags.C = false;
}

void CPU::gen_SRL_n(uint8_t& numToSRL) {
    flags.C = numToSRL & 0x01;
    numToSRL = numToSRL >> 1;
    flags.Z = (numToSRL == 0);
    flags.N = false;
    flags.H = false;
}

void CPU::gen_BIT_b_r(uint8_t bit, uint8_t numBITed) {
    flags.Z = (numBITed & (1 << bit)) == 0;
    flags.N = false;
    flags.H = true;
}

//0x
void CPU::RLC_B() { gen_RLC_n(registers.B); }
void CPU::RLC_C() { gen_RLC_n(registers.C); }
void CPU::RLC_D() { gen_RLC_n(registers.D); }
void CPU::RLC_E() { gen_RLC_n(registers.E); }
void CPU::RLC_H() { gen_RLC_n(registers.H); }
void CPU::RLC_L() { gen_RLC_n(registers.L); }
void CPU::RLC_HLp() { uint8_t n = memoryBus.readByte(registers.HL); gen_RLC_n(n); memoryBus.writeByte(registers.HL, n); }
void CPU::RLC_A() { gen_RLC_n(registers.A); }
void CPU::RRC_B() { gen_RRC_n(registers.B); }
void CPU::RRC_C() { gen_RRC_n(registers.C); }
void CPU::RRC_D() { gen_RRC_n(registers.D); }
void CPU::RRC_E() { gen_RRC_n(registers.E); }
void CPU::RRC_H() { gen_RRC_n(registers.H); }
void CPU::RRC_L() { gen_RRC_n(registers.L); }
void CPU::RRC_HLp() { uint8_t n = memoryBus.readByte(registers.HL); gen_RRC_n(n); memoryBus.writeByte(registers.HL, n); }
void CPU::RRC_A() { gen_RRC_n(registers.A); }

//1x
void CPU::RL_B() { gen_RL_n(registers.B); }
void CPU::RL_C() { gen_RL_n(registers.C); }
void CPU::RL_D() { gen_RL_n(registers.D); }
void CPU::RL_E() { gen_RL_n(registers.E); }
void CPU::RL_H() { gen_RL_n(registers.H); }
void CPU::RL_L() { gen_RL_n(registers.L); }
void CPU::RL_HLp() { uint8_t n = memoryBus.readByte(registers.HL); gen_RL_n(n); memoryBus.writeByte(registers.HL, n); }
void CPU::RL_A() { gen_RL_n(registers.A); }
void CPU::RR_B() { gen_RR_n(registers.B); }
void CPU::RR_C() { gen_RR_n(registers.C); }
void CPU::RR_D() { gen_RR_n(registers.D); }
void CPU::RR_E() { gen_RR_n(registers.E); }
void CPU::RR_H() { gen_RR_n(registers.H); }
void CPU::RR_L() { gen_RR_n(registers.L); }
void CPU::RR_HLp() { uint8_t n = memoryBus.readByte(registers.HL); gen_RR_n(n); memoryBus.writeByte(registers.HL, n); }
void CPU::RR_A() { gen_RR_n(registers.A); }

//2x
void CPU::SLA_B() { gen_SLA_n(registers.B); }
void CPU::SLA_C() { gen_SLA_n(registers.C); }
void CPU::SLA_D() { gen_SLA_n(registers.D); }
void CPU::SLA_E() { gen_SLA_n(registers.E); }
void CPU::SLA_H() { gen_SLA_n(registers.H); }
void CPU::SLA_L() { gen_SLA_n(registers.L); }
void CPU::SLA_HLp() { uint8_t n = memoryBus.readByte(registers.HL); gen_SLA_n(n); memoryBus.writeByte(registers.HL, n); }
void CPU::SLA_A() { gen_SLA_n(registers.A); }
void CPU::SRA_B() { gen_SRA_n(registers.B); }
void CPU::SRA_C() { gen_SRA_n(registers.C); }
void CPU::SRA_D() { gen_SRA_n(registers.D); }
void CPU::SRA_E() { gen_SRA_n(registers.E); }
void CPU::SRA_H() { gen_SRA_n(registers.H); }
void CPU::SRA_L() { gen_SRA_n(registers.L); }
void CPU::SRA_HLp() { uint8_t n = memoryBus.readByte(registers.HL); gen_SRA_n(n); memoryBus.writeByte(registers.HL, n); }
void CPU::SRA_A() { gen_SRA_n(registers.A); }

//3x
void CPU::SWAP_B() { gen_SWAP_n(registers.B); }
void CPU::SWAP_C() { gen_SWAP_n(registers.C); }
void CPU::SWAP_D() { gen_SWAP_n(registers.D); }
void CPU::SWAP_E() { gen_SWAP_n(registers.E); }
void CPU::SWAP_H() { gen_SWAP_n(registers.H); }
void CPU::SWAP_L() { gen_SWAP_n(registers.L); }
void CPU::SWAP_HLp() { uint8_t n = memoryBus.readByte(registers.HL); gen_SWAP_n(n); memoryBus.writeByte(registers.HL, n); }
void CPU::SWAP_A() { gen_SWAP_n(registers.A); }
void CPU::SRL_B() { gen_SRL_n(registers.B); }
void CPU::SRL_C() { gen_SRL_n(registers.C); }
void CPU::SRL_D() { gen_SRL_n(registers.D); }
void CPU::SRL_E() { gen_SRL_n(registers.E); }
void CPU::SRL_H() { gen_SRL_n(registers.H); }
void CPU::SRL_L() { gen_SRL_n(registers.L); }
void CPU::SRL_HLp() { uint8_t n = memoryBus.readByte(registers.HL); gen_SRL_n(n); memoryBus.writeByte(registers.HL, n); }
void CPU::SRL_A() { gen_SRL_n(registers.A); }

//4x
void CPU::BIT_0_B() { gen_BIT_b_r(0, registers.B); }
void CPU::BIT_0_C() { gen_BIT_b_r(0, registers.C); }
void CPU::BIT_0_D() { gen_BIT_b_r(0, registers.D); }
void CPU::BIT_0_E() { gen_BIT_b_r(0, registers.E); }
void CPU::BIT_0_H() { gen_BIT_b_r(0, registers.H); }
void CPU::BIT_0_L() { gen_BIT_b_r(0, registers.L); }
void CPU::BIT_0_HLp() { uint8_t r = memoryBus.readByte(registers.HL); gen_BIT_b_r(0, r); }
void CPU::BIT_0_A() { gen_BIT_b_r(0, registers.A); }
void CPU::BIT_1_B() { gen_BIT_b_r(1, registers.B); }
void CPU::BIT_1_C() { gen_BIT_b_r(1, registers.C); }
void CPU::BIT_1_D() { gen_BIT_b_r(1, registers.D); }
void CPU::BIT_1_E() { gen_BIT_b_r(1, registers.E); }
void CPU::BIT_1_H() { gen_BIT_b_r(1, registers.H); }
void CPU::BIT_1_L() { gen_BIT_b_r(1, registers.L); }
void CPU::BIT_1_HLp() { uint8_t r = memoryBus.readByte(registers.HL); gen_BIT_b_r(1, r); }
void CPU::BIT_1_A() { gen_BIT_b_r(1, registers.A); }

//5x
void CPU::BIT_2_B() { gen_BIT_b_r(2, registers.B); }
void CPU::BIT_2_C() { gen_BIT_b_r(2, registers.C); }
void CPU::BIT_2_D() { gen_BIT_b_r(2, registers.D); }
void CPU::BIT_2_E() { gen_BIT_b_r(2, registers.E); }
void CPU::BIT_2_H() { gen_BIT_b_r(2, registers.H); }
void CPU::BIT_2_L() { gen_BIT_b_r(2, registers.L); }
void CPU::BIT_2_HLp() { uint8_t r = memoryBus.readByte(registers.HL); gen_BIT_b_r(2, r); }
void CPU::BIT_2_A() { gen_BIT_b_r(2, registers.A); }
void CPU::BIT_3_B() { gen_BIT_b_r(3, registers.B); }
void CPU::BIT_3_C() { gen_BIT_b_r(3, registers.C); }
void CPU::BIT_3_D() { gen_BIT_b_r(3, registers.D); }
void CPU::BIT_3_E() { gen_BIT_b_r(3, registers.E); }
void CPU::BIT_3_H() { gen_BIT_b_r(3, registers.H); }
void CPU::BIT_3_L() { gen_BIT_b_r(3, registers.L); }
void CPU::BIT_3_HLp() { uint8_t r = memoryBus.readByte(registers.HL); gen_BIT_b_r(3, r); }
void CPU::BIT_3_A() { gen_BIT_b_r(3, registers.A); }

//6x
void CPU::BIT_4_B() { gen_BIT_b_r(4, registers.B); }
void CPU::BIT_4_C() { gen_BIT_b_r(4, registers.C); }
void CPU::BIT_4_D() { gen_BIT_b_r(4, registers.D); }
void CPU::BIT_4_E() { gen_BIT_b_r(4, registers.E); }
void CPU::BIT_4_H() { gen_BIT_b_r(4, registers.H); }
void CPU::BIT_4_L() { gen_BIT_b_r(4, registers.L); }
void CPU::BIT_4_HLp() { uint8_t r = memoryBus.readByte(registers.HL); gen_BIT_b_r(4, r); }
void CPU::BIT_4_A() { gen_BIT_b_r(4, registers.A); }
void CPU::BIT_5_B() { gen_BIT_b_r(5, registers.B); }
void CPU::BIT_5_C() { gen_BIT_b_r(5, registers.C); }
void CPU::BIT_5_D() { gen_BIT_b_r(5, registers.D); }
void CPU::BIT_5_E() { gen_BIT_b_r(5, registers.E); }
void CPU::BIT_5_H() { gen_BIT_b_r(5, registers.H); }
void CPU::BIT_5_L() { gen_BIT_b_r(5, registers.L); }
void CPU::BIT_5_HLp() { uint8_t r = memoryBus.readByte(registers.HL); gen_BIT_b_r(5, r); }
void CPU::BIT_5_A() { gen_BIT_b_r(5, registers.A); }

//7x
void CPU::BIT_6_B() { gen_BIT_b_r(6, registers.B); }
void CPU::BIT_6_C() { gen_BIT_b_r(6, registers.C); }
void CPU::BIT_6_D() { gen_BIT_b_r(6, registers.D); }
void CPU::BIT_6_E() { gen_BIT_b_r(6, registers.E); }
void CPU::BIT_6_H() { gen_BIT_b_r(6, registers.H); }
void CPU::BIT_6_L() { gen_BIT_b_r(6, registers.L); }
void CPU::BIT_6_HLp() { uint8_t r = memoryBus.readByte(registers.HL); gen_BIT_b_r(6, r); }
void CPU::BIT_6_A() { gen_BIT_b_r(6, registers.A); }
void CPU::BIT_7_B() { gen_BIT_b_r(7, registers.B); }
void CPU::BIT_7_C() { gen_BIT_b_r(7, registers.C); }
void CPU::BIT_7_D() { gen_BIT_b_r(7, registers.D); }
void CPU::BIT_7_E() { gen_BIT_b_r(7, registers.E); }
void CPU::BIT_7_H() { gen_BIT_b_r(7, registers.H); }
void CPU::BIT_7_L() { gen_BIT_b_r(7, registers.L); }
void CPU::BIT_7_HLp() { uint8_t r = memoryBus.readByte(registers.HL); gen_BIT_b_r(7, r); }
void CPU::BIT_7_A() { gen_BIT_b_r(7, registers.A); }

//8x
void CPU::RES_0_B() { registers.B &= ~(1 << 0); }
void CPU::RES_0_C() { registers.C &= ~(1 << 0); }
void CPU::RES_0_D() { registers.D &= ~(1 << 0); }
void CPU::RES_0_E() { registers.E &= ~(1 << 0); }
void CPU::RES_0_H() { registers.H &= ~(1 << 0); }
void CPU::RES_0_L() { registers.L &= ~(1 << 0); }
void CPU::RES_0_HLp() { uint8_t n = memoryBus.readByte(registers.HL); n &= ~(1 << 0); memoryBus.writeByte(registers.HL, n); }
void CPU::RES_0_A() { registers.A &= ~(1 << 0); }
void CPU::RES_1_B() { registers.B &= ~(1 << 1); }
void CPU::RES_1_C() { registers.C &= ~(1 << 1); }
void CPU::RES_1_D() { registers.D &= ~(1 << 1); }
void CPU::RES_1_E() { registers.E &= ~(1 << 1); }
void CPU::RES_1_H() { registers.H &= ~(1 << 1); }
void CPU::RES_1_L() { registers.L &= ~(1 << 1); }
void CPU::RES_1_HLp() { uint8_t n = memoryBus.readByte(registers.HL); n &= ~(1 << 1); memoryBus.writeByte(registers.HL, n); }
void CPU::RES_1_A() { registers.A &= ~(1 << 1); }

//9x
void CPU::RES_2_B() { registers.B &= ~(1 << 2); }
void CPU::RES_2_C() { registers.C &= ~(1 << 2); }
void CPU::RES_2_D() { registers.D &= ~(1 << 2); }
void CPU::RES_2_E() { registers.E &= ~(1 << 2); }
void CPU::RES_2_H() { registers.H &= ~(1 << 2); }
void CPU::RES_2_L() { registers.L &= ~(1 << 2); }
void CPU::RES_2_HLp() { uint8_t n = memoryBus.readByte(registers.HL); n &= ~(1 << 2); memoryBus.writeByte(registers.HL, n); }
void CPU::RES_2_A() { registers.A &= ~(1 << 2); }
void CPU::RES_3_B() { registers.B &= ~(1 << 3); }
void CPU::RES_3_C() { registers.C &= ~(1 << 3); }
void CPU::RES_3_D() { registers.D &= ~(1 << 3); }
void CPU::RES_3_E() { registers.E &= ~(1 << 3); }
void CPU::RES_3_H() { registers.H &= ~(1 << 3); }
void CPU::RES_3_L() { registers.L &= ~(1 << 3); }
void CPU::RES_3_HLp() { uint8_t n = memoryBus.readByte(registers.HL); n &= ~(1 << 3); memoryBus.writeByte(registers.HL, n); }
void CPU::RES_3_A() { registers.A &= ~(1 << 3); }

//Ax
void CPU::RES_4_B() { registers.B &= ~(1 << 4); }
void CPU::RES_4_C() { registers.C &= ~(1 << 4); }
void CPU::RES_4_D() { registers.D &= ~(1 << 4); }
void CPU::RES_4_E() { registers.E &= ~(1 << 4); }
void CPU::RES_4_H() { registers.H &= ~(1 << 4); }
void CPU::RES_4_L() { registers.L &= ~(1 << 4); }
void CPU::RES_4_HLp() { uint8_t n = memoryBus.readByte(registers.HL); n &= ~(1 << 4); memoryBus.writeByte(registers.HL, n); }
void CPU::RES_4_A() { registers.A &= ~(1 << 4); }
void CPU::RES_5_B() { registers.B &= ~(1 << 5); }
void CPU::RES_5_C() { registers.C &= ~(1 << 5); }
void CPU::RES_5_D() { registers.D &= ~(1 << 5); }
void CPU::RES_5_E() { registers.E &= ~(1 << 5); }
void CPU::RES_5_H() { registers.H &= ~(1 << 5); }
void CPU::RES_5_L() { registers.L &= ~(1 << 5); }
void CPU::RES_5_HLp() { uint8_t n = memoryBus.readByte(registers.HL); n &= ~(1 << 5); memoryBus.writeByte(registers.HL, n); }
void CPU::RES_5_A() { registers.A &= ~(1 << 5); }

//Bx
void CPU::RES_6_B() { registers.B &= ~(1 << 6); }
void CPU::RES_6_C() { registers.C &= ~(1 << 6); }
void CPU::RES_6_D() { registers.D &= ~(1 << 6); }
void CPU::RES_6_E() { registers.E &= ~(1 << 6); }
void CPU::RES_6_H() { registers.H &= ~(1 << 6); }
void CPU::RES_6_L() { registers.L &= ~(1 << 6); }
void CPU::RES_6_HLp() { uint8_t n = memoryBus.readByte(registers.HL); n &= ~(1 << 6); memoryBus.writeByte(registers.HL, n); }
void CPU::RES_6_A() { registers.A &= ~(1 << 6); }
void CPU::RES_7_B() { registers.B &= ~(1 << 7); }
void CPU::RES_7_C() { registers.C &= ~(1 << 7); }
void CPU::RES_7_D() { registers.D &= ~(1 << 7); }
void CPU::RES_7_E() { registers.E &= ~(1 << 7); }
void CPU::RES_7_H() { registers.H &= ~(1 << 7); }
void CPU::RES_7_L() { registers.L &= ~(1 << 7); }
void CPU::RES_7_HLp() { uint8_t n = memoryBus.readByte(registers.HL); n &= ~(1 << 7); memoryBus.writeByte(registers.HL, n); }
void CPU::RES_7_A() { registers.A &= ~(1 << 7); }

//Cx
void CPU::SET_0_B() { registers.B |= (1 << 0); }
void CPU::SET_0_C() { registers.C |= (1 << 0); }
void CPU::SET_0_D() { registers.D |= (1 << 0); }
void CPU::SET_0_E() { registers.E |= (1 << 0); }
void CPU::SET_0_H() { registers.H |= (1 << 0); }
void CPU::SET_0_L() { registers.L |= (1 << 0); }
void CPU::SET_0_HLp() { uint8_t n = memoryBus.readByte(registers.HL); n |= (1 << 0); memoryBus.writeByte(registers.HL, n); }
void CPU::SET_0_A() { registers.A |= (1 << 0); }
void CPU::SET_1_B() { registers.B |= (1 << 1); }
void CPU::SET_1_C() { registers.C |= (1 << 1); }
void CPU::SET_1_D() { registers.D |= (1 << 1); }
void CPU::SET_1_E() { registers.E |= (1 << 1); }
void CPU::SET_1_H() { registers.H |= (1 << 1); }
void CPU::SET_1_L() { registers.L |= (1 << 1); }
void CPU::SET_1_HLp() { uint8_t n = memoryBus.readByte(registers.HL); n |= (1 << 1); memoryBus.writeByte(registers.HL, n); }
void CPU::SET_1_A() { registers.A |= (1 << 1); }

//Dx
void CPU::SET_2_B() { registers.B |= (1 << 2); }
void CPU::SET_2_C() { registers.C |= (1 << 2); }
void CPU::SET_2_D() { registers.D |= (1 << 2); }
void CPU::SET_2_E() { registers.E |= (1 << 2); }
void CPU::SET_2_H() { registers.H |= (1 << 2); }
void CPU::SET_2_L() { registers.L |= (1 << 2); }
void CPU::SET_2_HLp() { uint8_t n = memoryBus.readByte(registers.HL); n |= (1 << 2); memoryBus.writeByte(registers.HL, n); }
void CPU::SET_2_A() { registers.A |= (1 << 2); }
void CPU::SET_3_B() { registers.B |= (1 << 3); }
void CPU::SET_3_C() { registers.C |= (1 << 3); }
void CPU::SET_3_D() { registers.D |= (1 << 3); }
void CPU::SET_3_E() { registers.E |= (1 << 3); }
void CPU::SET_3_H() { registers.H |= (1 << 3); }
void CPU::SET_3_L() { registers.L |= (1 << 3); }
void CPU::SET_3_HLp() { uint8_t n = memoryBus.readByte(registers.HL); n |= (1 << 3); memoryBus.writeByte(registers.HL, n); }
void CPU::SET_3_A() { registers.A |= (1 << 3); }

//Ex
void CPU::SET_4_B() { registers.B |= (1 << 4); }
void CPU::SET_4_C() { registers.C |= (1 << 4); }
void CPU::SET_4_D() { registers.D |= (1 << 4); }
void CPU::SET_4_E() { registers.E |= (1 << 4); }
void CPU::SET_4_H() { registers.H |= (1 << 4); }
void CPU::SET_4_L() { registers.L |= (1 << 4); }
void CPU::SET_4_HLp() { uint8_t n = memoryBus.readByte(registers.HL); n |= (1 << 4); memoryBus.writeByte(registers.HL, n); }
void CPU::SET_4_A() { registers.A |= (1 << 4); }
void CPU::SET_5_B() { registers.B |= (1 << 5); }
void CPU::SET_5_C() { registers.C |= (1 << 5); }
void CPU::SET_5_D() { registers.D |= (1 << 5); }
void CPU::SET_5_E() { registers.E |= (1 << 5); }
void CPU::SET_5_H() { registers.H |= (1 << 5); }
void CPU::SET_5_L() { registers.L |= (1 << 5); }
void CPU::SET_5_HLp() { uint8_t n = memoryBus.readByte(registers.HL); n |= (1 << 5); memoryBus.writeByte(registers.HL, n); }
void CPU::SET_5_A() { registers.A |= (1 << 5); }

//Fx
void CPU::SET_6_B() { registers.B |= (1 << 6); }
void CPU::SET_6_C() { registers.C |= (1 << 6); }
void CPU::SET_6_D() { registers.D |= (1 << 6); }
void CPU::SET_6_E() { registers.E |= (1 << 6); }
void CPU::SET_6_H() { registers.H |= (1 << 6); }
void CPU::SET_6_L() { registers.L |= (1 << 6); }
void CPU::SET_6_HLp() { uint8_t n = memoryBus.readByte(registers.HL); n |= (1 << 6); memoryBus.writeByte(registers.HL, n); }
void CPU::SET_6_A() { registers.A |= (1 << 6); }
void CPU::SET_7_B() { registers.B |= (1 << 7); }
void CPU::SET_7_C() { registers.C |= (1 << 7); }
void CPU::SET_7_D() { registers.D |= (1 << 7); }
void CPU::SET_7_E() { registers.E |= (1 << 7); }
void CPU::SET_7_H() { registers.H |= (1 << 7); }
void CPU::SET_7_L() { registers.L |= (1 << 7); }
void CPU::SET_7_HLp() { uint8_t n = memoryBus.readByte(registers.HL); n |= (1 << 7); memoryBus.writeByte(registers.HL, n); }
void CPU::SET_7_A() { registers.A |= (1 << 7); }
