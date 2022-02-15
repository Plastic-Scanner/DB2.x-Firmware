#ifndef TLC59208_H
#define TLC59208_H

class TLC59208 {
public:
    void begin();
    void ledOn(int output);
    void ledOff(int output);
};


#endif  // TLC59208_H
