#include <iostream>
#include <stdio.h>
#include <sstream>
#include <filesystem>
#include <windows.h>

#include "commands.h"
#include "cmdline.h"

string get_current_date_time() {
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);

    char buffer[100];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);

    return string(buffer);
}

void cmd_loop() {
    vector<string> args;
    int status = 0;
    DWORD bytes;

    HANDLE history_file = CreateFile(
        (LPCSTR) "C:\\Users\\Max\\Dropbox\\OperationSystems\\lab1\\history.txt",
        GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    string data = "\nStarting programm in " + get_current_date_time() + "\n";

    SetFilePointer(history_file, 0, NULL, FILE_END);

    if (!WriteFile(history_file, data.c_str(), data.size(), &bytes, NULL)) {
        cerr << "Error: WriteFile!\n";
        return;
    }

    while (!status) {
        auto path = filesystem::current_path();
        cout << path.string() << ">";
        args = cmd_read();
        status = cmd_execute(args);
        if (cmd_history(args, history_file)) {
            cerr << "Error: can't write commands too history.txt\n";
            return;
        }
    }
    CloseHandle(history_file);
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
    } else {
        return (commands[EXE].exec)(args);
    }
    return 0;
}

int cmd_history(vector<string> args, HANDLE const file) {
    DWORD bytes;

    if (file == INVALID_HANDLE_VALUE) {
        cerr << "Error: file handle is invalid!\n";
        return 1;
    }

    SetFilePointer(file, 0, NULL, FILE_END);

    string buffer_to_write = "";
    for (size_t i = 0; i < args.size(); i++) {
        buffer_to_write += args[i];
        buffer_to_write += " ";
    }
    buffer_to_write += "\n";
    if (!WriteFile(file, buffer_to_write.c_str(), buffer_to_write.size(), &bytes, NULL)) {
        cerr << "Error: WriteFile!\n";
        return 1;
    }
    return 0;
}