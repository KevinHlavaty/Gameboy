
#ifndef GAMEBOY_MEMORYBUS_H
#define GAMEBOY_MEMORYBUS_H

#include <cstdint>
#include <fstream>
#include <vector>

#define CLOCK_SPEED 1048576

class MemoryBus {

private:
    std::vector<uint8_t> ROM1;
    std::vector<uint8_t> ROM2;
    std::vector<uint8_t> VRAM;
    std::vector<uint8_t> extendedRAM;
    std::vector<uint8_t> workingRAM;
    std::vector<uint8_t> zeroPageRAM;
    int ROMBank;
    int RAMBank;
    int dividerLeftOverCycles;
    int counterLeftOverCycles;
    std::ofstream* logFile;

private:
    void handleInput();

public:
    explicit MemoryBus(char* filename);
    ~MemoryBus();

    void takeLogFile(std::ofstream* logfile);

    uint8_t readByte(uint16_t address);
    uint16_t readWord(uint16_t address);
    void writeByte(uint16_t address, uint8_t byte);
    void writeWord(uint16_t address, uint16_t word);
    void updateTimers(int cycles);
    void printSprites();

};

#endif //GAMEBOY_MEMORYBUS_H
