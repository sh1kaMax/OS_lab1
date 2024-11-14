#include <iostream>
#include <windows.h>
#include <time.h>

#include "commands.h"

command_names string_to_enum(string const c) {
    if (c == "help") {
        return HELP;
    } else if (c == "exit") {
        return EXIT;
    } else if (c == "exe") {
        return EXE;
    }else {
        return UNKNOWN;
    }
}

int help(vector<string> const args) {
    for (auto c : commands) {
        cout << c.second.name << ": " << c.second.description << endl;
    }
    return 0;
}

int exit(vector<string> const args) {
    return 1;
}

int exe(vector<string> args) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    string commandLine = "";
    for (size_t i = 1; i < args.size(); i++) {
        commandLine += args[i] + " ";
    }
    clock_t start = clock();

    if (!CreateProcess(NULL, 
        &commandLine[0],
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi
        )
    ) {
        cerr << "Error: CreateProcess failed\n";
        return 1;
    } else {
        WaitForSingleObject(pi.hProcess, INFINITE);

        clock_t end = clock();
        double seconds = (double) (end - start) / CLOCKS_PER_SEC;
        cout << "Time of execution: " << seconds << "\n";

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    return 0;
}

unordered_map<command_names, command> commands = {
    { HELP, {"help", "Displays a list of commands", help}},
    { EXIT, {"exit", "Ends the program", exit}},
    { EXE, {"exe", "Create new process with your program and consult the time of execution", exe}}
};