#include <iostream>
#include "finalProject_readFile.h"
#include "finalProject_translation.h"
#include "finalProject_compiler.h"

int main(int argc, char* argv[]){
    ReadFile myP1_rf;
    TranslateFile myP1_t(myP1_rf.getFileName());
    cCompiler myP1_c(myP1_rf.getFileName());
    return 0;
}