#include "cli.h"
#include <Arduino.h>

static const int MAX_COMMANDS = 20;
static const int RX_BUF_SIZE = 20;
static const int MAX_ARGS = 3;

static int command_cnt;
static char rx_buf[RX_BUF_SIZE];
static int rx_cnt;

static void parse_command()
{
    int argc = 0;
    char *argv[MAX_ARGS] = {0};
    bool args_ok = true;

    const char* delimiters = " ";
    char *token = strtok(rx_buf, delimiters);
    while (token != NULL) {
        argv[argc++] = token;
        token = strtok(NULL, delimiters);
    }

    // Compare first token (command) with all command names
    for (int i=0; i < command_cnt; i++) {
        Command cmd = command_list[i];
        if (strcmp(cmd.name, argv[0]) == 0) {
            if (cmd.func != nullptr) cmd.func(argc, argv);
            else Serial.println("Command function not provided");
            return;
        }
    }
}

static void reset()
{
    rx_cnt = 0;
    memset(rx_buf, 0, RX_BUF_SIZE);
}

void Cli::begin()
{
    reset();
    command_cnt = 0;
}

void Cli::handle()
{
    int n = Serial.available();
    while (n > 0) {
        char c = Serial.read();
        if (c == '\b') {                    // backspace
            rx_buf[--rx_cnt] = '\0';

        } else if (rx_cnt == RX_BUF_SIZE) { // buffer overflow
            reset();

        } else if (c == '\n' || c == '\r') { // line ending (LF or CR)
            parse_command();
            reset();
            if (Serial.peek() == '\n') Serial.read();  // handle CRLF line ending

        } else {
            rx_buf[rx_cnt++] = c;           // add to buffer
        }
        n--;
    }
}

void Cli::add_command(const char *name, void (*func)(int argc, char *argv[]), const char *descr)
{
    command_list[command_cnt++] = Command{name, func, descr};
}

void Cli::list_commands()
{
    for (int i=0; i<command_cnt; i++) {
        Serial.print("Command ");
        Serial.print(i);
        Serial.print(": ");
        Serial.print(command_list[i].name);
        Serial.print("\t");
        Serial.print(command_list[i].descr);
        Serial.println();
    }
}