#ifndef ADS1256_H
#define ADS1256_H

#include <stdint.h>

class ADS1256 {
public:
    void begin();
    int read_id();
    long read_channel();
};

#endif // ADS1256_H