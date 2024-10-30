//------------------------------------------------------------------------------------------------------------- 
//          Names: David Medina Dominguez 
//          Assignment     : No.7
//          Due date       : 10/30/2024. 
// Purpose: Given the following CFG and the Predictive Parsing table. Write a program to determine which of the
//     following are accepted/rejected by the given grammar (1) (i+i)*i$, (2) i*(i-i)$, (3) i(i+i)$. Show the 
//     content of the stack after each match.
//-------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <functional>

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


std::vector<std::vector<std::string>> tableEx2 = {
        {"TQ", "", "", "", "", "TQ", "", ""},
        {"", "+TQ", "-TQ", "", "", "", "_", "_"},
        {"FR", "", "", "", "", "FR", "", ""},
        {"", "_", "_", "*FR", "/FR", "", "_", "_"},
        {"i", "", "", "", "", "(E)", "", ""}
};

std::vector<std::vector<std::string>> tableEx3 = {
    {"aW", "", "", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", "", "=E", ""},
    {"TE'", "TE'", "", "", "", "", "TE'", "", "", ""},
    {"", "", "+TE'", "-TE'", "", "", "", "_", "", "_"},
    {"FT'", "FT'", "", "", "", "", "FT'", "", "", ""},
    {"", "", "_", "_", "*FT'", "/FT'", "", "_", "", "_"},
    {"a", "b", "", "", "", "", "(E)", "", "", ""}
};




struct Node{
    std::string element;
    Node* previous;
};

class Stack{
private:
    Node* top;
    std::string input;
    std::vector<std::string> tableRows;
    std::vector<std::string> tableCols;
    std::vector<std::vector<std::string>> parsingTable;

public:
    // Constructor 
    Stack(std::vector<std::string> rows, std::vector<std::string> cols, std::vector<std::vector<std::string>> table, std::string input) 
        : top(nullptr), tableRows(rows), tableCols(cols), parsingTable(table), input(input){
        this->trace();
    }

    std::string getStartState(){
        return this->tableRows[0];
    }

    void push(std::string c){
        Node* newNode = new Node();
        newNode->element = c; 
        newNode->previous = top;
        top = newNode;
    }

    std::string pop(){
        if(top == nullptr)
            return "!"; 
        std::string element_ = top->element;
        Node* top_ = top;
        top = top->previous;
        delete top_;
        return element_; // Return the popped data
    }

    int getCol(std::string c){
        int i = 0;
        for(std::string col : this->tableCols){
            if(c == col){
                return i;
            }
            ++i;
        }
        return -1;
    }

    int getRow(std::string c){
        int i = 0;
        for(std::string row : this->tableRows){
            if(c == row){
                return i;
            }
            ++i;
        }
        return -1;
    }

    void printStack(){
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

    int trace(){
        this->push("$");
        this->push(getStartState());
        for(int i = 0; input[i] != '\0'; ++i){
            printStack();
            std::string pop = this->pop();
            std::string read; read += this->input[i];
            // std::cout<<"  Read: "<<read<<std::endl;
            std::string tableElement = this->parsingTable[this->getRow(pop)][this->getCol(read)];
            while(pop != read){
                // std::cout<<"table["<<pop<<"]"<<"["<<read<<"]: "<<tableElement<<std::endl;
                if(tableElement == ""){
                    std::cout<<"The input: "<<this->input<<" is rejected"<<std::endl;
                    return -1;
                }
                if(tableElement != "_"){
                    for(int i = tableElement.length() - 1; i >= 0; --i){
                        std::string temp;
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