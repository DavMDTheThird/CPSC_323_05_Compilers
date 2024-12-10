#include <iostream>
#include <string>
#include <functional>

// #define Cols {"i", "+", "-", "*", "/", "(", ")", "$", "E", "T", "F", "N", "G", "D", "L"}
#define Cols {"i"}

std::vector<std::string> CFG = {
    "P>program I ; var J begin H end", // program
    "I>L", // identifier "I>L{L|D}"
    "J>V : Y ;", // dec-list
    "V>I , V ", //dec
    "V>I", 
    "Y>integer", // type
    "H>Q", // stat-list
    "H>QH", // 
    "Q>W", // stat
    "Q>A", 
    "W>print ( S , I ) ;", // Write 
    "S>\" value = \"", // string 
    "S>λ",
    "A>I=E", // Assign 
    "E>E + T", // Expresison 
    "E>E - T", 
    "E>T", 
    "T>T * F", // Term
    "T>T / F", 
    "T>F",
    "F>( E )", // Factor
    "F>N",
    "F>I", 
    "N>G D", // Number, could also be "N>GD{D}"
    "G>+", // Sign
    "G>-", 
    "G>λ", 
    "D>0", "D>1", "D>2", "D>3", "D>4", // Digits 
    "D>5", "D>6", "D>7", "D>8", "D>9", 
    "L>a","L>b",  // Letters
    "L>c","L>d",
    "L>l","L>f",
};

// Left Recursive Parsing table
std::vector<std::vector<std::string>> LR_parsingTable = {
        {"S5", "", "", "", "", "S4", "", "", "1", "2", "3"},
        {"", "S6", "S7", "", "", "", "", "ACC", "", "", ""},
        {"", "R3", "R3", "S8", "S9", "", "R3", "R3", "", "", ""},
        {"", "R6", "R6", "R6", "R6", "", "R6", "R6", "", "", ""},
        {"S5", "", "", "", "", "S4", "", "", "10", "2", "3"},
        {"", "R8", "R8", "R8", "R8", "", "R8", "R8", "", "", ""},
        {"S5", "", "", "", "", "S4", "", "", "", "11", "3"},
        {"S5", "", "", "", "", "S4", "", "", "", "12", "3"},
        {"S5", "", "", "", "", "S4", "", "", "", "", "13"},
        {"S5", "", "", "", "", "S4", "", "", "", "", "14"},
        {"", "S6", "S7", "", "", "", "S15", "", "", "", ""},
        {"", "R1", "R1", "S8", "S9", "", "R1", "R1", "", "", ""},
        {"", "R2", "R2", "S8", "S9", "", "R2", "R2", "", "", ""},
        {"", "R4", "R4", "R4", "R4", "", "R4", "R4", "", "", ""},
        {"", "R5", "R5", "R5", "R5", "", "R5", "R5", "", "", ""},
        {"", "R7", "R7", "R7", "R7", "", "R7", "R7", "", "", ""}
};