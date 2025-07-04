#ifndef ENGINE_H
#define ENGINE_H

#include <thread>
#include <atomic>

// Class representing a simple engine that updates its temperature periodically
class Engine {
private:
    std::atomic<int> temperature;   // Current temperature, thread-safe
    std::thread worker;             // Background thread that updates temperature
    std::atomic<bool> running;      // Flag to control the running state of the thread

    // Internal loop function run by the worker thread
    void updateLoop();

public:
    Engine();   // Constructor starts the update thread
    ~Engine();  // Destructor stops the thread and cleans up

    // Returns the current temperature value
    int getTemperature() const;
};

#endif // ENGINE_H
