//------------------------------------------------------------------------------------------------------------- 
//          Group names: David Medina Dominguez, Donovan Jabido and Jaiveer Nayen Kapadia 
//          Assignment     : No.1 
//          Due date       : 10/09/2024. 
// Purpose: this program reads an expression in postfix form, evaluates the expression 
// and displays its value 
//-------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <vector>

class stack{
        std::vector<char> myVec;

    public:
        stack(std::string expression){
            for(int i = 0; i < expression.length(); ++i){
                myVec.push_back(expression[i]);
                std::cout << expression[i] << std::endl;
            }

            printVec(myVec);
        }
        

        void printVec(std::vector<char> vec_){
            for(int i = 0; i < myVec.size(); ++i){
                std::cout<<myVec[i]<<", ";
            }
        }
};

int main(){ 
    std::cout<< "Give me your expression:";
    std::string myExpression;
    std::cin>>myExpression;

    stack myStack(myExpression);


    return 0;
}