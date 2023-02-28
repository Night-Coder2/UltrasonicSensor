#ifndef PICOPROJECTS_ULTRASONICSENSOR_H
#define PICOPROJECTS_ULTRASONICSENSOR_H

#include <pico/stdlib.h>

#define DEBUGCORE(...) do { } while(0)

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout);

class UltrasonicSensor {
private:
    uint32_t triggerPin;
    uint32_t echoPin;
    long duration;
    int distanceCm, distanceInch;

public:
    UltrasonicSensor(){}
    UltrasonicSensor(uint32_t triggerPin, uint32_t echoPin);

    void init();

    uint64_t getCM();
    uint64_t getINCH();
};


#endif //PICOPROJECTS_ULTRASONICSENSOR_H
