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
    private:
        std::vector<std::string> myVecStr;
        int answer = 0; 

    public: 
        postFix(std::string expression){
            for(int i = 0; i < expression.length(); i){
                std::string temp;
                do{
                    temp.push_back(expression[i]);
                    if(checkIfOperator(expression[i])){++i;break;} //If there is an operator at the start
                    ++i;
                }while((expression[i] != ' ')&&(expression[i] != '$')&&(expression[i] != '\0')&&!checkIfOperator(expression[i])); //Stop when you find the end, blank space or operator [end of variable]

                myVecStr.push_back(temp);
                
                if(expression[i] == ' '){++i;} // Skip/ignore blank spaces
                if((expression[i]=='$')||expression[i]=='\0'){break;} // End of string
            }
            // printVecStr();
            // setValValues();
            // printVecStr();
        }

        void solvePostFix(){

        }

        int getAnswer(){
            return answer;
        }

        //Check if a character is an operator
        bool checkIfOperator(char expression){
            if((expression=='+')||(expression=='-')||(expression=='*')||(expression=='/'))
                return true;
            return false;
        }

        void setValValues(){
            int i = 0; 
            for(std::string element : myVecStr){
                // If it is a number
                // If its not an operator, it must be a variable
                if(!isdigit(element[0])&&element[0]!='+' && element[0]!='-' && element[0]!='*' && element[0]!='/'){
                    std::string value;
                    std::cout << "Enter the value of " << element << ": ";
                    std::cin >> value;
                    myVecStr[i] = value;
                }
                i++;
            }
        }

        
        // Method that prints out the compleate stack thats left of the expression
        void printVecStr(){
            for(std::string n : myVecStr){
                std::cout<<n<<" ";
            }
                std::cout<<std::endl;
        }
};

int main(int argc, char* argv[]){
    std::string myExpression;
    std::cout<< "Enter a postfix expression with $ at the end:";
    std::getline(std::cin, myExpression);
    postFix myPostFix(myExpression);
    // myPostFix.printVecStr();

    return 0;
}