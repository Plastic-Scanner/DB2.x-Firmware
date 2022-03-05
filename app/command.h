#ifndef COMMAND_H
#define COMMAND_H

class Command {
public:
    void begin(
        void (*scan)(), 
        void (*adc)(),
        void (*led)(int, bool),
        void (*unknown)() );
    void handle();

private:
    void parse_command();
    
    // User-provided functions for each command
    void (*scan)();
    void (*adc)();
    void (*led)(int, bool);
    void (*unknown)();

};
#endif // COMMAND_H