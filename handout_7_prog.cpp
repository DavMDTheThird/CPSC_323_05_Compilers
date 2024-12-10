//------------------------------------------------------------------------------------------------------------- 
//          Names: David Medina Dominguez 
//          Assignment     : No.7
//          Due date       : 10/30/2024. 
// Purpose: Given the following CFG and the Predictive Parsing table. Write a program to determine which of the
//     following are accepted/rejected by the given grammar (1) (i+i)*i$, (2) i*(i-i)$, (3) i(i+i)$. Show the 
//     content of the stack after each match. 2. Include the  S->aW , W->=E  rules to the beginning of the 
//     grammar, replace F->i  with F->a and F->b. Trace input (i) a=(a+b)*a$, (ii) a=a*(b-a)$, (iii) a=(a+a)b$
//-------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <functional>

// Some definitions to test the program
#define ex1Rows {"E", "Q", "T", "R", "F"}
#define ex1Cols {"i", "+", "-", "*", "/", "(", ")", "$"}
#define ex1_test1 "(i+i)*i$"
#define ex1_test2 "i*(i-i)$"
#define ex1_test3 "i(i+i)$"

#define ex2Rows {"S", "W", "E", "E'", "T", "T'", "F"}
#define ex2Cols {"a", "b", "+", "-", "*", "/", "(", ")", "=", "$"}
#define ex2_test1 "a=(a+b)*a$"
#define ex2_test2 "a=a*(b-a)$"
#define ex2_test3 "a=(a+a)b$"


// Parsing tables for exercises 2 & 3
std::vector<std::vector<std::string>> tableEx2 = {
        {"TQ", "", "", "", "", "TQ", "", ""},
        {"", "+TQ", "-TQ", "", "", "", "λ", "λ"},
        {"FR", "", "", "", "", "FR", "", ""},
        {"", "λ", "λ", "*FR", "/FR", "", "λ", "λ"},
        {"i", "", "", "", "", "(E)", "", ""}
};
std::vector<std::vector<std::string>> tableEx3 = {
    {"aW", "", "", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", "", "=E", ""},
    {"TE'", "TE'", "", "", "", "", "TE'", "", "", ""},
    {"", "", "+TE'", "-TE'", "", "", "", "λ", "", "λ"},
    {"FT'", "FT'", "", "", "", "", "FT'", "", "", ""},
    {"", "", "λ", "λ", "*FT'", "/FT'", "", "λ", "", "λ"},
    {"a", "b", "", "", "", "", "(E)", "", "", ""}
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
    std::vector<std::string> tableRows;
    std::vector<std::string> tableCols;
    std::vector<std::vector<std::string>> parsingTable;

public:
    // Constructor, which will also do the trace of the input.
    Stack(std::vector<std::string> rows, std::vector<std::string> cols, 
            std::vector<std::vector<std::string>> table, std::string input) 
        : top(nullptr), tableRows(rows), tableCols(cols), parsingTable(table), input(input){
        this->trace();
    }

    // Just returns the initial/starting state for the trace to work
    std::string getStartState(){
        return this->tableRows[0];
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
    std::string pop(){
        if(top == nullptr)
            return "!"; 
        std::string element_ = top->element;
        Node* top_ = top;
        top = top->previous;
        delete top_;
        return element_; // Return the popped data
    }

    // Given a string s, find it in the given column
    // Error handling should be added if return -1 
    int getCol(std::string s){
        int i = 0;
        for(std::string col : this->tableCols){
            if(s == col){
                return i;
            }
            ++i;
        }
        return -1;
    }

    // Given a string s, find it in the given column
    // Error handling should be added if return -1 
    int getRow(std::string s){
        int i = 0;
        for(std::string row : this->tableRows){
            if(s == row){
                return i;
            }
            ++i;
        }
        return -1;
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

    // Main function to trace an input through the given rules and states (parsing table)
    int trace(){
        this->push("$");
        this->push(getStartState());
        for(int i = 0; input[i] != '\0'; ++i){
            printStack();
            std::string pop = this->pop();
            std::string read; read += this->input[i];
            // std::cout<<"  Read: "<<read<<std::endl;
            // This line could break if a given character is not on the list, further error handling could be added
            std::string tableElement = this->parsingTable[this->getRow(pop)][this->getCol(read)];
            while(pop != read){
                // std::cout<<"table["<<pop<<"]"<<"["<<read<<"]: "<<tableElement<<std::endl;

                // If the parsing tree points to a empty state, input is rejected
                if(tableElement == ""){
                    std::cout<<"The input: "<<this->input<<" is rejected"<<std::endl;
                    return -1;
                }
                // If lambda ("λ"), skip to the next state
                if(tableElement != "λ"){
                    // Pushes the states (backwards) to the Stack
                    for(int i = tableElement.length() - 1; i >= 0; --i){
                        std::string temp;
                        // If the given state is in E' form (two characters, instead of one)
                        // This only work with one ', further increase could be implemented 
                        if('\'' == tableElement[i]){
                            temp += tableElement[i-1];
                            temp += tableElement[i];
                            --i;
                        }
                        else{
                            temp += tableElement[i];
                        }
                        this->push(temp);
                    }
                }
                // Advance to the next state until a match is found or input is rejected
                // printStack();
                tableElement = this->parsingTable[this->getRow(pop)][this->getCol(read)];
                pop = this->pop();
            }
            std::cout<<"--Match with input "<<read<<std::endl;
        }
        std::cout<<"The input: "<<this->input<<" is accepted"<<std::endl;
        return 1;
    }
};

int main(int argc, char* argv[]){
    Stack myStack1(ex1Rows, ex1Cols, tableEx2, ex1_test1);
    Stack myStack2(ex1Rows, ex1Cols, tableEx2, ex1_test2);
    Stack myStack3(ex1Rows, ex1Cols, tableEx2, ex1_test3);

    Stack myStack4(ex2Rows, ex2Cols, tableEx3, ex2_test1);
    Stack myStack5(ex2Rows, ex2Cols, tableEx3, ex2_test2);
    Stack myStack6(ex2Rows, ex2Cols, tableEx3, ex2_test3);

    return 0; 
}