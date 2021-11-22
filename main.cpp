
#include "CPU.h"

#include <iostream>
#include <chrono>
#include <windows.h>

#define FPS 60

int main(int argc, char* argv[]) {
    sf::RenderWindow window(sf::VideoMode(768, 768), "Gameboy", sf::Style::Titlebar | sf::Style::Close);
    MemoryBus memoryBus(argv[1]);
    PPU ppu(window, memoryBus);
    CPU cpu(memoryBus, ppu);
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while(window.pollEvent(event)) {
            // Window closed or escape key pressed: exit
            if((event.type == sf::Event::Closed) || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))) {
                window.close();
                break;
            }
        }
        auto frameStartTime = std::chrono::steady_clock::now();
        cpu.emulateFrame();
        auto frameEndTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(frameEndTime - frameStartTime).count();
        //std::cout << elapsedTime << std::endl;
        int millisecondsToSleep = (1000 / FPS) - elapsedTime;
        if (millisecondsToSleep < 0)
            millisecondsToSleep = 0;
        Sleep(millisecondsToSleep);
    }
    std::cout << "DONE" << std::endl;
    _sleep(5000);
    return 0;
}
