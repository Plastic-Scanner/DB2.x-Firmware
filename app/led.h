#ifndef LED_H
#define LED_H

class Led {
public:
    Led(int pin): _pin(pin) {};
    void begin();
    void on();
    void off();
    void toggle();

private:
    const int _pin; 
};


#endif // LED_H