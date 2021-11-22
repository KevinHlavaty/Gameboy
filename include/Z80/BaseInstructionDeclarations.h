
void gen_ADD_A_n(uint8_t numADDed);
void gen_ADC_A_n(uint8_t numADCed);

void gen_SUB_A_n(uint8_t numSUBed);
void gen_SBC_A_n(uint8_t numSBCed);

void gen_AND_n(uint8_t numANDed);
void gen_OR_n(uint8_t numORed);
void gen_XOR_n(uint8_t numXORed);

void gen_CP_n(uint8_t numCPed);

void gen_INC_n(uint8_t& numToINC);
void gen_DEC_n(uint8_t& numToDEC);

void gen_ADD_HL_n(uint16_t numADDed);

void XXX();

//0x
void nop();
void LD_BC_nn();
void LD_BCp_A();
void INC_BC();
void INC_B();
void DEC_B();
void LD_B_n();
void RLCA();
void LD_nnp_SP();
void ADD_HL_BC();
void LD_A_BCp();
void DEC_BC();
void INC_C();
void DEC_C();
void LD_C_n();
void RRCA();

//1x
void STOP();
void LD_DE_nn();
void LD_DEp_A();
void INC_DE();
void INC_D();
void DEC_D();
void LD_D_n();
void RLA();
void JR_n();
void ADD_HL_DE();
void LD_A_DEp();
void DEC_DE();
void INC_E();
void DEC_E();
void LD_E_n();
void RRA();

//2x
void JR_NZ_n();
void LD_HL_nn();
void LDI_HLp_A();
void INC_HL();
void INC_H();
void DEC_H();
void LD_H_n();
void DAA();
void JR_Z_n();
void ADD_HL_HL();
void LDI_A_HLp();
void DEC_HL();
void INC_L();
void DEC_L();
void LD_L_n();
void CPL();

//3x
void JR_NC_n();
void LD_SP_nn();
void LDD_HLp_A();
void INC_SP();
void INC_HLp();
void DEC_HLp();
void LD_HLp_n();
void SCF();
void JR_C_n();
void ADD_HL_SP();
void LDD_A_HLp();
void DEC_SP();
void INC_A();
void DEC_A();
void LD_A_n();
void CCF();

//4x
void LD_B_B();
void LD_B_C();
void LD_B_D();
void LD_B_E();
void LD_B_H();
void LD_B_L();
void LD_B_HLp();
void LD_B_A();
void LD_C_B();
void LD_C_C();
void LD_C_D();
void LD_C_E();
void LD_C_H();
void LD_C_L();
void LD_C_HLp();
void LD_C_A();

//5x
void LD_D_B();
void LD_D_C();
void LD_D_D();
void LD_D_E();
void LD_D_H();
void LD_D_L();
void LD_D_HLp();
void LD_D_A();
void LD_E_B();
void LD_E_C();
void LD_E_D();
void LD_E_E();
void LD_E_H();
void LD_E_L();
void LD_E_HLp();
void LD_E_A();

//6x
void LD_H_B();
void LD_H_C();
void LD_H_D();
void LD_H_E();
void LD_H_H();
void LD_H_L();
void LD_H_HLp();
void LD_H_A();
void LD_L_B();
void LD_L_C();
void LD_L_D();
void LD_L_E();
void LD_L_H();
void LD_L_L();
void LD_L_HLp();
void LD_L_A();

//7x
void LD_HLp_B();
void LD_HLp_C();
void LD_HLp_D();
void LD_HLp_E();
void LD_HLp_H();
void LD_HLp_L();
void HALT();
void LD_HLp_A();
void LD_A_B();
void LD_A_C();
void LD_A_D();
void LD_A_E();
void LD_A_H();
void LD_A_L();
void LD_A_HLp();
void LD_A_A();

//8x
void ADD_A_B();
void ADD_A_C();
void ADD_A_D();
void ADD_A_E();
void ADD_A_H();
void ADD_A_L();
void ADD_A_HLp();
void ADD_A_A();
void ADC_A_B();
void ADC_A_C();
void ADC_A_D();
void ADC_A_E();
void ADC_A_H();
void ADC_A_L();
void ADC_A_HLp();
void ADC_A_A();

//9x
void SUB_A_B();
void SUB_A_C();
void SUB_A_D();
void SUB_A_E();
void SUB_A_H();
void SUB_A_L();
void SUB_A_HLp();
void SUB_A_A();
void SBC_A_B();
void SBC_A_C();
void SBC_A_D();
void SBC_A_E();
void SBC_A_H();
void SBC_A_L();
void SBC_A_HLp();
void SBC_A_A();

//Ax
void AND_B();
void AND_C();
void AND_D();
void AND_E();
void AND_H();
void AND_L();
void AND_HLp();
void AND_A();
void XOR_B();
void XOR_C();
void XOR_D();
void XOR_E();
void XOR_H();
void XOR_L();
void XOR_HLp();
void XOR_A();

//Bx
void OR_B();
void OR_C();
void OR_D();
void OR_E();
void OR_H();
void OR_L();
void OR_HLp();
void OR_A();
void CP_B();
void CP_C();
void CP_D();
void CP_E();
void CP_H();
void CP_L();
void CP_HLp();
void CP_A();

//Cx
void RET_NZ();
void POP_BC();
void JP_NZ_nn();
void JP_nn();
void CALL_NZ_nn();
void PUSH_BC();
void ADD_A_n();
void RST_0();
void RET_Z();
void RET();
void JP_Z_nn();
void EXT_ops();
void CALL_Z_nn();
void CALL_nn();
void ADC_A_n();
void RST_8();

//Dx
void RET_NC();
void POP_DE();
void JP_NC_nn();
//void XXX();
void CALL_NC_nn();
void PUSH_DE();
void SUB_A_n();
void RST_10();
void RET_C();
void RETI();
void JP_C_nn();
//void XXX();
void CALL_C_nn();
//void XXX();
void SBC_A_n();
void RST_18();

//Ex
void LDH_np_A();
void POP_HL();
void LDH_Cp_A();
//void XXX();
//void XXX();
void PUSH_HL();
void AND_n();
void RST_20();
void ADD_SP_n();
void JP_HL();
void LD_nnp_A();
//void XXX();
//void XXX();
//void XXX();
void XOR_n();
void RST_28();

//Fx
void LDH_A_np();
void POP_AF();
void LDH_A_Cp();
void DI();
//void XXX();
void PUSH_AF();
void OR_n();
void RST_30();
void LDHL_SP_n();
void LD_SP_HL();
void LD_A_nnp();
void EI();
//void XXX();
//void XXX();
void CP_n();
void RST_38();
