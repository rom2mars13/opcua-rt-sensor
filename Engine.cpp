#include <random>
#include <mutex>
#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>

class Engine {
public:
    Engine();
    ~Engine();

    int getTemperature();
    void setTemperature(int temp);

    void startUpdating();
    void stopUpdating();

private:
    void updateLoop();

    int temperature;

    std::mutex mtx;

    std::atomic<bool> running;
    std::thread updateThread;
};

// Implementation

Engine::Engine() {
    // Initialize temperature with a default value
    temperature = 20;
    startUpdating();
}

Engine::~Engine() {
    stopUpdating();
}

int Engine::getTemperature() {
    std::lock_guard<std::mutex> lock(mtx);
    return temperature;
}

void Engine::setTemperature(int temp) {
    std::lock_guard<std::mutex> lock(mtx);
    temperature = temp;
}

void Engine::startUpdating() {
    running = true;
    updateThread = std::thread(&Engine::updateLoop, this);
}

void Engine::stopUpdating() {
    running = false;
    if(updateThread.joinable())
        updateThread.join();
}

void Engine::updateLoop() {
    std::srand((unsigned)std::time(nullptr));
    while (running) {
        int delta = (std::rand() % 2 == 0) ? 1 : -1;
        temperature += delta;
        if (temperature < 10) temperature = 10;
        if (temperature > 95) temperature = 95;
        std::this_thread::sleep_for(std::chrono::seconds(4));
    }
}
