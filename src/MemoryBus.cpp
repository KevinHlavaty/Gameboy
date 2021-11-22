

#include "MemoryBus.h"

#include <SFML/Window.hpp>

#include <cstdio>
#include <cstring>
#include <iostream>

MemoryBus::MemoryBus(char* filename):
    ROM1(0x4000), ROM2(), VRAM(0x2000), extendedRAM(0x2000), workingRAM(0x4000)
{
    ROMBank = 1;
    RAMBank = 1;
    dividerLeftOverCycles = 0;
    counterLeftOverCycles = 0;
    FILE* rom = std::fopen(filename, "rb");
    if(rom == nullptr)
        std::cout << "NULLLLLL" << std::endl;

    std::fread(&ROM1[0], sizeof(uint8_t), 0x4000, rom);

    uint8_t buffer[0x4000]; //16kb
    size_t bytesRead;
    while((bytesRead = std::fread(buffer, sizeof(uint8_t), 0x4000, rom)) != 0) {
        for(int i = 0; i < bytesRead; i++) {
            ROM2.push_back(buffer[i]);
        }
    }
    std::cout << std::hex << "MCB THING" << (int)ROM1[0x147] << std::endl;

    writeByte(0xFF40, 0x91);
    workingRAM[0xFF04 % 0x4000] = 0x44;
}

MemoryBus::~MemoryBus() = default;

void MemoryBus::takeLogFile(std::ofstream* logFile) {
    this->logFile = logFile;
}

uint8_t MemoryBus::readByte(uint16_t address) {
    if(address < 0x4000) {
        return ROM1[address];
    } else if(address < 0x8000) {
        return ROM2[(0x4000 * (ROMBank - 1)) + (address % 0x4000)];
    } else if(address < 0xA000) {
        return VRAM[address % 0x2000];
    } else if(address < 0xC000) {
        std::cout << "READING EXTENDED RAM" << std::endl;
        return extendedRAM[(0x2000 * (RAMBank - 1)) + (address % 0x2000)];
    } else {
        return workingRAM[address % 0x4000];
    }
}

uint16_t MemoryBus::readWord(uint16_t address) {
    return (readByte(address + 1) << 8) | readByte(address);
}

void MemoryBus::writeByte(uint16_t address, uint8_t byte) {
    if(address < 0x4000) {
        if(address < 0x2000) {
            //enable external RAM
            std::cout << "ENABLE EXTERNAL RAM" << std::endl;
        } else {
            std::cout << "SWITCH ROM BANK" << (int) byte << std::endl;
            ROMBank = byte & 0b00011111;
        }
    } else if(address < 0x8000) {
        if(address < 0x6000) {
            //switch bank "set"
            std::cout << "SWITCH BANK SET" << std::endl;
        } else {
            //change rom mode / ram mode
            std::cout << "CHANGE ROM / RAM MODE" << std::endl;
        }
    } else if(address < 0xA000) {
        VRAM[address % 0x2000] = byte;
    } else if(address < 0xC000) {
        extendedRAM[(0x2000 * (RAMBank - 1)) + (address % 0x2000)] = byte;
    } else {
        if(address == 0xFF00) { //Input
            std::cout << "INPUT" << std::endl;
            workingRAM[0xFF00 % 0x4000] = byte;
            handleInput();
        } else if(address == 0xFF04) { //Reset timer
            workingRAM[0xFF04 % 0x4000] = 0;
            workingRAM[0xFF05 % 0x4000] = readByte(0xFF06);
            dividerLeftOverCycles = 0;
            counterLeftOverCycles = 0;
        } else if(address == 0xFF46) { //DMA transfer
            uint16_t sourceStart = byte * 0x100;
            uint16_t destinationStart = 0xFE00;
            for(int i = 0; i < 40 * 4; i++) { //Transfer 40 sprites * 4 bytes per sprite
                writeByte(destinationStart + i, readByte(sourceStart + i));
            }
        }
        else {
            workingRAM[address % 0x4000] = byte;
        }
    }
}

void MemoryBus::writeWord(uint16_t address, uint16_t word) {
    writeByte(address + 1, word >> 8);
    writeByte(address, word & 0x00FF);
}

void MemoryBus::updateTimers(int cycles) {
    dividerLeftOverCycles = dividerLeftOverCycles + cycles;
    if(dividerLeftOverCycles >= CLOCK_SPEED / 16384) {
        uint8_t divider = readByte(0xFF04);
        workingRAM[0xFF04 % 0x4000] = divider + 1; //The divider resets when written to with writeByte()
        dividerLeftOverCycles = dividerLeftOverCycles - (CLOCK_SPEED / 16384);
    }

    uint8_t control = readByte(0xFF07);
    if((control & 0b00000100) == 0) {
        return; //If bit 2 is 0, counter is not active
    }

    counterLeftOverCycles = counterLeftOverCycles + cycles;
    uint8_t speed = control & 0b00000011;
    int hertz;
    if(speed == 0)
        hertz = 4096;
    else if(speed == 1)
        hertz = 262144;
    else if(speed == 2)
        hertz = 65536;
    else
        hertz = 16384;

    while(counterLeftOverCycles >= CLOCK_SPEED / hertz) {
        counterLeftOverCycles = counterLeftOverCycles - (CLOCK_SPEED / hertz);
        uint8_t counter = readByte(0xFF05);
        if(counter == 0xFF) {
            counter = readByte(0xFF06);
            writeByte(0xFF05, counter);
            if((readByte(0xFFFF) & 0b00000100) != 0) {
                uint8_t oldInterrupts = readByte(0xFF0F);
                oldInterrupts = oldInterrupts | 0b00000100;
                writeByte(0xFF0F, oldInterrupts);
            }
        } else {
            counter++;
            writeByte(0xFF05, counter);
        }

    }
}

void MemoryBus::printSprites() {
    int i = 0xFE00;
    while(i <= 0xFE9F) {
        for(int j = 0; j < 8; j++) {
            std::cout << (int) readByte(i);
            i++;
        }
        std::cout << std::endl;
    }
}

void MemoryBus::handleInput() {
    uint8_t FF00 = workingRAM[0xFF00 % 0x4000];
    if(FF00 == 0x20) {
        FF00 = FF00 | 0x0F;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            FF00 = FF00 & 0b0111;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            FF00 = FF00 & 0b1011;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            FF00 = FF00 & 0b1101;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            FF00 = FF00 & 0b1110;
    } else {
        FF00 = FF00 | 0x0F;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            FF00 = FF00 & 0b0111;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            FF00 = FF00 & 0b1011;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::X))
            FF00 = FF00 & 0b1101;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            FF00 = FF00 & 0b1110;
    }
    workingRAM[0xFF00 % 0x4000] = FF00;
    std::cout << "FF00: " << std::hex << (int) readByte(0xFF00) << std::endl;
}
