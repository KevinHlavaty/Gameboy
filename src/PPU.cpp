
#include "PPU.h"

#include <iostream>
#include <cstring>

PPU::PPU(sf::RenderWindow& window, MemoryBus& memoryBus):
    window(window), memoryBus(memoryBus)
{
    cyclesPassed = 0;
    x = 0;
    y = 0;
    mode = 2;
    clocksSinceLastMode = 0;
    std::memset(image, WHITE, 256 * 256);
    memoryBus.writeByte(0xFF44, y);
}

PPU::~PPU() = default;

void PPU::renderCycles(int cycles) {
    if((memoryBus.readByte(0xFF40) & 0x80) == 0) {
        cyclesPassed = 0;
        memoryBus.writeByte(0xFF44, 0);
        mode = 0;
        uint8_t FF41 = memoryBus.readByte(0xFF41);
        FF41 = (FF41 & 0b11111100) | mode;
        memoryBus.writeByte(0xFF41, FF41);
        return;
    }

    cyclesPassed = cyclesPassed + cycles;
    int oldY = y;
    y = cyclesPassed / 114;
    memoryBus.writeByte(0xFF44, y);

    if(y == memoryBus.readByte(0xFF45) && y != oldY) {
        if((memoryBus.readByte(0xFF41) & 0b01000000) != 0 && (memoryBus.readByte(0xFFFF) & 0b00000010) != 0) {
            uint8_t oldInterrupts = memoryBus.readByte(0xFF0F);
            oldInterrupts = oldInterrupts | 0b000000010;
            memoryBus.writeByte(0xFF0F, oldInterrupts);
        }
    }

    clocksSinceLastMode = clocksSinceLastMode + cycles;
    if(mode == 2) { //Scanline accessing OAM
        if(clocksSinceLastMode >= 20) {
            mode = 3;
            clocksSinceLastMode = clocksSinceLastMode - 20;
        }
    } else if(mode == 3) { //Scanline accessing VRAM
        if(clocksSinceLastMode >= 43) {
            mode = 0;
            clocksSinceLastMode = clocksSinceLastMode - 43;
            uint8_t interruptsEnabled = memoryBus.readByte(0xFFFF);
            if(y < 144 && (memoryBus.readByte(0xFF41) & 0b00001000) != 0 && (interruptsEnabled & 0b00000010) != 0) {
                uint8_t oldInterrupts = memoryBus.readByte(0xFF0F);
                oldInterrupts = oldInterrupts | 0b000000010;
                memoryBus.writeByte(0xFF0F, oldInterrupts);
            }
        }
    } else if(mode == 1) {
        if(clocksSinceLastMode >= 1140) {
            mode = 2;
            clocksSinceLastMode = clocksSinceLastMode - 1140;
            cyclesPassed = cyclesPassed - 17556;
            uint8_t interruptsEnabled = memoryBus.readByte(0xFFFF);
            if((memoryBus.readByte(0xFF41) & 0b00100000) != 0 && (interruptsEnabled & 0b00000010) != 0) {
                uint8_t oldInterrupts = memoryBus.readByte(0xFF0F);
                oldInterrupts = oldInterrupts | 0b000000010;
                memoryBus.writeByte(0xFF0F, oldInterrupts);
            }
        }
    }

    if(mode == 0) { //Horizontal blank
        if(y < 145) {
            if(clocksSinceLastMode >= 51) {
                mode = 2;
                clocksSinceLastMode = clocksSinceLastMode - 51;
                uint8_t interruptsEnabled = memoryBus.readByte(0xFFFF);
                if((memoryBus.readByte(0xFF41) & 0b00100000) != 0 && (interruptsEnabled & 0b00000010) != 0) {
                    uint8_t oldInterrupts = memoryBus.readByte(0xFF0F);
                    oldInterrupts = oldInterrupts | 0b000000010;
                    memoryBus.writeByte(0xFF0F, oldInterrupts);
                }
            }
        } else {
            mode = 1; //It is a vertical blank, not horizontal
            displayImage();
            uint8_t interruptsEnabled = memoryBus.readByte(0xFFFF);
            if((memoryBus.readByte(0xFF41) & 0b00010000) != 0 && (interruptsEnabled & 0b00000010) != 0) {
                uint8_t oldInterrupts = memoryBus.readByte(0xFF0F);
                oldInterrupts = oldInterrupts | 0b000000010;
                memoryBus.writeByte(0xFF0F, oldInterrupts);
            }
            if((interruptsEnabled & 0b00000001) != 0 && (memoryBus.readByte(0xFF40) & 0x80) != 0) {
                uint8_t oldInterrupts = memoryBus.readByte(0xFF0F);
                oldInterrupts = oldInterrupts | 0b000000001;
                memoryBus.writeByte(0xFF0F, oldInterrupts);
            }
        }
    }

    uint8_t FF41 = memoryBus.readByte(0xFF41);
    FF41 = (FF41 & 0b11111100) | mode;
    memoryBus.writeByte(0xFF41, FF41);
}

void PPU::displayImage() {
    uint8_t LCDControl = memoryBus.readByte(0xFF40);
    int tileStartAddress = 0;
    int mapStartAddress = 0;
    bool signedTileIndexes;
    if((LCDControl & 0b00010000) == 0) {
        tileStartAddress = 0x9000;
        signedTileIndexes = true;
    } else {
        tileStartAddress = 0x8000;
        signedTileIndexes = false;
    }

    if((LCDControl & 0b00001000) == 0)
        mapStartAddress = 0x9800;
    else
        mapStartAddress = 0x9C00;

    auto* pixels = new sf::Uint8[256 * 256 * 4];

    //Draw background
    for(int row = 0; row < 256; row++) {
        for(int col = 0; col < 256; col++) {
            int currentMapAddress = mapStartAddress + ((row / 8) * 32) + (col / 8);
            uint8_t tempTileIndex = memoryBus.readByte(currentMapAddress);
            int currentTileIndex;
            if(signedTileIndexes) {
                currentTileIndex = *(int8_t*) &tempTileIndex;
            } else {
                currentTileIndex = tempTileIndex;
            }

            int tileAddress = tileStartAddress + (currentTileIndex * 16); //16 bytes per tile
            uint8_t firstSpriteByte = memoryBus.readByte(tileAddress + ((row % 8) * 2));
            uint8_t secondSpriteByte = memoryBus.readByte(tileAddress + (((row % 8) * 2) + 1));
            uint8_t colorValue = ((firstSpriteByte & (1 << (7 - (col % 8)))) != 0) | (((secondSpriteByte & (1 << (7 - (col % 8)))) != 0) << 1);
            if(colorValue == 0) {
                pixels[((row * 256) + col) * 4 + 0] = 255;
                pixels[((row * 256) + col) * 4 + 1] = 255;
                pixels[((row * 256) + col) * 4 + 2] = 255;
                pixels[((row * 256) + col) * 4 + 3] = 255;
            } else if(colorValue == 1) {
                pixels[((row * 256) + col) * 4 + 0] = 192;
                pixels[((row * 256) + col) * 4 + 1] = 192;
                pixels[((row * 256) + col) * 4 + 2] = 192;
                pixels[((row * 256) + col) * 4 + 3] = 255;
            } else if(colorValue == 2) {
                pixels[((row * 256) + col) * 4 + 0] = 96;
                pixels[((row * 256) + col) * 4 + 1] = 96;
                pixels[((row * 256) + col) * 4 + 2] = 96;
                pixels[((row * 256) + col) * 4 + 3] = 255;
            } else {
                pixels[((row * 256) + col) * 4 + 0] = 0;
                pixels[((row * 256) + col) * 4 + 1] = 0;
                pixels[((row * 256) + col) * 4 + 2] = 0;
                pixels[((row * 256) + col) * 4 + 3] = 255;
            }
        }
    }

    //Draw sprites
    for(int sprite = 0; sprite < 40; sprite++) {
        uint8_t ycoord = memoryBus.readByte(0xFE00 + (sprite * 4));
        uint8_t xcoord = memoryBus.readByte(0xFE00 + (sprite * 4) + 1);
        uint8_t dataTile = memoryBus.readByte(0xFE00 + (sprite * 4) + 2);
        uint8_t info = memoryBus.readByte(0xFE00 + (sprite * 4) + 3); //Currently unused

        uint16_t tileAddress = 0x8000 + (dataTile * 16);
        for(int row = 0; row < 8; row++) {
            for(int col = 0; col < 8; col++) {
                uint8_t firstSpriteByte = memoryBus.readByte(tileAddress + (row * 2));
                uint8_t secondSpriteByte = memoryBus.readByte(tileAddress + ((row * 2) + 1));
                int pixelY = (ycoord - 16) + row;
                int pixelX = (xcoord - 8) + col;

                if(pixelY < 0 || pixelX < 0 || pixelY > 255 || pixelX > 255)
                    continue;

                uint8_t colorValue = ((firstSpriteByte & (1 << (7 - (col % 8)))) != 0) | (((secondSpriteByte & (1 << (7 - (col % 8)))) != 0) << 1);

                if(colorValue == 0) {
                    pixels[(pixelY * 256 + pixelX) * 4 + 0] = 255;
                    pixels[(pixelY * 256 + pixelX) * 4 + 1] = 255;
                    pixels[(pixelY * 256 + pixelX) * 4 + 2] = 255;
                    pixels[(pixelY * 256 + pixelX) * 4 + 3] = 255;
                } else if(colorValue == 1) {
                    pixels[(pixelY * 256 + pixelX) * 4 + 0] = 192;
                    pixels[(pixelY * 256 + pixelX) * 4 + 1] = 192;
                    pixels[(pixelY * 256 + pixelX) * 4 + 2] = 192;
                    pixels[(pixelY * 256 + pixelX) * 4 + 3] = 255;
                } else if(colorValue == 2) {
                    pixels[(pixelY * 256 + pixelX) * 4 + 0] = 96;
                    pixels[(pixelY * 256 + pixelX) * 4 + 1] = 96;
                    pixels[(pixelY * 256 + pixelX) * 4 + 2] = 96;
                    pixels[(pixelY * 256 + pixelX) * 4 + 3] = 255;
                } else {
                    pixels[(pixelY * 256 + pixelX) * 4 + 0] = 0;
                    pixels[(pixelY * 256 + pixelX) * 4 + 1] = 0;
                    pixels[(pixelY * 256 + pixelX) * 4 + 2] = 0;
                    pixels[(pixelY * 256 + pixelX) * 4 + 3] = 255;
                }
            }
        }
    }

    sf::Image pixelImage;
    pixelImage.create(256, 256, pixels);
    sf::Texture texture;
    texture.loadFromImage(pixelImage);
    sf::Sprite sprite(texture);
    sprite.setScale(3, 3);
    window.draw(sprite);
    window.display();
    delete[] pixels;
}
