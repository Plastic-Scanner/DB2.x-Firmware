#ifndef ADS1256_H
#define ADS1256_H

#include <stdint.h>

class ADS1256 {
public:
    void begin();
    int read_id();
    long read_channel();

    void send_command(uint8_t cmd);
    void write_register(uint8_t reg, uint8_t data);
    uint8_t read_register(uint8_t reg);
};

#endif // ADS1256_H