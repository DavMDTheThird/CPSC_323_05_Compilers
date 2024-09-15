//------------------------------------------------------------------------------------------------------------- 
//          Group names: David Medina Dominguez, Donovan Jabido and Jaiveer Nayen Kapadia 
//          Assignment     : No.1 
//          Due date       : 10/09/2024. 
// Purpose: Write a program to find the value of a postfix expression. Variables are one or more characters. 
//-------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <vector>
#include <string>

class postFix{
    // Vector where the 'stack' is implemented.
    std::vector<std::string> myVecStr;
    int answer = 0; 

    public: 
        postFix(std::string expression){
            for(int i = 0; i < expression.length(); ++i){
                // myVec.push_back(expression[i]); 
                std::string temp;
                do{
                    std::cout<<"A";
                    temp = temp.append(std::string(&expression[i]));
                    ++i;
                } while (expression[i+1] =! ' ' ||  '$' || '\0');
                
                myVecStr.push_back(temp);

                if(expression[i+1] == '$' || '\0'){break;}
            }
        }

        
        // if(std::isdigit(expression[i])){
        //     myVec.push_back(expression[i] - '0');
        //     // std::cout << "num #" <<i <<": "<<expression[i]<< std::endl;
        // }
        // Method that prints out the compleate stack thats left of the expression
        void printVecStr(){
            for(std::string n : myVecStr){
                std::cout<<n<<" ";
            }
                std::cout<<std::endl;
        }
};

int main(int argc, char* argv[]){

    std::cout<< "Enter a postfix expression with $ at the end:";
    std::string myExpression;
    std::cin>>myExpression;

    postFix myPostFix(myExpression);
    myPostFix.printVecStr();

    return 0;
}