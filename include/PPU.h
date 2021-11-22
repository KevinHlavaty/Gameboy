
#ifndef GAMEBOY_PPU_H
#define GAMEBOY_PPU_H

#include "MemoryBus.h"

#include <SFML/Graphics.hpp>

class PPU {

public:
    enum Color {
        WHITE,
        LIGHT_GREY,
        DARK_GREY,
        BLACK
    };

private:
    Color image[256][256];
    sf::RenderWindow& window;
    MemoryBus& memoryBus;
    int cyclesPassed;
    int x;
    int y;
    int mode;
    int clocksSinceLastMode;

public:
    PPU(sf::RenderWindow& window, MemoryBus& memoryBus);
    ~PPU();
    void renderCycles(int cycles);
    void displayImage();

};

#endif //GAMEBOY_PPU_H
