#include "Application.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
//#undef main
using namespace std;

int main(int argc, char* args[]) {

    Application app;

    app.loop();
    app.draw();

    //system("DATE"); // command line example - looking into adding post-build event through code
    // Might need to use Windows specific API'S like ShellExecute or ShellExecuteEx for this
    // https://stackoverflow.com/questions/31201631/execute-cmd-commands-using-c

    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtDumpMemoryLeaks();

    return 0;
}