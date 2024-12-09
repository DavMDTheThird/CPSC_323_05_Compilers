#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <bits/stdc++.h>


const std::string FILENAME = "finalf24.txt";

const std::string null = "NULL";
const std::string RESERVED[] = {"print", "integer", "program", "var", "begin", "end", "\"value=\","};
// Maps non-terminals to rows of the parsing table
const std::map<std::string, int> ROW = {
    {"P", 0},
    {"I", 1},
    {"I'", 2},
    {"J", 3},
    {"V", 4},
    {"V'", 5},
    {"Y", 6},
    {"H", 7},
    {"H'", 8},
    {"Q", 9},
    {"W", 10},
    {"S", 11},
    {"A", 12},
    {"E", 13},
    {"E'", 14},
    {"T", 15},
    {"T'", 16},
    {"F", 17},
    {"N", 18},
    {"N'", 19},
    {"G", 20},
    {"D", 21},
    {"L", 22},
};
// Maps terminals to columns of the parsing table
const std::map<std::string, int> COL = {
    {"a", 0},
    {"b", 1},
    {"c", 2},
    {"d", 3},
    {"l", 4},
    {"f", 5},
    {"0", 6},
    {"1", 7},
    {"2", 8},
    {"3", 9},
    {"4", 10},
    {"5", 11},
    {"6", 12},
    {"7", 13},
    {"8", 14},
    {"9", 15},
    {"+", 16},
    {"-", 17},
    {"*", 18},
    {"/", 19},
    {"=", 20},
    {"\"value=\",", 21},
    {",", 22},
    {"(", 23},
    {")", 24},
    {":", 25},
    {";", 26},
    {"$", 27},
    {"print", 28},
    {"integer", 29},
    {"program", 30},
    {"var", 31},
    {"begin", 32},
    {"end", 33},
};
const std::string parse_table[23][34] = {
    {null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "program I ; var J begin H end", null, null},
    {"L I'", "L I'", "L I'", "L I'", "L I'", "L I'", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null},
    {"L I'", "L I'", "L I'", "L I'", "L I'", "L I'", "D I'", "D I'", "D I'", "D I'", "D I'", "D I'", "D I'", "D I'", "D I'", "D I'", "λ", "λ", "λ", "λ", "λ", null, "λ", null, "λ", "λ", "λ", null, null, null, null, null, null},
    {"V : Y ;", "V : Y ;", "V : Y ;", "V : Y ;", "V : Y ;", "V : Y ;", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null},
    {"I V'", "I V'", "I V'", "I V'", "I V'", "I V'", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null},
    {null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, ", V", null, null, "λ", null, null, null, null, null, null, null},
    {null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "integer", null, null, null},
    {"Q H'", "Q H'", "Q H'", "Q H'", "Q H'", "Q H'", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "Q H'", null, null, null, null},
    {"H", "H", "H", "H", "H", "H", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "H", null, null, null, null, "λ"},
    {"A", "A", "A", "A", "A", "A", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "W", null, null, null, null},
    {null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "print ( S I ) ;", null, null, null, null},
    {"λ", "λ", "λ", "λ", "λ", "λ", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "\"value=\",", null, null, null, null, null, null, null, null, null, null, null, null},
    {"I = E ;", "I = E ;", "I = E ;", "I = E ;", "I = E ;", "I = E ;", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null},
    {"T E'", "T E'", "T E'", "T E'", "T E'", "T E'", "T E'", "T E'", "T E'", "T E'", "T E'", "T E'", "T E'", "T E'", "T E'", "T E'", "T E'", "T E'", null, null, null, null, null, "T E'", null, null, null, null, null, null, null, null, null},
    {null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "+ T E'", "- T E'", null, null, null, null, null, null, "λ", null, "λ", null, null, null, null, null, null},
    {"F T'", "F T'", "F T'", "F T'", "F T'", "F T'", "F T'", "F T'", "F T'", "F T'", "F T'", "F T'", "F T'", "F T'", "F T'", "F T'", "F T'", "F T'", null, null, null, null, null, "F T'", null, null, null, null, null, null, null, null, null},
    {null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "λ", "λ", "* F T'", "/ F T'", null, null, null, null, "λ", null, "λ", null, null, null, null, null, null},
    {"I", "I", "I", "I", "I", "I", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", null, null, null, null, null, "( E )", null, null, null, null, null, null, null, null, null},
    {null, null, null, null, null, null, "G D N'", "G D N'", "G D N'", "G D N'", "G D N'", "G D N'", "G D N'", "G D N'", "G D N'", "G D N'", "G D N'", "G D N'", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null},
    {null, null, null, null, null, null, "D N'", "D N'", "D N'", "D N'", "D N'", "D N'", "D N'", "D N'", "D N'", "D N'", "λ", "λ", "λ", "λ", null, null, null, null, "λ", null, "λ", null, null, null, null, null, null},
    {null, null, null, null, null, null, "λ", "λ", "λ", "λ", "λ", "λ", "λ", "λ", "λ", "λ", "+", "-", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null},
    {null, null, null, null, null, null, "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null},
    {"a", "b", "c", "d", "l", "f", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null}
};


// Split string by spaces into vector of smaller strings
std::vector<std::string> split(std::string str, bool reversed = false) {
    std::stringstream stream(str);
    std::vector<std::string> v;
    std::string s;
    while (std::getline(stream, s, ' ')) {
        v.push_back(s);
    }
    // Reverse the string vector
    if (reversed) {
        std::reverse(v.begin(), v.end());
    }
    return v;
}

// Print current contents of stack
void print_stack(std::stack<std::string> stack) {
    std::cout << "Stack: ";
    // Reverse the stack to print symbols in correct order
    std::stack<std::string> r_stack;
    while (!stack.empty()) {
        r_stack.push(stack.top());
        stack.pop();
    }
    while (!r_stack.empty()) {
        std::string s = r_stack.top();
        r_stack.pop();
        std::cout << s;
    }
    std::cout << std::endl;
}

bool trace(std::string input) {
    std::stack<std::string> input_tokens;
    for (std::string s : split(input, true)) {
        input_tokens.push(s);
    }
    std::stack<std::string> trace_stack;
    
    // Push '$' and starting state 'P'
    trace_stack.push("$");
    trace_stack.push("P");

    std::string read = "";
    bool get_next = true;
    
    while(!trace_stack.empty() and !input_tokens.empty()) {
        print_stack(trace_stack);
        
        // Pop the top element
        std::string state = trace_stack.top();
        trace_stack.pop();
        std::cout << "Pop " << state << std::endl;
        
        // Get next token to read
        if (get_next) {
            // Do not split if detected a reserved word
            bool split_id = true;
            for (std::string s : RESERVED) {
                if (s == input_tokens.top()) {
                    split_id = false;
                    break;
                }
            }
            // Split strings into characters (allows tracing identifiers)
            if (split_id) {
                std::string id = input_tokens.top();
                input_tokens.pop();
                if (id.length() > 1) {
                    std::cout << "Splitting " << id << " into chars\n";
                }
                for (auto i = id.rbegin(); i != id.rend(); i++) {
                    input_tokens.push({*i});
                }
            }
            read = input_tokens.top();
            get_next = false;
            std::cout << "Read: " << read << '\n';
        }

        // If match found, move to next token of input string
        if (state == read) {
            std::cout << "Match found\n";
            input_tokens.pop();
            read = "";
            get_next = true;
            continue;
        }

        // Check if token is in the language
        if (COL.find(read) != COL.end()) {
            // Get the new tokens at the specified cell of the parsing table
            std::string new_states = parse_table[ROW.at(state)][COL.at(read)];
            std::cout << "[" << state << ", " << read << "] = " << new_states << std::endl;
            
            // If reached an "empty cell", reject input
            if (new_states == null) {
                return false;
            }
            // If cell is 'λ', skip push
            if (new_states == "λ") {
                continue;
            }
            // Push new symbols in reverse order
            for (std::string token : split(new_states, true)) {
                trace_stack.push(token);
            }
        } else {
            // Token was not in language, reject input
            return false;
        }
    }
    // Stack emptied, accept input
    return true;
}


int main(int argc, char* argv[]){
    std::ifstream input_file(FILENAME);
    if (!input_file.is_open()) {
        std::cerr << "Error opening " << FILENAME << '\n';
        return 1;
    }
    std::string tokens;
    std::string line;
    while (std::getline(input_file, line)) {
        // std::cout << line << '\n';
        tokens.append(line);
    }
    input_file.close();

    bool result = trace(tokens);
    std::cout << "===============\n";
    if (result) {
        std::cout << "String accepted\n";
    } else {
        std::cout << "String rejected\n";
    }
    return 0;
}