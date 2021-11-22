
#ifndef GAMEBOY_CPU_H
#define GAMEBOY_CPU_H

#include "MemoryBus.h"
#include "PPU.h"

#include <stack>
#include <cstdint>
#include <string>
#include <vector>
#include <fstream>

class CPU {

private:
    struct Registers {
        struct {
            union {
                struct {
                    uint8_t F;
                    uint8_t A;
                };
                uint16_t AF;
            };
        };

        struct {
            union {
                struct {
                    uint8_t C;
                    uint8_t B;
                };
                uint16_t BC;
            };
        };

        struct {
            union {
                struct {
                    uint8_t E;
                    uint8_t D;
                };
                uint16_t DE;
            };
        };

        struct {
            union {
                struct {
                    uint8_t L;
                    uint8_t H;
                };
                uint16_t HL;
            };
        };
    };

    union Flags {
        uint8_t allFlags;
        struct {
            bool padding: 4; //Only 4 flags, low 4 bits are not used
            bool C: 1; //Carry flag
            bool H: 1; //Half carry flag
            bool N: 1; //Subtraction flag
            bool Z: 1; //Zero flag
        };
    };

    struct Instruction {
        std::string disassembly;
        uint8_t cycles; //M-cycles
        void (CPU::*function)();
    };

private:
    #include "BaseInstructionDeclarations.h"
    #include "ExtendedInstructionDeclarations.h"
    void handleInterrupts();

private:
    std::vector<Instruction> baseInstructions;
    std::vector<Instruction> extendedInstructions;
    Registers registers;
    Flags flags;
    MemoryBus& memoryBus;
    PPU& ppu;
    uint16_t sp;
    uint16_t pc;
    int cyclesSinceFrameStart;
    bool interruptsEnabled;
    bool enableInterruptsNext;
    bool disableInterruptsNext;
    bool halted;
    std::ofstream logFile;

public:
    CPU(MemoryBus& memoryBus, PPU& ppu);
    ~CPU();
    void emulateFrame();
    void printInfo();

};

#endif //GAMEBOY_CPU_H
