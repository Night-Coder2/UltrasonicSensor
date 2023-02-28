#include "include/UltrasonicSensor.h"

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout) {
    uint64_t start = time_us_64();
    uint64_t abort = start + timeout;

    if (pin > 29) {
        DEBUGCORE("ERROR: Illegal pin in pulseIn (%d)\n", pin);
        return 0;
    }

    // Wait for deassert, if needed
    while ((!!gpio_get(pin) != !state) && (time_us_64() < abort));
    if (time_us_64() >= abort) {
        return 0;
    }

    // Wait for assert
    while ((!!gpio_get(pin) != !!state) && (time_us_64() < abort));
    uint64_t begin = time_us_64();
    if (begin >= abort) {
        return 0;
    }

    // Wait for deassert
    while ((!!gpio_get(pin) != !state) && (time_us_64() < abort));
    uint64_t end = time_us_64();
    if (end >= abort) {
        return 0;
    }

    return end - begin;
}
UltrasonicSensor::UltrasonicSensor(uint32_t triggerPin, uint32_t echoPin) {
    this->triggerPin = triggerPin;
    this->echoPin = echoPin;
}
void UltrasonicSensor::init() {
    gpio_init(triggerPin);
    gpio_set_dir(triggerPin, GPIO_OUT);
    gpio_init(echoPin);
    gpio_set_dir(echoPin, GPIO_IN);
}
uint64_t UltrasonicSensor::getCM() {
    gpio_put(triggerPin, 0);
    sleep_us(2);
    gpio_put(triggerPin, 1);
    sleep_us(10);
    gpio_put(triggerPin, 0);
    duration = pulseIn(echoPin, 1, 1000000);
    return distanceCm = duration * 0.034 / 2;
}
uint64_t UltrasonicSensor::getINCH() {
    gpio_put(triggerPin, 0);
    sleep_us(2);
    gpio_put(triggerPin, 1);
    sleep_us(10);
    gpio_put(triggerPin, 0);
    duration = pulseIn(echoPin, 1, 1000000);
    return distanceInch = duration * 0.0133 / 2;
}