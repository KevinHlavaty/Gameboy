
#include "CPU.h"

#include <iostream>

#define CYCLES_PER_FRAME (CLOCK_SPEED / 60)

CPU::CPU(MemoryBus& memoryBus, PPU& ppu):
    memoryBus(memoryBus), ppu(ppu)
{
    registers.A = 0x11;
    flags.allFlags = 0xB0;
    registers.BC = 0x0013;
    registers.DE = 0x00D8;
    registers.HL = 0x014D;

    logFile.open("../output.txt", std::ofstream::out | std::ofstream::trunc);

    pc = 0x100;
    sp = 0xFFFE;

    interruptsEnabled = false;
    halted = false;
    enableInterruptsNext = false;
    disableInterruptsNext = false;

    cyclesSinceFrameStart = 0;

    baseInstructions = {
        #include "BaseInstructionInitializers.h"
    };

    extendedInstructions = {
        #include "ExtendedInstructionInitializers.h"
    };

    memoryBus.takeLogFile(&logFile);
}

CPU::~CPU() = default;

#include "BaseInstructionImplementations.h"

#include "ExtendedInstructionImplementations.h"

void CPU::emulateFrame() {
    OUTER_LOOP:
    while(cyclesSinceFrameStart < CYCLES_PER_FRAME) {
        handleInterrupts();
        while(halted) {
            ppu.renderCycles(1);
            memoryBus.updateTimers(1);
            cyclesSinceFrameStart = cyclesSinceFrameStart + 1;
            if(cyclesSinceFrameStart >= CYCLES_PER_FRAME)
                goto OUTER_LOOP;
            handleInterrupts();
        }
        if (enableInterruptsNext) {
            interruptsEnabled = true;
            enableInterruptsNext = false;
        }
        if (disableInterruptsNext) {
            interruptsEnabled = false;
            disableInterruptsNext = false;
        }
        //logFile << std::endl;
        //logFile << std::hex << "pc: " << pc << "  ";
        uint8_t currentOperation = memoryBus.readByte(pc);
        Instruction currentInstruction = baseInstructions[currentOperation];
        pc++;
        //printInfo();
        //logFile << std::hex << currentInstruction.disassembly << " " << (int)memoryBus.readByte(pc) << " " <<
        //        (int)memoryBus.readByte(pc + 1) << ",    " << (int) currentInstruction.cycles << std::endl;
        (this->*currentInstruction.function)();
        memoryBus.updateTimers(currentInstruction.cycles);
        ppu.renderCycles(currentInstruction.cycles);
        cyclesSinceFrameStart = cyclesSinceFrameStart + currentInstruction.cycles;
    }
    cyclesSinceFrameStart = 0;
}

void CPU::handleInterrupts() {
    uint8_t interruptsToHandle = memoryBus.readByte(0xFF0F) & memoryBus.readByte(0xFFFF);
    if(interruptsToHandle == 0)
        return;

    halted = false;
    if(!interruptsEnabled)
        return;

    interruptsEnabled = false;
    sp -= 2;
    memoryBus.writeWord(sp, pc);
    uint8_t pendingInterrupts = memoryBus.readByte(0xFF0F);
    if((interruptsToHandle & 0b00000001) != 0) { //vblank
        pc = 0x0040;
        memoryBus.writeByte(0xFF0F, pendingInterrupts & 0b11111110);
    } else if((interruptsToHandle & 0b00000010) != 0) { //lcd stat
        pc = 0x0048;
        memoryBus.writeByte(0xFF0F, pendingInterrupts & 0b11111101);
    } else if((interruptsToHandle & 0b00000100) != 0) { //Timer
        pc = 0x0050;
        memoryBus.writeByte(0xFF0F, pendingInterrupts & 0b11111011);
    } else if((interruptsToHandle & 0b00001000) != 0) { //Serial
        pc = 0x0058;
        memoryBus.writeByte(0xFF0F, pendingInterrupts & 0b11110111);
    } else if((interruptsToHandle & 0b00010000) != 0) { //Joypad
        pc = 0x0060;
        memoryBus.writeByte(0xFF0F, pendingInterrupts & 0b11101111);
    } else {
        std::cout << "UNKNOWN INTERRUPT" << std::endl;
    }
}

void CPU::printInfo() {
    logFile << std::endl;
    logFile << "Reg A: " << (int) registers.A << " Reg F: " << (int) flags.allFlags << std::endl;
    logFile << "Reg B: " << (int) registers.B << " Reg C: " << (int) registers.C << std::endl;
    logFile << "Reg D: " << (int) registers.D << " Reg E: " << (int) registers.E << std::endl;
    logFile << "Reg H: " << (int) registers.H << " Reg L: " << (int) registers.L << std::endl;
    logFile << "0xFF04: " << (int) memoryBus.readByte(0xFF04) << " 0xFF05: " << (int) memoryBus.readByte(0xFF05) << std::endl;
}
