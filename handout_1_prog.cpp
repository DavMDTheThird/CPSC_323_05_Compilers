//------------------------------------------------------------------------------------------------------------- 
//          Group names: David Medina Dominguez, Donovan Jabido and Jaiveer Nayen Kapadia 
//          Assignment     : No.1 
//          Due date       : 10/09/2024. 
// Purpose: this program reads an expression in postfix form, evaluates the expression 
// and displays its value 
//-------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <vector>
#include <string>

class postFix{
    std::vector<int> myVec;
    int answer = 0; 
    public: 
        postFix(std::string expression){
            for(int i = 0; i < expression.length(); ++i){
                if(isdigit(expression[i])){
                    myVec.push_back(expression[i] - '0');
                    std::cout << "num #" <<i <<": "<<expression[i]<< std::endl;
                    // printVec(myVec);
                }
                else{
                    std::cout << "exp #" <<i <<": "<<expression[i]<< std::endl;
                    if(expression[i] == '*'){
                        int num1 = int(myVec.back());myVec.pop_back();
                        int num2 = int(myVec.back());myVec.pop_back();

                        myVec.push_back(num1 * num2);
                    }
                    else if(expression[i] == '+'){
                        int num1 = int(myVec.back());myVec.pop_back();
                        int num2 = int(myVec.back());myVec.pop_back();
                        
                        myVec.push_back(num1 + num2);
                    }
                    else if(expression[i] == '/'){
                        int num1 = int(myVec.back());myVec.pop_back();
                        int num2 = int(myVec.back());myVec.pop_back();

                        myVec.push_back(num1 / num2);
                    }
                    else if(expression[i] == '-'){
                        int num1 = int(myVec.back());myVec.pop_back();
                        int num2 = int(myVec.back());myVec.pop_back();

                        myVec.push_back(num1 - num2);
                    }
                    else{
                        std::cout<<"There was an error"<<std::endl;
                        break;
                    }
                }
                
            }
            // std::cout << myVec[0] << std::endl;
            printVec(myVec);
        }

        void printVec(std::vector<int> vec_){
            for(int n : myVec){
                std::cout<<n<<" ";
            }
                std::cout<<std::endl;
        }
};

int main(){ 
    std::cout<< "Give me your expression:";
    std::string myExpression;
    std::cin>>myExpression;

    postFix myPostFix(myExpression);

    return 0;
}