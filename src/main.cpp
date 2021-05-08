#include "Interpreter.h"

int main(int argc, char** argv, char** envp)
{
    Interpreter interp(argc, argv, envp);
    interp.start();
}

