#ifndef ENGINE_H
#define ENGINE_H

#include <random>

class Engine {
public:
    Engine();

    int getTemperature();
    void setTemperature(int temp);
    int getHumidity() const;
    int getPressure() const;

    void updateSensors();

private:
    int temperature;
    int humidity;
    int pressure;

    mutable std::mt19937 gen;
    mutable std::uniform_int_distribution<> distTemp;
    mutable std::uniform_int_distribution<> distHum;
    mutable std::uniform_int_distribution<> distPres;
};

#endif // ENGINE_H

