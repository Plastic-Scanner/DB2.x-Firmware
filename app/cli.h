#ifndef CLI_H
#define CLI_H

class Cli {
public:
    struct Command {
        const char *name;
        void (*func)(int argc, char *argv[]);
        const char *descr;
    };

    void begin(Command command_arr[], int arr_size);
    void handle();

/* Temp dev/debug functions */
    static void list_commands();        // hacky, since that's not really a static function
};


#endif // CLI_H