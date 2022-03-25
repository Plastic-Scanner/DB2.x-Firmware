#ifndef CLI_H
#define CLI_H

class Cli {
public:
    struct Command {
        const char *name;
        void (*func)(int argc, char *argv[]);
        const char *descr;
    };

    void begin(Command cmd_list[]);
    void handle();
    // void add_command(const char *name, void (*func)(int argc, char *argv[]), const char *descr);

/* Temp dev/debug functions */
    static void list_commands();        // hacky, since that's not really a static function
};


#endif // CLI_H