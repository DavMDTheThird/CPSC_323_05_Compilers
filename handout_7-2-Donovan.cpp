#include <iostream>
#include <algorithm>
#include <string>
#include <stack>
#include <map>


const std::string null = "NULL";
// Maps non-terminals to rows of the parsing table
const std::map<char, int> row = {
    {'S', 0},
    {'W', 1},
    {'E', 2},
    {'Q', 3},
    {'T', 4},
    {'R', 5},
    {'F', 6},
};
// Maps terminals to columns of the parsing table
const std::map<char, int> col = {
    {'a', 0},
    {'b', 1},
    {'=', 2},
    {'+', 3},
    {'-', 4},
    {'*', 5},
    {'/', 6},
    {'(', 7},
    {')', 8},
    {'$', 9},
};
const std::string parse_table[7][10] = {
    {"aW", null, null, null,  null,  null,  null,  null,  null, null},
    {null, null, "=E", null,  null,  null,  null,  null,  null, null},
    {"TQ", "TQ", null, null,  null,  null,  null,  "TQ",  null, null},
    {null, null, null, "+TQ", "-TQ", null,  null,  null,  "λ",  "λ"},
    {"FR", "FR", null, null,  null,  null,  null,  "FR",  null, null},
    {null, null, null, "λ",   "λ",   "*FR", "/FR", null,  "λ",  "λ"},
    {"a",  "b",  null, null,  null,  null,  null,  "(E)", null, null},
};


// Print current contents of stack
void print_stack(std::stack<char> stack) {
    std::cout << "Stack: ";
    // Reverse the stack to print symbols in correct order
    std::stack<char> r_stack;
    while (!stack.empty()) {
        r_stack.push(stack.top());
        stack.pop();
    }
    while (!r_stack.empty()) {
        char c = r_stack.top();
        r_stack.pop();
        std::cout << c;
    }
    std::cout << std::endl;
}

bool trace(std::string input) {
    std::stack<char> trace_stack;
    
    // Push '$' and starting state 'E'
    trace_stack.push('$');
    trace_stack.push('S');

    int string_index = 0;
    char read = '~'; // '~' is a placeholder value
    bool get_next = true;
    
    while(!trace_stack.empty()) {
        print_stack(trace_stack);
        
        // Pop the top element
        char state = trace_stack.top();
        trace_stack.pop();
        std::cout << "Pop " << state << std::endl;
        
        // If match found, move to next character of input string
        if (state == read) {
            std::cout << "Match found\n";
            string_index++;
            get_next = true;
            continue;
        }
        if (get_next) {
            read = input[string_index];
            get_next = false;
        }
        // Check if character is in the language
        if (col.find(read) != col.end()) {
            // Get the new symbols at the specified cell of the parsing table
            std::string new_states = parse_table[row.at(state)][col.at(read)];
            std::cout << "[" << state << ", " << read << "] = " << new_states << std::endl;
            
            // If reached an "empty cell", reject string
            if (new_states == null) {
                return false;
            }
            // If cell is 'λ', skip push
            if (new_states == "λ") {
                continue;
            }
            // Push new symbols in reverse order
            std::reverse(new_states.begin(), new_states.end());
            for (char c : new_states) {
                trace_stack.push(c);
            }
        } else {
            // Character was not in language, reject string
            return false;
        }
    }
    // Stack emptied, accept string
    return true;
}


int main(int argc, char* argv[]){
    std::string input = "";
    std::cout << "Enter an expression followed by '$': ";
    std::cin >> input;
    bool result = trace(input);
    std::cout << "===============\n";
    if (result) {
        std::cout << "String accepted\n";
    } else {
        std::cout << "String rejected\n";
    }
    return 0;
}