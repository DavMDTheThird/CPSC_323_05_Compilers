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
                if(expression[i] == 'a'){
                    myVec.push_back(5);
                }
                else if(expression[i] == 'b'){
                    myVec.push_back(7);
                }
                else if(expression[i] == 'c'){
                    myVec.push_back(2);
                }
                else if(expression[i] == 'd'){
                    myVec.push_back(4);
                }

                else if(isdigit(expression[i])){
                    myVec.push_back(expression[i] - '0');
                    // std::cout << "num #" <<i <<": "<<expression[i]<< std::endl;
                    // printVec(myVec);
                }
                else{
                    // std::cout << "exp #" <<i <<": "<<expression[i]<< std::endl;
                    if(expression[i] == '*'){
                        int num1 = int(myVec.back());myVec.pop_back();
                        int num2 = int(myVec.back());myVec.pop_back();

                        myVec.push_back(num2 * num1);
                    }
                    else if(expression[i] == '+'){
                        int num1 = int(myVec.back());myVec.pop_back();
                        int num2 = int(myVec.back());myVec.pop_back();
                        
                        myVec.push_back(num2 + num1);
                    }
                    else if(expression[i] == '/'){
                        int num1 = int(myVec.back());myVec.pop_back();
                        int num2 = int(myVec.back());myVec.pop_back();

                        myVec.push_back(num2 / num1);
                    }
                    else if(expression[i] == '-'){
                        int num1 = int(myVec.back());myVec.pop_back();
                        int num2 = int(myVec.back());myVec.pop_back();

                        myVec.push_back(num2 - num1);
                    }
                    else if(expression[i] == '$'){
                        break;
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
    bool continue_ = true;
    while(continue_){
        std::cout<< "Enter a postfix expression with $ at the end:";
        std::string myExpression;
        std::cin>>myExpression;
        postFix myPostFix(myExpression);


        std::string answer;
        std::cout<< "CONTINUE(y/n)?";
        std::cin>>answer;
        if(answer != "y")
            continue_ = false;
    }


    return 0;
}