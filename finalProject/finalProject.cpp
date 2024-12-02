#include <iostream>
#include "finalProject_readFile.h"
#include "finalProject_translation.h"
#include "tokenizer.h"
#include "syntax_analyzer.h"

int main(int argc, char* argv[]){
    ReadFile myP1_rf;
    TranslateFile myP1_t(myP1_rf.getFileName());
    Tokenizer          tokenizer( myP1_rf.getFileName() );
    std::vector<Token> tokens = tokenizer.tokenize();

    // Create a SyntaxAnalyzer object and analyze the tokens
    SyntaxAnalyzer syntaxAnalyzer( tokens );
    syntaxAnalyzer.analyze();

    return 0;
}
