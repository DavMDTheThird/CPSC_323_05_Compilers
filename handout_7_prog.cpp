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

#define ex1Rows {'E', 'Q', 'T', 'R', 'F'}
#define ex1Cols {'i', '+', '-', '*', '/', '(', ')', '$'}
#define ex1_test1 "(i+i)*i$"
#define ex1_test2 "i*(i-i)$"
#define ex1_test3 "i(i+i)$"

#define ex2_test1 "a=(a+b)*a$"
#define ex2_test2 "a=a*(b-a)$"
#define ex2_test3 "a=(a+a)b$"


std::string table1[5][8] = {{"TQ","","","","","TQ","",""},
                            {"","+TQ","-TQ","","","","_","_"},
                            {"FR","","","","","FR","",""},
                            {"","_","_","*FR","/FR","","_","_"},
                            {"i","","","","","(E)","",""}};

struct Node{
    char element;
    Node* previous;
};

class Stack{
private:
    Node* top;
    std::string input;
    std::vector<char> tableRows;
    std::vector<char> tableCols;

public:
    // Constructor 
    Stack(std::vector<char> rows, std::vector<char> cols, std::string input): top(nullptr){
        this->input = input;
        this->tableRows = rows;
        this->tableCols = cols;
        this->trace();
    }

    void push(char c){
        Node* newNode = new Node();
        newNode->element = c; 
        newNode->previous = top;
        top = newNode;
    }

    char pop(){
        if(top == nullptr)
            return '!'; 
        char element_ = top->element;
        Node* top_ = top;
        top = top->previous;
        delete top_;
        return element_; // Return the popped data
    }

    int getCol(char c){
        int i = 0;
        for(char col : this->tableCols){
            if(c == col){
                return i;
            }
            ++i;
        }
        return -1;
    }

    int getRow(char c){
        int i = 0;
        for(char row : this->tableRows){
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
        this->push('$');
        this->push('E');
        // printStack();
        for(int i = 0; input[i] != '\0'; ++i){
            printStack();
            char pop = this->pop();
            char read = this->input[i];
            std::string tableElement = table1[this->getRow(pop)][this->getCol(read)];
            // std::cout<<"  Read: "<<read<<std::endl;
            while(pop != read){
                // std::cout<<"table1["<<pop<<"]"<<"["<<read<<"]: "<<tableElement<<std::endl;
                if(tableElement == ""){
                    std::cout<<"The input: "<<this->input<<" is rejected"<<std::endl;
                    return -1;
                }
                if(tableElement[0] != '_'){
                    for(int i = tableElement.length() - 1; i >= 0; --i)
                        this->push(tableElement[i]);
                }

                // printStack();
                tableElement = table1[this->getRow(pop)][this->getCol(read)];
                pop = this->pop();
            }
            std::cout<<"--Match with input "<<read<<std::endl;
        }
        std::cout<<"The input: "<<this->input<<" is accepted"<<std::endl;
        return 1;
    }
};

int main(int argc, char* argv[]){
    Stack myStack1(ex1Rows, ex1Cols, ex1_test1);
    Stack myStack2(ex1Rows, ex1Cols, ex1_test2);
    Stack myStack3(ex1Rows, ex1Cols, ex1_test3);

    return 0; 
}