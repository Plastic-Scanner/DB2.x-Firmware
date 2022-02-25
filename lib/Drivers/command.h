#ifndef COMMAND_H
#define COMMAND_H

class Command {
public:
    void begin(
        void (*scan)(), 
        void (*adc)(),
        void (*ledon_fptr)(int), 
        void (*ledoff_fptr)(int),
        void (*unknown)()
        ); 
    void handle();

private:
    void parse_command(char *ptr);

    void (*scan_fptr)();
    void (*adc_fptr)();
    void (*ledon_fptr)(int);
    void (*ledoff_fptr)(int);
    void (*unknown_fptr)();
};


#endif // COMMAND_H