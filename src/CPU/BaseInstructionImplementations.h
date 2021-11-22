
void CPU::gen_ADD_A_n(uint8_t numADDed) {
    flags.C = (signed int) (registers.A) + numADDed > 0xFF;
    flags.H = (signed int) (registers.A & 0x0F) + (numADDed & 0x0F) > 0x0F;
    flags.N = false;
    registers.A = registers.A + numADDed;
    flags.Z = (registers.A == 0);
}

void CPU::gen_ADC_A_n(uint8_t numADCed) {
    bool oldFlagC = flags.C;
    flags.C = (signed int) (registers.A) + numADCed + oldFlagC > 0xFF;
    flags.H = (signed int) (registers.A & 0x0F) + (numADCed & 0x0F) + (oldFlagC) > 0x0F;
    flags.N = false;
    registers.A = registers.A + numADCed + oldFlagC;
    flags.Z = (registers.A == 0);
}

void CPU::gen_SUB_A_n(uint8_t numSUBed) {
    flags.C = (signed int) (registers.A) < numSUBed;
    flags.H = (signed int) (registers.A & 0x0F) < (numSUBed & 0x0F);
    flags.N = true;
    registers.A = registers.A - numSUBed;
    flags.Z = (registers.A == 0);
}

void CPU::gen_SBC_A_n(uint8_t numSBCed) {
    bool oldC = flags.C;
    flags.C = (signed int) (registers.A) < (numSBCed + oldC);
    flags.H = (signed int) (registers.A & 0x0F) < ((numSBCed & 0x0F) + oldC);
    flags.N = true;
    registers.A = registers.A - (numSBCed + oldC);
    flags.Z = (registers.A == 0);
}

void CPU::gen_AND_n(uint8_t numANDed) {
    registers.A = registers.A & numANDed;
    flags.Z = (registers.A == 0);
    flags.N = false;
    flags.H = true;
    flags.C = false;
}

void CPU::gen_OR_n(uint8_t numORed) {
    registers.A = registers.A | numORed;
    flags.Z = (registers.A == 0);
    flags.N = false;
    flags.H = false;
    flags.C = false;
}

void CPU::gen_XOR_n(uint8_t numXORed) {
    registers.A = registers.A ^ numXORed;
    flags.Z = (registers.A == 0);
    flags.N = false;
    flags.H = false;
    flags.C = false;
}

void CPU::gen_CP_n(uint8_t numCPed) {
    flags.Z = (registers.A == numCPed);
    flags.N = true;
    flags.H = (registers.A & 0x0F) < (numCPed & 0x0F);
    flags.C = registers.A < numCPed;
}

void CPU::gen_INC_n(uint8_t& numToINC) {
    flags.Z = (numToINC == 0xFF); //Will overflow to 0
    flags.N = false;
    flags.H = ((numToINC & 0x0F) == 0x0F);
    //flags.C not affected
    numToINC++;
}

void CPU::gen_DEC_n(uint8_t& numToDEC) {
    flags.Z = (numToDEC == 1);
    flags.N = true;
    flags.H = ((numToDEC & 0x0F) == 0);
    //flags.C not affected
    numToDEC--;
}

void CPU::gen_ADD_HL_n(uint16_t numADDed) {
    flags.H = (signed int) (registers.HL & 0x0FFF) + (numADDed & 0x0FFF) > 0x0FFF;
    flags.C = (signed int) registers.HL + numADDed > 0xFFFF;
    flags.N = false;
    //flags.Z not affected
    registers.HL = registers.HL + numADDed;
}

void CPU::XXX() { std::cout << "XXX got called!!!" << std::endl; }

//0x
void CPU::nop() { /* Do nothing */ }
void CPU::LD_BC_nn() { registers.BC = memoryBus.readWord(pc); pc += 2; }
void CPU::LD_BCp_A() { memoryBus.writeByte(registers.BC, registers.A); }
void CPU::INC_BC() { registers.BC++; }
void CPU::INC_B() { gen_INC_n(registers.B); }
void CPU::DEC_B() { gen_DEC_n(registers.B); }
void CPU::LD_B_n() { registers.B = memoryBus.readByte(pc); pc++; }
void CPU::RLCA() {
    flags.C = ((registers.A & 0x80) != 0);
    registers.A = registers.A << 1;
    registers.A = registers.A | flags.C;
    flags.Z = false;
    flags.N = false;
    flags.H = false;
}
void CPU::LD_nnp_SP() { uint16_t nn = memoryBus.readWord(pc); pc += 2; memoryBus.writeWord(nn, sp); }
void CPU::ADD_HL_BC() { gen_ADD_HL_n(registers.BC); }
void CPU::LD_A_BCp() { registers.A = memoryBus.readByte(registers.BC); }
void CPU::DEC_BC() { registers.BC--; }
void CPU::INC_C() { gen_INC_n(registers.C); }
void CPU::DEC_C() { gen_DEC_n(registers.C); }
void CPU::LD_C_n() { registers.C = memoryBus.readByte(pc); pc++; }
void CPU::RRCA() {
    flags.C = registers.A & 0x01;
    registers.A = registers.A >> 1;
    registers.A = registers.A | (flags.C << 7);
    flags.Z = false;
    flags.N = false;
    flags.H = false;
}

//1x
void CPU::STOP() {/* 2 bytes for some reason */ pc++; std::cout << "STOP GOT CALLED!!!" << std::endl; }
void CPU::LD_DE_nn() { registers.DE = memoryBus.readWord(pc); pc += 2; }
void CPU::LD_DEp_A() { memoryBus.writeByte(registers.DE, registers.A); }
void CPU::INC_DE() { registers.DE++; }
void CPU::INC_D() { gen_INC_n(registers.D); }
void CPU::DEC_D() { gen_DEC_n(registers.D); }
void CPU::LD_D_n() { registers.D = memoryBus.readByte(pc); pc++; }
void CPU::RLA() {
    bool oldC = flags.C;
    flags.C = ((registers.A & 0x80) != 0);
    registers.A = registers.A << 1;
    registers.A = registers.A | oldC;
    flags.Z = false;
    flags.N = false;
    flags.H = false;
}
void CPU::JR_n() {
    uint8_t unsignedN = memoryBus.readByte(pc);
    int8_t signedN = *(int8_t*) &unsignedN;
    pc++;
    pc = pc + signedN;
}
void CPU::ADD_HL_DE() { gen_ADD_HL_n(registers.DE); }
void CPU::LD_A_DEp() { registers.A = memoryBus.readByte(registers.DE); }
void CPU::DEC_DE() { registers.DE--; }
void CPU::INC_E() { gen_INC_n(registers.E); }
void CPU::DEC_E() { gen_DEC_n(registers.E); }
void CPU::LD_E_n() { registers.E = memoryBus.readByte(pc); pc++; }
void CPU::RRA() {
    bool oldC = flags.C;
    flags.C = registers.A & 0x01;
    registers.A = registers.A >> 1;
    registers.A = registers.A | (oldC << 7);
    flags.Z = false;
    flags.N = false;
    flags.H = false;
}

//2x
void CPU::JR_NZ_n() { if(!flags.Z) JR_n(); else pc++;}
void CPU::LD_HL_nn() { registers.HL = memoryBus.readWord(pc); pc += 2; }
void CPU::LDI_HLp_A() { memoryBus.writeByte(registers.HL, registers.A); registers.HL++; }
void CPU::INC_HL() { registers.HL++; }
void CPU::INC_H() { gen_INC_n(registers.H); }
void CPU::DEC_H() { gen_DEC_n(registers.H); }
void CPU::LD_H_n() { registers.H = memoryBus.readByte(pc); pc++; }
void CPU::DAA() { //https://forums.nesdev.com/viewtopic.php?t=15944
    if(!flags.N) {
        if(flags.C || registers.A > 0x99) {
            registers.A = registers.A + 0x60;
            flags.C = true;
        }
        if(flags.H || (registers.A & 0x0F) > 0x09)
            registers.A = registers.A + 0x06;
    } else {
        if(flags.C)
            registers.A = registers.A - 0x60;

        if(flags.H)
            registers.A = registers.A - 0x06;
    }

    flags.H = false;
    flags.Z = (registers.A == 0);
}
void CPU::JR_Z_n() { if(flags.Z) JR_n(); else pc++;}
void CPU::ADD_HL_HL() { gen_ADD_HL_n(registers.HL); }
void CPU::LDI_A_HLp() { registers.A = memoryBus.readByte(registers.HL); registers.HL++; }
void CPU::DEC_HL() { registers.HL--; }
void CPU::INC_L() { gen_INC_n(registers.L); }
void CPU::DEC_L() { gen_DEC_n(registers.L); }
void CPU::LD_L_n() { registers.L = memoryBus.readByte(pc); pc++; }
void CPU::CPL() { registers.A = ~registers.A; flags.N = true; flags.H = true; }

//3x
void CPU::JR_NC_n() { if(!flags.C) JR_n(); else pc++; }
void CPU::LD_SP_nn() { sp = memoryBus.readWord(pc); pc += 2; }
void CPU::LDD_HLp_A() { memoryBus.writeByte(registers.HL, registers.A); registers.HL--; }
void CPU::INC_SP() { sp++; }
void CPU::INC_HLp() { uint8_t n = memoryBus.readByte(registers.HL); gen_INC_n(n); memoryBus.writeByte(registers.HL, n); }
void CPU::DEC_HLp() { uint8_t n = memoryBus.readByte(registers.HL); gen_DEC_n(n); memoryBus.writeByte(registers.HL, n); }
void CPU::LD_HLp_n() { uint8_t n = memoryBus.readByte(pc); pc++; memoryBus.writeByte(registers.HL, n); }
void CPU::SCF() { flags.C = true; flags.N = false; flags.H = false; }
void CPU::JR_C_n() { if(flags.C) JR_n(); else pc++; }
void CPU::ADD_HL_SP() { gen_ADD_HL_n(sp); }
void CPU::LDD_A_HLp() { registers.A = memoryBus.readByte(registers.HL); registers.HL--; }
void CPU::DEC_SP() { sp--; }
void CPU::INC_A() { gen_INC_n(registers.A); }
void CPU::DEC_A() { gen_DEC_n(registers.A); }
void CPU::LD_A_n() { registers.A = memoryBus.readByte(pc); pc++; }
void CPU::CCF() { flags.C = !flags.C; flags.N = false; flags.H = false; }

//4x
void CPU::LD_B_B() { registers.B = registers.B; }
void CPU::LD_B_C() { registers.B = registers.C; }
void CPU::LD_B_D() { registers.B = registers.D; }
void CPU::LD_B_E() { registers.B = registers.E; }
void CPU::LD_B_H() { registers.B = registers.H; }
void CPU::LD_B_L() { registers.B = registers.L; }
void CPU::LD_B_HLp() { registers.B = memoryBus.readByte(registers.HL); }
void CPU::LD_B_A() { registers.B = registers.A; }
void CPU::LD_C_B() { registers.C = registers.B; }
void CPU::LD_C_C() { registers.C = registers.C; }
void CPU::LD_C_D() { registers.C = registers.D; }
void CPU::LD_C_E() { registers.C = registers.E; }
void CPU::LD_C_H() { registers.C = registers.H; }
void CPU::LD_C_L() { registers.C = registers.L; }
void CPU::LD_C_HLp() { registers.C = memoryBus.readByte(registers.HL); }
void CPU::LD_C_A() {registers.C = registers.A; }

//5x
void CPU::LD_D_B() { registers.D = registers.B; }
void CPU::LD_D_C() { registers.D = registers.C; }
void CPU::LD_D_D() { registers.D = registers.D; }
void CPU::LD_D_E() { registers.D = registers.E; }
void CPU::LD_D_H() { registers.D = registers.H; }
void CPU::LD_D_L() { registers.D = registers.L; }
void CPU::LD_D_HLp() { registers.D = memoryBus.readByte(registers.HL); }
void CPU::LD_D_A() { registers.D= registers.A; }
void CPU::LD_E_B() { registers.E = registers.B; }
void CPU::LD_E_C() { registers.E = registers.C; }
void CPU::LD_E_D() { registers.E = registers.D; }
void CPU::LD_E_E() { registers.E = registers.E; }
void CPU::LD_E_H() { registers.E = registers.H; }
void CPU::LD_E_L() { registers.E = registers.L; }
void CPU::LD_E_HLp() { registers.E = memoryBus.readByte(registers.HL); }
void CPU::LD_E_A() { registers.E= registers.A; }

//6x
void CPU::LD_H_B() { registers.H = registers.B; }
void CPU::LD_H_C() { registers.H = registers.C; }
void CPU::LD_H_D() { registers.H = registers.D; }
void CPU::LD_H_E() { registers.H = registers.E; }
void CPU::LD_H_H() { registers.H = registers.H; }
void CPU::LD_H_L() { registers.H = registers.L; }
void CPU::LD_H_HLp() { registers.H = memoryBus.readByte(registers.HL); }
void CPU::LD_H_A() { registers.H= registers.A; }
void CPU::LD_L_B() { registers.L = registers.B; }
void CPU::LD_L_C() { registers.L = registers.C; }
void CPU::LD_L_D() { registers.L = registers.D; }
void CPU::LD_L_E() { registers.L = registers.E; }
void CPU::LD_L_H() { registers.L = registers.H; }
void CPU::LD_L_L() { registers.L = registers.L; }
void CPU::LD_L_HLp() { registers.L = memoryBus.readByte(registers.HL); }
void CPU::LD_L_A() { registers.L= registers.A; }

//7x
void CPU::LD_HLp_B() { memoryBus.writeByte(registers.HL, registers.B); }
void CPU::LD_HLp_C() { memoryBus.writeByte(registers.HL, registers.C); }
void CPU::LD_HLp_D() { memoryBus.writeByte(registers.HL, registers.D); }
void CPU::LD_HLp_E() { memoryBus.writeByte(registers.HL, registers.E); }
void CPU::LD_HLp_H() { memoryBus.writeByte(registers.HL, registers.H); }
void CPU::LD_HLp_L() { memoryBus.writeByte(registers.HL, registers.L); }
void CPU::HALT() { halted = true; std::cout << "Halt Called" << std::endl; }
void CPU::LD_HLp_A() { memoryBus.writeByte(registers.HL, registers.A); }
void CPU::LD_A_B() { registers.A = registers.B; }
void CPU::LD_A_C() { registers.A = registers.C; }
void CPU::LD_A_D() { registers.A = registers.D; }
void CPU::LD_A_E() { registers.A = registers.E; }
void CPU::LD_A_H() { registers.A = registers.H; }
void CPU::LD_A_L() { registers.A = registers.L; }
void CPU::LD_A_HLp() { registers.A = memoryBus.readByte(registers.HL); }
void CPU::LD_A_A() { registers.A = registers.A; }

//8x
void CPU::ADD_A_B() { gen_ADD_A_n(registers.B); }
void CPU::ADD_A_C() { gen_ADD_A_n(registers.C);}
void CPU::ADD_A_D() { gen_ADD_A_n(registers.D); }
void CPU::ADD_A_E() { gen_ADD_A_n(registers.E); }
void CPU::ADD_A_H() { gen_ADD_A_n(registers.H); }
void CPU::ADD_A_L() { gen_ADD_A_n(registers.L); }
void CPU::ADD_A_HLp() { uint8_t n = memoryBus.readByte(registers.HL); gen_ADD_A_n(n); }
void CPU::ADD_A_A() { gen_ADD_A_n(registers.A); }
void CPU::ADC_A_B() { gen_ADC_A_n(registers.B); }
void CPU::ADC_A_C() { gen_ADC_A_n(registers.C); }
void CPU::ADC_A_D() { gen_ADC_A_n(registers.D); }
void CPU::ADC_A_E() { gen_ADC_A_n(registers.E); }
void CPU::ADC_A_H() { gen_ADC_A_n(registers.H); }
void CPU::ADC_A_L() { gen_ADC_A_n(registers.L); }
void CPU::ADC_A_HLp() { uint8_t n = memoryBus.readByte(registers.HL); gen_ADC_A_n(n); }
void CPU::ADC_A_A() { gen_ADC_A_n(registers.A); }

//9x
void CPU::SUB_A_B() { gen_SUB_A_n(registers.B); }
void CPU::SUB_A_C() { gen_SUB_A_n(registers.C); }
void CPU::SUB_A_D() { gen_SUB_A_n(registers.D); }
void CPU::SUB_A_E() { gen_SUB_A_n(registers.E); }
void CPU::SUB_A_H() { gen_SUB_A_n(registers.H); }
void CPU::SUB_A_L() { gen_SUB_A_n(registers.L); }
void CPU::SUB_A_HLp() { uint8_t n = memoryBus.readByte(registers.HL); gen_SUB_A_n(n); }
void CPU::SUB_A_A() { gen_SUB_A_n(registers.A); }
void CPU::SBC_A_B() { gen_SBC_A_n(registers.B); }
void CPU::SBC_A_C() { gen_SBC_A_n(registers.C); }
void CPU::SBC_A_D() { gen_SBC_A_n(registers.D); }
void CPU::SBC_A_E() { gen_SBC_A_n(registers.E); }
void CPU::SBC_A_H() { gen_SBC_A_n(registers.H); }
void CPU::SBC_A_L() { gen_SBC_A_n(registers.L); }
void CPU::SBC_A_HLp() { uint8_t n = memoryBus.readByte(registers.HL); gen_SBC_A_n(n); }
void CPU::SBC_A_A() { gen_SBC_A_n(registers.A); }

//Ax
void CPU::AND_B() { gen_AND_n(registers.B); }
void CPU::AND_C() { gen_AND_n(registers.C); }
void CPU::AND_D() { gen_AND_n(registers.D); }
void CPU::AND_E() { gen_AND_n(registers.E); }
void CPU::AND_H() { gen_AND_n(registers.H); }
void CPU::AND_L() { gen_AND_n(registers.L); }
void CPU::AND_HLp() { uint8_t n = memoryBus.readByte(registers.HL); gen_AND_n(n); }
void CPU::AND_A() { gen_AND_n(registers.A); }
void CPU::XOR_B() { gen_XOR_n(registers.B); }
void CPU::XOR_C() { gen_XOR_n(registers.C); }
void CPU::XOR_D() { gen_XOR_n(registers.D); }
void CPU::XOR_E() { gen_XOR_n(registers.E); }
void CPU::XOR_H() { gen_XOR_n(registers.H); }
void CPU::XOR_L() { gen_XOR_n(registers.L); }
void CPU::XOR_HLp() { uint8_t n = memoryBus.readByte(registers.HL); gen_XOR_n(n); }
void CPU::XOR_A() { gen_XOR_n(registers.A); }

//Bx
void CPU::OR_B() { gen_OR_n(registers.B); }
void CPU::OR_C() { gen_OR_n(registers.C); }
void CPU::OR_D() { gen_OR_n(registers.D); }
void CPU::OR_E() { gen_OR_n(registers.E); }
void CPU::OR_H() { gen_OR_n(registers.H); }
void CPU::OR_L() { gen_OR_n(registers.L); }
void CPU::OR_HLp() { uint8_t n = memoryBus.readByte(registers.HL); gen_OR_n(n); }
void CPU::OR_A() { gen_OR_n(registers.A); }
void CPU::CP_B() { gen_CP_n(registers.B); }
void CPU::CP_C() { gen_CP_n(registers.C); }
void CPU::CP_D() { gen_CP_n(registers.D); }
void CPU::CP_E() { gen_CP_n(registers.E); }
void CPU::CP_H() { gen_CP_n(registers.H); }
void CPU::CP_L() { gen_CP_n(registers.L); }
void CPU::CP_HLp() { uint8_t n = memoryBus.readByte(registers.HL); gen_CP_n(n); }
void CPU::CP_A() { gen_CP_n(registers.A); }

//Cx
void CPU::RET_NZ() { if(!flags.Z) RET(); }
void CPU::POP_BC() { registers.BC = memoryBus.readWord(sp); sp += 2; }
void CPU::JP_NZ_nn() { if(!flags.Z) JP_nn(); else pc += 2; }
void CPU::JP_nn() { pc = memoryBus.readWord(pc); }
void CPU::CALL_NZ_nn() { if(!flags.Z) CALL_nn(); else pc += 2; }
void CPU::PUSH_BC() { sp -= 2; memoryBus.writeWord(sp, registers.BC); }
void CPU::ADD_A_n() { uint8_t n = memoryBus.readByte(pc); pc++; gen_ADD_A_n(n); }
void CPU::RST_0() { sp -= 2; memoryBus.writeWord(sp, pc); pc = 0x00; }
void CPU::RET_Z() { if(flags.Z) RET(); }
void CPU::RET() { pc = memoryBus.readWord(sp); sp += 2; }
void CPU::JP_Z_nn() { if(flags.Z) JP_nn(); else pc += 2;}
void CPU::EXT_ops() {
    uint8_t currentOperation = memoryBus.readByte(pc);
    pc++;
    Instruction currentInstruction = extendedInstructions[currentOperation];
    logFile << std::hex << currentInstruction.disassembly << " " << (int)memoryBus.readByte(pc) << " " << (int)memoryBus.readByte(pc + 1) << std::endl;
    (this->*currentInstruction.function)();
    memoryBus.updateTimers(currentInstruction.cycles);
    ppu.renderCycles(currentInstruction.cycles);
    cyclesSinceFrameStart = cyclesSinceFrameStart + currentInstruction.cycles;
}
void CPU::CALL_Z_nn() { if(flags.Z) CALL_nn(); else pc += 2;}
void CPU::CALL_nn() { sp -= 2; memoryBus.writeWord(sp, pc + 2); JP_nn(); }
void CPU::ADC_A_n() { uint8_t n = memoryBus.readByte(pc); pc++; gen_ADC_A_n(n); }
void CPU::RST_8() { sp -= 2; memoryBus.writeWord(sp, pc); pc = 0x08; }

//Dx
void CPU::RET_NC() { if(!flags.C) RET(); }
void CPU::POP_DE() { registers.DE = memoryBus.readWord(sp); sp += 2; }
void CPU::JP_NC_nn() { if(!flags.C) JP_nn(); else pc += 2; }
//void CPU::void XXX() {}
void CPU::CALL_NC_nn() { if(!flags.C) CALL_nn(); else pc += 2; }
void CPU::PUSH_DE() { sp -= 2; memoryBus.writeWord(sp, registers.DE); }
void CPU::SUB_A_n() { uint8_t n = memoryBus.readByte(pc); pc++; gen_SUB_A_n(n); }
void CPU::RST_10() { sp -= 2; memoryBus.writeWord(sp, pc); pc = 0x10; }
void CPU::RET_C() { if(flags.C) RET(); }
void CPU::RETI() { RET(); interruptsEnabled = true; }
void CPU::JP_C_nn() { if(flags.C) JP_nn(); else pc += 2; }
//void CPU::XXX() {}
void CPU::CALL_C_nn() { if(flags.C) CALL_nn(); else pc += 2; }
//void CPU::XXX() {}
void CPU::SBC_A_n() { uint8_t n = memoryBus.readByte(pc); pc++; gen_SBC_A_n(n); }
void CPU::RST_18() { sp -= 2; memoryBus.writeWord(sp, pc); pc = 0x18; }

//Ex
void CPU::LDH_np_A() { uint8_t n = memoryBus.readByte(pc); pc++; memoryBus.writeByte(0xFF00 + n, registers.A); }
void CPU::POP_HL() { registers.HL = memoryBus.readWord(sp); sp += 2; }
void CPU::LDH_Cp_A() { memoryBus.writeByte(0xFF00 + registers.C, registers.A); }
//void CPU::XXX() {}
//void CPU::XXX() {}
void CPU::PUSH_HL() { sp -= 2; memoryBus.writeWord(sp, registers.HL); }
void CPU::AND_n() { uint8_t n = memoryBus.readByte(pc); pc++; gen_AND_n(n); }
void CPU::RST_20() { sp -= 2; memoryBus.writeWord(sp, pc); pc = 0x20; }
void CPU::ADD_SP_n() {
    uint8_t unsignedN = memoryBus.readByte(pc);
    pc++;
    int8_t signedN = *(int8_t*) &unsignedN;
    flags.H = (sp & 0x000F) + (signedN & 0x0F) > 0x000F;
    flags.C = (sp & 0x00FF) + (signedN & 0xFF) > 0x00FF;
    flags.Z = false;
    flags.N = false;
    sp = sp + signedN;
}
void CPU::JP_HL() { pc = registers.HL; }
void CPU::LD_nnp_A() { uint16_t nn = memoryBus.readWord(pc); pc += 2; memoryBus.writeByte(nn, registers.A); }
//void CPU::XXX() {}
//void CPU::XXX() {}
//void CPU::XXX() {}
void CPU::XOR_n() { uint8_t n = memoryBus.readByte(pc); pc++; gen_XOR_n(n); }
void CPU::RST_28() { sp -= 2; memoryBus.writeWord(sp, pc); pc = 0x28; }

//Fx
void CPU::LDH_A_np() { uint8_t n = memoryBus.readByte(pc); pc++; registers.A = memoryBus.readByte(0xFF00 + n); }
void CPU::POP_AF() { registers.AF = memoryBus.readWord(sp); sp += 2; registers.F = registers.F & 0xF0; flags.allFlags = registers.F; }
void CPU::LDH_A_Cp() { registers.A = memoryBus.readByte(0xFF00 + registers.C); }
void CPU::DI() { disableInterruptsNext = true; }
//void CPU::XXX() {}
void CPU::PUSH_AF() { uint16_t AF = (registers.A << 8) | flags.allFlags; sp -= 2; memoryBus.writeWord(sp, AF); }
void CPU::OR_n() { uint8_t n = memoryBus.readByte(pc); pc++; gen_OR_n(n); }
void CPU::RST_30() { sp -= 2; memoryBus.writeWord(sp, pc); pc = 0x30; }
void CPU::LDHL_SP_n() { //https://stackoverflow.com/questions/5159603/gbz80-how-does-ld-hl-spe-affect-h-and-c-flags
    uint8_t unsignedN = memoryBus.readByte(pc);
    pc++;
    int8_t signedN = *(int8_t*) &unsignedN;
    registers.HL = sp + signedN;
    flags.Z = false;
    flags.N = false;
    if(signedN >= 0) {
        flags.C = ((sp & 0xFF) + signedN) > 0xFF;
        flags.H = ((sp & 0xF) + (signedN & 0xF)) > 0xF;
    } else {
        flags.C = (registers.HL &  0xFF) <= (sp & 0xFF);
        flags.H = (registers.HL & 0xF) <= (sp & 0xF);
    }
}
void CPU::LD_SP_HL() { sp = registers.HL; }
void CPU::LD_A_nnp() { uint16_t nn = memoryBus.readWord(pc); pc += 2; registers.A = memoryBus.readByte(nn); }
void CPU::EI() { enableInterruptsNext = true; }
//void CPU::XXX() {}
//void CPU::XXX() {}
void CPU::CP_n() { uint8_t n = memoryBus.readByte(pc); pc++; gen_CP_n(n); }
void CPU::RST_38() { sp -= 2; memoryBus.writeWord(sp, pc); pc = 0x38; }
