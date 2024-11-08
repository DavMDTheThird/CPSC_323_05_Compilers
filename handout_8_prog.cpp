//------------------------------------------------------------------------------------------------------------- 
//          Names: David Medina Dominguez 
//          Assignment     : No.8
//          Due date       : 11/13/2024. 
// Purpose: Given the following CFG and the LR Parsing table. Write a program to trace the input strings 
//          1. (i+i)*i$,  2. (i*)$.  To determine whether they satisfy the given CFG or not.
//-------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <functional>

// Some definitions to test the program
#define Cols {"i", "+", "-", "*", "/", "(", ")", "$", "E", "T", "F"}
#define test1 "(i+i)*i$"
#define test2 "(i*)$"


std::vector<std::string> CFGtest = {
    "E>E+T", "E>E-T", "E>T", "T>T*F", "T>T/F", "T>F","F>(E)", "F>i" 
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

// Node Object Class for the stack
struct Node{
    std::string element;
    Node* previous;
};

// Stack Object Class
// Pointer to the top of the Stack, last element denoted by pointing to a nullpointer
// The Stack asks for the rows and columns of the parsing table, so each state and terminal characters
// a thing to note is that the first element of the rows MUST be the inicial/starting state.
// Finally, it also requires the parsing table for which it will process the input.
class Stack{
private:
    Node* top;
    std::string input;
    std::vector<std::string> LRtableCols;
    std::vector<std::string> CFG;
    std::vector<std::vector<std::string>> LRparsingTable;

public:
    // Constructor, which will also do the trace of the input.
    Stack(std::vector<std::string> cols, std::vector<std::string> CFG_, std::vector<std::vector<std::string>> LRtable, std::string input) 
        : top(nullptr), LRtableCols(cols), CFG(CFG_), LRparsingTable(LRtable), input(input){
        this->trace();
    }

    // Push a new node to the Stack
    void push(std::string c){
        Node* newNode = new Node();
        newNode->element = c; 
        newNode->previous = top;
        top = newNode;
    }

    // Pops the top node of the stack, returns its value
    // Error handling should be introduced if return "!"
    std::string pop(int num = 1){
        std::string element_;
        for(int i = 0; i < num; ++i){
            if(this->top == nullptr){
                std::cout<<"ERROR! Stack si Empty"<<std::endl;
                return "!"; 
            }
            element_ = this->top->element;
            Node* top_ = this->top;
            this->top = top->previous;
            delete top_;
        }
        return element_; // Return the popped data
    }

    // Given a string s, find it in the given column
    // Error handling should be added if return -1 
    int getCol(std::string s){
        int i = 0;
        for(std::string col : this->LRtableCols){
            if(s == col){
                return i;
            }
            ++i;
        }
        return -1;
    }

    // Returns a Vector of strings containing the left hand-side of the rule, 
    // and the total elements of the right hand-side.
    std::vector<std::string> getRule_Pop(int num){
        std::string ruleLHS = "";
        int i = 0;
        bool right = false;
        for(char e : CFG[num-1]){
            if(right)
                ++i;
            else if(e == '>')
                right = true;
            else
                ruleLHS += e;
        }
        return {ruleLHS, std::to_string(i)};
    }

    // A function that prints the current Stack
    void printStack(){
        // Definition of a recursive function to print the elements in correct order 
        //      (left to right) -> (bottom of Stack to top of the Stack)
        std::function<void(Node*)> print_element = [&print_element](Node* element){
            if(element->previous == nullptr)
                std::cout<<element->element;
            else{
                print_element(element->previous);
                std::cout<<element->element;
            }
        };
        std::cout<<"Stack: ";
        print_element(this->top);
        std::cout<<std::endl;
    }

    // This function returns the given element into its two diferent parts from the Parsing table,
    // either it's a Rule or State, and the value, or just the terminal value.  
    std::vector<std::string> getRule_Elem(std::string element){
        std::string state = "";
        std::string element_ = "";
        for(char e : element){
            if(e == 'S' || e == 'R'){
                state += e;
            }
            else{
                element_ += e;
            }
        }
        return {state, element_};
    }

    // Main function to trace an input through the given rules and states (LR parsing table)
    int trace(){
        std::string read;
        std::string tableElement;
        int i = 0;
        bool read_ = true; // true = S, false = N or number

        this->push("0");
        while(true){
            printStack();
            std::string pop = this->pop();
            if(read_){
                if(this->input[i] == '\n'){
                    std::cout<<this->input<<" is NOT ACCEPTED"<<std::endl;
                    return 0;
                }
                read = this->input[i];
                ++i;
                read_ = false;
                std::cout<<"Read: "<<read<<std::endl;
            }
            tableElement = this->LRparsingTable[std::stoi(pop)][this->getCol(read)];
            std::cout<<"tableElement: "<<tableElement<<std::endl;
            if(tableElement == "ACC"){
                std::cout<<this->input<<" is ACCEPTED"<<std::endl;
                return 1;
            }
            else if(tableElement == ""){
                std::cout<<this->input<<" is NOT ACCEPTED"<<std::endl;
                return 0;
            }
            std::vector<std::string> TableElements = getRule_Elem(tableElement);
            if (TableElements[0] == "S"){
                this->push((pop)); this->push(read); this->push(TableElements[1]);
                read_ = true;
            }
            else if (TableElements[0] == "R"){
                this->push((pop));
                std::vector<std::string> rule_pop = getRule_Pop(std::stoi(TableElements[1]));
                for(int i = 0; i < std::stoi(rule_pop[1]) * 2; ++i)
                    this->pop();
                pop = this->pop();
                tableElement = this->LRparsingTable[std::stoi(pop)][this->getCol(rule_pop[0])];
                if(tableElement == ""){
                    std::cout<<this->input<<" is NOT ACCEPTED"<<std::endl;
                    return 0;
                }
                std::cout<<"tableElement: "<<tableElement<<std::endl;
                this->push(pop); this->push(rule_pop[0]); this->push(tableElement);
            }
        }
        return 1;
    }
};

int main(int argc, char* argv[]){
    Stack myStack1(Cols, CFGtest, LR_parsingTable, test1);
    Stack myStack2(Cols, CFGtest, LR_parsingTable, test2);

    return 0; 
}