#include <iostream>
#include <vector>
#include <cmath>
#include <windows.h>

#define BLOCK_SIZE 1024


using namespace std;

int main(int argc,char* argv[]) {
    if (argc != 2) {
        cerr << "Error: not valid usage of prog (./prog.exe count)";
        return 1;
    }

    size_t size_to_write = 100 * pow(2, 20);
    size_t written_size;
    DWORD bytes;

    vector<char> buffer(BLOCK_SIZE, 'F');

    HANDLE file = CreateFile(
        (LPCSTR) "output.bin",
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (file == INVALID_HANDLE_VALUE) {
        cerr << "Error: CreateFile!\n";
        return 1;
    }

    for (int i = 0; i < atoi(argv[1]); i++) {
        written_size = 0;
        while (written_size < size_to_write) {
            if (!WriteFile(file, buffer.data(), BLOCK_SIZE, &bytes, NULL)) {
                cerr << "Error: WriteFile!\n";
                CloseHandle(file);
                return 1;
            }
            written_size += bytes;
        }
    }
    CloseHandle(file);
    return 0;
}