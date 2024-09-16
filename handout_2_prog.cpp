//------------------------------------------------------------------------------------------------------------- 
//          Group names: David Medina Dominguez, Donovan Jabido and Jaiveer Nayen Kapadia 
//          Assignment     : No.2 
//          Due date       : 10/18/2024. 
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
            // std::cout<<"Trying ("<<expression.length()<<"): "<<expression<<std::endl;
            for(int i = 0; i < expression.length(); i){
                std::string temp;
                do{
                    std::cout<<"now:"<<expression[i]<<std::endl;
                    temp.push_back(expression[i]);
                    ++i;
                } while ((expression[i] != ' ')&&(expression[i] != '$')&&(expression[i] != '\0'));
                
                std::cout<<"temp: "<<temp<<std::endl;
                std::cout<<"-----------------"<<std::endl;
                // myVecStr.push_back(temp);
                // printVecStr();
                if(expression[i] == ' '){++i;}
                if((expression[i]=='$')||expression[i]=='\0'){break;}
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
    std::getline(std::cin, myExpression);
    std::cout<<"You said: "<<myExpression<<std::endl;

    postFix myPostFix(myExpression);
    // myPostFix.printVecStr();

    return 0;
}