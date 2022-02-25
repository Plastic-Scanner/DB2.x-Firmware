#ifndef COMMAND_H
#define COMMAND_H

class Command {
public:
    void begin();
    void handle();

private:
    void parse_command(char *ptr, int nchars);
};


#endif // COMMAND_H