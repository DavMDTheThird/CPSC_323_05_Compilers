//------------------------------------------------------------------------------------------------------------- 
//          Group names: David Medina Dominguez, Donovan Jabido and Jaiveer Nayen Kapadia 
//          Assignment     : No.3 
//          Due date       : 10/25/2024. 
// Purpose: Write a program to read one token at a time from the given text file and determine whether the token 
//          is a number, an identifier or a reserved word. 
//-------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

const std::string RESERVED[] = {"while", "for", "switch", "do", "return"};

bool is_number(std::string token) {
    // if (token.empty()) {
    //     return false;
    // }
    for (int i = 0; i < token.length(); i++) {
        if (!isdigit(token[i])) {
            return false;
        }
    }
    return true;
}

bool is_identifier(std::string token) {
    if (token.empty() || !(token[0] == '_' || isalpha(token[0]))) {
        return false;
    }
    for (int i = 1; i < token.length(); i++) {
        if (!(token[i] == '_' || isalpha(token[i]) || isdigit(token[i]))) {
            return false;
        }
    }
    return true;
}

bool is_reserved(std::string token) {
    for (std::string word : RESERVED) {
        if (token == word) {
            return true;
        }
    }
    return false;
}


int main(int argc, char* argv[]){
    std::ifstream inputFile("tokens.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error opening file\n";
        return 1;
    }

    std::string token;
    std::cout << "Token            number         identifier     reserved word\n";
    while (getline(inputFile, token)) {
        std::string is_num = is_number(token) ? "yes" : "no ";
        std::string is_id = is_identifier(token) ? "yes" : "no ";
        std::string is_res = is_reserved(token) ? "yes" : "no ";
        std::cout << token << std::setw(20 - token.length()) << is_num << "            " << is_id << "            " << is_res << '\n';
    }
    
    inputFile.close();

    return 0;
}