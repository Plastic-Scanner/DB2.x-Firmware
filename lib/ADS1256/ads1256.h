#ifndef ADS1256_H
#define ADS1256_H

class ADS1256 {
public:
    ADS1256();
    int read_id();
    long read_channel();
};

#endif // ADS1256_H