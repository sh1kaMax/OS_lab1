#ifndef CMDLINE_H
#define CMDLINE_H

#include <string>
#include <vector>

using namespace std;

void cmd_loop();
vector<string> cmd_read();
int cmd_execute(vector<string>);


#endif