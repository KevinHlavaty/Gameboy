
//0x
{"nop", 1, &CPU::nop},
{"LD BC,nn", 3, &CPU::LD_BC_nn},
{"LD (BC),A", 2, &CPU::LD_BCp_A},
{"INC BC", 2, &CPU::INC_BC},
{"INC B", 1, &CPU::INC_B},
{"DEC B", 1, &CPU::DEC_B},
{"LD B,n", 2, &CPU::LD_B_n},
{"RLC A", 1, &CPU::RLCA},
{"LD (nn),SP", 5, &CPU::LD_nnp_SP},
{"ADD HL,BC", 2, &CPU::ADD_HL_BC},
{"LD A,(BC)", 2, &CPU::LD_A_BCp},
{"DEC BC", 2, &CPU::DEC_BC},
{"INC C", 1, &CPU::INC_C},
{"DEC C", 1, &CPU::DEC_C},
{"LD C,n", 2, &CPU::LD_C_n},
{"RRC A", 1, &CPU::RRCA},

//1x
{"STOP", 1, &CPU::STOP},
{"LD DE,nn", 3, &CPU::LD_DE_nn},
{"LD (DE),A", 2, &CPU::LD_DEp_A},
{"INC DE", 2, &CPU::INC_DE},
{"INC D", 1, &CPU::INC_D},
{"DEC D", 1, &CPU::DEC_D},
{"LD D,n", 2, &CPU::LD_D_n},
{"RL A", 1, &CPU::RLA},
{"JR n", 3, &CPU::JR_n},
{"ADD HL,DE", 2, &CPU::ADD_HL_DE},
{"LD A,(DE)", 2, &CPU::LD_A_DEp},
{"DEC DE", 2, &CPU::DEC_DE},
{"INC E", 1, &CPU::INC_E},
{"DEC E", 1, &CPU::DEC_E},
{"LD E,n", 2, &CPU::LD_E_n},
{"RR A", 1, &CPU::RRA},

//2x
{"JR NZ,n", 2, &CPU::JR_NZ_n},
{"LD HL,nn", 3, &CPU::LD_HL_nn},
{"LDI (HL),A", 2, &CPU::LDI_HLp_A},
{"INC HL", 2, &CPU::INC_HL},
{"INC H", 1, &CPU::INC_H},
{"DEC H", 1, &CPU::DEC_H},
{"LD H,n", 2, &CPU::LD_H_n},
{"DAA", 1, &CPU::DAA},
{"JR Z,n", 2, &CPU::JR_Z_n},
{"ADD HL,HL", 2, &CPU::ADD_HL_HL},
{"LDI A,(HL)", 2, &CPU::LDI_A_HLp},
{"DEC HL", 2, &CPU::DEC_HL},
{"INC L", 1, &CPU::INC_L},
{"DEC L", 1, &CPU::DEC_L},
{"LD L,n", 2, &CPU::LD_L_n},
{"CPL", 1, &CPU::CPL},

//3x
{"JR NC,n", 2, &CPU::JR_NC_n},
{"LD SP,nn", 3, &CPU::LD_SP_nn},
{"LDD (HL),A", 2, &CPU::LDD_HLp_A},
{"INC SP", 2, &CPU::INC_SP},
{"INC (HL)", 3, &CPU::INC_HLp},
{"DEC (HL)", 3, &CPU::DEC_HLp},
{"LD (HL), n", 3, &CPU::LD_HLp_n},
{"SCF", 1, &CPU::SCF},
{"JR C,n", 2, &CPU::JR_C_n},
{"ADD HL,SP", 2, &CPU::ADD_HL_SP},
{"LDD A,(HL)", 2, &CPU::LDD_A_HLp},
{"DEC SP", 2, &CPU::DEC_SP},
{"INC A", 1, &CPU::INC_A},
{"DEC A", 1, &CPU::DEC_A},
{"LD A,n", 2, &CPU::LD_A_n},
{"CCF", 1, &CPU::CCF},

//4x
{"LD B,B", 1, &CPU::LD_B_B},
{"LD B,C", 1, &CPU::LD_B_C},
{"LD B,D", 1, &CPU::LD_B_D},
{"LD B,E", 1, &CPU::LD_B_E},
{"LD B,H", 1, &CPU::LD_B_H},
{"LD B,L", 1, &CPU::LD_B_L},
{"LD B,(HL)", 2, &CPU::LD_B_HLp},
{"LD B,A", 1, &CPU::LD_B_A},
{"LD C,B", 1, &CPU::LD_C_B},
{"LD C,C", 1, &CPU::LD_C_C},
{"LD C,D", 1, &CPU::LD_C_D},
{"LD C,E", 1, &CPU::LD_C_E},
{"LD C,H", 1, &CPU::LD_C_H},
{"LD C,L", 1, &CPU::LD_C_L},
{"LD C,(HL)", 2, &CPU::LD_C_HLp},
{"LD C,A", 1, &CPU::LD_C_A},

//5x
{"LD D,B", 1, &CPU::LD_D_B},
{"LD D,C", 1, &CPU::LD_D_C},
{"LD D,D", 1, &CPU::LD_D_D},
{"LD D,E", 1, &CPU::LD_D_E},
{"LD D,H", 1, &CPU::LD_D_H},
{"LD D,L", 1, &CPU::LD_D_L},
{"LD D,(HL)", 2, &CPU::LD_D_HLp},
{"LD D,A", 1, &CPU::LD_D_A},
{"LD E,B", 1, &CPU::LD_E_B},
{"LD E,C", 1, &CPU::LD_E_C},
{"LD E,D", 1, &CPU::LD_E_D},
{"LD E,E", 1, &CPU::LD_E_E},
{"LD E,H", 1, &CPU::LD_E_H},
{"LD E,L", 1, &CPU::LD_E_L},
{"LD E,(HL)", 2, &CPU::LD_E_HLp},
{"LD E,A", 1, &CPU::LD_E_A},

//6x
{"LD H,B", 1, &CPU::LD_H_B},
{"LD H,C", 1, &CPU::LD_H_C},
{"LD H,D", 1, &CPU::LD_H_D},
{"LD H,E", 1, &CPU::LD_H_E},
{"LD H,H", 1, &CPU::LD_H_H},
{"LD H,L", 1, &CPU::LD_H_L},
{"LD H,(HL)", 2, &CPU::LD_H_HLp},
{"LD H,A", 1, &CPU::LD_H_A},
{"LD L,B", 1, &CPU::LD_L_B},
{"LD L,C", 1, &CPU::LD_L_C},
{"LD L,D", 1, &CPU::LD_L_D},
{"LD L,E", 1, &CPU::LD_L_E},
{"LD L,H", 1, &CPU::LD_L_H},
{"LD L,L", 1, &CPU::LD_L_L},
{"LD L,(HL)", 2, &CPU::LD_L_HLp},
{"LD L,A", 1, &CPU::LD_L_A},

//7x
{"LD (HL),B", 2, &CPU::LD_HLp_B},
{"LD (HL),C", 2, &CPU::LD_HLp_C},
{"LD (HL),D", 2, &CPU::LD_HLp_D},
{"LD (HL),E", 2, &CPU::LD_HLp_E},
{"LD (HL),H", 2, &CPU::LD_HLp_H},
{"LD (HL),L", 2, &CPU::LD_HLp_L},
{"HALT", 1, &CPU::HALT},
{"LD (HL),A", 2, &CPU::LD_HLp_A},
{"LD A,B", 1, &CPU::LD_A_B},
{"LD A,C", 1, &CPU::LD_A_C},
{"LD A,D", 1, &CPU::LD_A_D},
{"LD A,E", 1, &CPU::LD_A_E},
{"LD A,H", 1, &CPU::LD_A_H},
{"LD A,L", 1, &CPU::LD_A_L},
{"LD A,(HL)", 2, &CPU::LD_A_HLp},
{"LD A,A", 1, &CPU::LD_A_A},

//8x
{"ADD A,B", 1, &CPU::ADD_A_B},
{"ADD A,C", 1, &CPU::ADD_A_C},
{"ADD A,D", 1, &CPU::ADD_A_D},
{"ADD A,E", 1, &CPU::ADD_A_E},
{"ADD A,H", 1, &CPU::ADD_A_H},
{"ADD A,L", 1, &CPU::ADD_A_L},
{"ADD A,(HL)", 2, &CPU::ADD_A_HLp},
{"ADD A,A", 1, &CPU::ADD_A_A},
{"ADC A,B", 1, &CPU::ADC_A_B},
{"ADC A,C", 1, &CPU::ADC_A_C},
{"ADC A,D", 1, &CPU::ADC_A_D},
{"ADC A,E", 1, &CPU::ADC_A_E},
{"ADC A,H", 1, &CPU::ADC_A_H},
{"ADC A,L", 1, &CPU::ADC_A_L},
{"ADC A,(HL)", 2, &CPU::ADC_A_HLp},
{"ADC A,A", 1, &CPU::ADC_A_A},

//9x
{"SUB A,B", 1, &CPU::SUB_A_B},
{"SUB A,C", 1, &CPU::SUB_A_C},
{"SUB A,D", 1, &CPU::SUB_A_D},
{"SUB A,E", 1, &CPU::SUB_A_E},
{"SUB A,H", 1, &CPU::SUB_A_H},
{"SUB A,L", 1, &CPU::SUB_A_L},
{"SUB A,(HL)", 2, &CPU::SUB_A_HLp},
{"SUB A,A", 1, &CPU::SUB_A_A},
{"SBC A,B", 1, &CPU::SBC_A_B},
{"SBC A,C", 1, &CPU::SBC_A_C},
{"SBC A,D", 1, &CPU::SBC_A_D},
{"SBC A,E", 1, &CPU::SBC_A_E},
{"SBC A,H", 1, &CPU::SBC_A_H},
{"SBC A,L", 1, &CPU::SBC_A_L},
{"SBC A,(HL)", 2, &CPU::SBC_A_HLp},
{"SBC A,A", 1, &CPU::SBC_A_A},

//Ax
{"AND B", 1, &CPU::AND_B},
{"AND C", 1, &CPU::AND_C},
{"AND D", 1, &CPU::AND_D},
{"AND E", 1, &CPU::AND_E},
{"AND H", 1, &CPU::AND_H},
{"AND L", 1, &CPU::AND_L},
{"AND (HL)", 2, &CPU::AND_HLp},
{"AND A", 1, &CPU::AND_A},
{"XOR B", 1, &CPU::XOR_B},
{"XOR C", 1, &CPU::XOR_C},
{"XOR D", 1, &CPU::XOR_D},
{"XOR E", 1, &CPU::XOR_E},
{"XOR H", 1, &CPU::XOR_H},
{"XOR L", 1, &CPU::XOR_L},
{"XOR (HL)", 2, &CPU::XOR_HLp},
{"XOR A", 1, &CPU::XOR_A},

//Bx
{"OR B", 1, &CPU::OR_B},
{"OR C", 1, &CPU::OR_C},
{"OR D", 1, &CPU::OR_D},
{"OR E", 1, &CPU::OR_E},
{"OR H", 1, &CPU::OR_H},
{"OR L", 1, &CPU::OR_L},
{"OR (HL)", 2, &CPU::OR_HLp},
{"OR A", 1, &CPU::OR_A},
{"CP B", 1, &CPU::CP_B},
{"CP C", 1, &CPU::CP_C},
{"CP D", 1, &CPU::CP_D},
{"CP E", 1, &CPU::CP_E},
{"CP H", 1, &CPU::CP_H},
{"CP L", 1, &CPU::CP_L},
{"CP (HL)", 2, &CPU::CP_HLp},
{"CP A", 1, &CPU::CP_A},

//Cx
{"RET NZ", 2, &CPU::RET_NZ},
{"POP BC", 3, &CPU::POP_BC},
{"JP NZ,nn", 3, &CPU::JP_NZ_nn},
{"JP nn", 4, &CPU::JP_nn},
{"CALL NZ,nn", 3, &CPU::CALL_NZ_nn},
{"PUSH BC", 4, &CPU::PUSH_BC},
{"ADD A,n", 2, &CPU::ADD_A_n},
{"RST 0", 4, &CPU::RST_0},
{"RET Z", 2, &CPU::RET_Z},
{"RET", 4, &CPU::RET},
{"JP Z,nn", 3, &CPU::JP_Z_nn},
{"EXT ops", 0, &CPU::EXT_ops},
{"CALL Z,nn", 3, &CPU::CALL_Z_nn},
{"CALL nn", 6, &CPU::CALL_nn},
{"ADC A,n", 2, &CPU::ADC_A_n},
{"RST 8", 4, &CPU::RST_8},

//Dx
{"RET NC", 2, &CPU::RET_NC},
{"POP DE", 3, &CPU::POP_DE},
{"JP_NC_nn", 3, &CPU::JP_NC_nn},
{"XXX", 0, &CPU::XXX},
{"CALL NC,nn", 3, &CPU::CALL_NC_nn},
{"PUSH DE", 4, &CPU::PUSH_DE},
{"SUB A,n", 2, &CPU::SUB_A_n},
{"RST 10", 4, &CPU::RST_10},
{"RET C", 2, &CPU::RET_C},
{"RETI", 4, &CPU::RETI},
{"JP C,nn", 3, &CPU::JP_C_nn},
{"XXX", 0, &CPU::XXX},
{"CALL C,nn", 3, &CPU::CALL_C_nn},
{"XXX", 0, &CPU::XXX},
{"SBC A,n", 2, &CPU::SBC_A_n},
{"RST 18", 4, &CPU::RST_18},

//Ex
{"LDH (n),A", 3, &CPU::LDH_np_A},
{"POP HL", 3, &CPU::POP_HL},
{"LDH (C),A", 2, &CPU::LDH_Cp_A},
{"XXX", 0, &CPU::XXX},
{"XXX", 0, &CPU::XXX},
{"PUSH HL", 4, &CPU::PUSH_HL},
{"AND n", 2, &CPU::AND_n},
{"RST 20", 4, &CPU::RST_20},
{"ADD_SP_n", 4, &CPU::ADD_SP_n},
{"JP (HL)", 1, &CPU::JP_HL},
{"LD (nn),A", 4, &CPU::LD_nnp_A},
{"XXX", 0, &CPU::XXX},
{"XXX", 0, &CPU::XXX},
{"XXX", 0, &CPU::XXX},
{"XOR n", 2, &CPU::XOR_n},
{"RST 28", 4, &CPU::RST_28},

//Fx
{"LDH A,(n)", 3, &CPU::LDH_A_np},
{"POP AF", 3, &CPU::POP_AF},
{"LD A,(C)", 2, &CPU::LDH_A_Cp},
{"DI", 1, &CPU::DI},
{"XXX", 0, &CPU::XXX},
{"PUSH AF", 4, &CPU::PUSH_AF},
{"OR n", 2, &CPU::OR_n},
{"RST 30", 4, &CPU::RST_30},
{"LDHL SP,n", 3, &CPU::LDHL_SP_n},
{"LD SP,HL", 2, &CPU::LD_SP_HL},
{"LD A,(nn)", 4, &CPU::LD_A_nnp},
{"EI", 1, &CPU::EI},
{"XXX", 0, &CPU::XXX},
{"XXX", 0, &CPU::XXX},
{"CP n", 2, &CPU::CP_n},
{"RST 38", 4, &CPU::RST_38}
