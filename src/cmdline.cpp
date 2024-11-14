#include <iostream>
#include <stdio.h>
#include <sstream>

#include "commands.h"
#include "cmdline.h"


void cmd_loop() {
    vector<string> args;
    int status = 0;

    while (!status) {
        args = cmd_read();
        status = cmd_execute(args);
    }
}


vector<string> cmd_read() {
    string line;
    getline(cin, line);
    istringstream iss(line);
    vector<string> args;
    string word;

    while (iss >> word) {
        args.push_back(word);
    }
    
    return args;
}


int cmd_execute(vector<string> args) {
    command_names maybe_command_name = string_to_enum(args[0]);
    if (maybe_command_name != UNKNOWN) {
        return (commands[maybe_command_name].exec)(args);
    }
    cerr << "Error: not valid command\nType help\n";
    return 0;
}