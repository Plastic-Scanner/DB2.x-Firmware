#ifndef ADS1256_H
#define ADS1256_H

class ADS1256 {
public:
    ADS1256() {}
    void init();
    int read_id();
};

#endif // ADS1256_H