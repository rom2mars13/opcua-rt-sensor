#include "Engine.h"
#include <chrono>

Engine::Engine() {
    // Initialise la température à 25
    temperature = 25;

    // Indique que le thread doit tourner
    running = true;

    // Lance la boucle updateLoop dans un nouveau thread
    worker = std::thread(&Engine::updateLoop, this);
}

Engine::~Engine() {
    // Signal the thread to stop and wait for it to finish
    running = false;
    if (worker.joinable())
        worker.join();
}

void Engine::updateLoop() {
    // Loop until 'running' is false
    while (running) {
        // Increment temperature by 1
        temperature++;

        // Sleep for 1 second between updates
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int Engine::getTemperature() const {
    // Return the latest temperature value (thread-safe)
    return temperature.load();
}
