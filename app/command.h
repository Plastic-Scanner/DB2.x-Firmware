#ifndef COMMAND_H
#define COMMAND_H

class Command {
public:
    void begin();
    void handle();

private:
    void parse_command();
};


#endif // COMMAND_H