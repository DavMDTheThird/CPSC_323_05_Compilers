//------------------------------------------------------------------------------------------------------------- 
//          Group names: David Medina Dominguez, Donovan Jabido and Jaiveer Nayen Kapadia 
//          Assignment     : No.2 
//          Due date       : 10/18/2024. 
// Purpose: Write a program to find the value of a postfix expression. Variables are one or more characters. 
//-------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <vector>
#include <string>
#include <limits>

class postFix{
    private:
        // Vector where the 'stack' is implemented.
        std::vector<std::string> myVecStr;
        // Vector where the final math answer is concatenated
        std::vector<int> myVecInt;
        int answer = 0; 

    public: 
        // Constructor, it parses the input string, into the Vector string.
        // The only thing that is missing is that if you start with a number and follow with letters, it will record it 
        // as a variable!!!!, instead of recoring them as different separate. If a space is between them, there is no 
        // problem. Imporovements can be done.
        postFix(std::string expression){
            for(int i = 0; i < expression.length(); i){
                std::string temp;
                do{
                    temp.push_back(expression[i]);
                    if(checkIfOperator(expression[i])){++i;break;} //If there is an operator at the start
                    ++i;
                    // If it finds a blank space, dolar sign, end of string, or an operator, STOP. 
                }while((expression[i]!=' ')&&(expression[i]!='$')&&(expression[i]!='\0')&&
                !checkIfOperator(expression[i])); 

                // Record and push the variable/number
                myVecStr.push_back(temp);
                
                if(expression[i]==' '){++i;} // Skip/ignore blank spaces
                if((expression[i]=='$')||expression[i]=='\0'){break;} // End of string
            }
            // printVecStr();
            setVariableValues();
            // printVecStr();
            solvePostFix();
        }

        // Solves the postFix equation.
        void solvePostFix(){
            // Go though the Vector of strings, which should only have either numbers or operators.
            for(std::string element : myVecStr){
                // If a number is found, push it to the 'stack'
                if(std::isdigit(element[0])){
                    myVecInt.push_back(std::stoi(element));
                }
                // If it is an operator, solve it.
                else{
                    if(element[0] == '+'){
                        int num1 = myVecInt.back();myVecInt.pop_back();
                        int num2 = myVecInt.back();myVecInt.pop_back();

                        myVecInt.push_back(num2 + num1);
                    }
                    else if(element[0] == '-'){
                        int num1 = myVecInt.back();myVecInt.pop_back();
                        int num2 = myVecInt.back();myVecInt.pop_back();

                        myVecInt.push_back(num2 - num1);
                    }
                    else if(element[0] == '*'){
                        int num1 = myVecInt.back();myVecInt.pop_back();
                        int num2 = myVecInt.back();myVecInt.pop_back();

                        myVecInt.push_back(num2 * num1);
                    }
                    else if(element[0] == '/'){
                        int num1 = myVecInt.back();myVecInt.pop_back();
                        int num2 = myVecInt.back();myVecInt.pop_back();

                        myVecInt.push_back(num2 / num1);
                    }
                }

            }
            // If by the end, there are more than one elements in the 'stack', the operation is incomplete (so it tells you)
            if(myVecInt.size() != 1){
                std::cout<<"There are still elements in the stack, operation incomplete!"<<std::endl;
            }
            answer = myVecInt[0];
            std::cout<<"Expression's value is: "<<answer<<std::endl;
        }

        //Check if a character is an operator
        bool checkIfOperator(char expression){
            if((expression=='+')||(expression=='-')||(expression=='*')||(expression=='/'))
                return true;
            return false;
        }

        // Goes through the vector of strings to find the variables and asign a numeric value to them
        void setVariableValues(){
            int i = 0; 
            for(std::string element : myVecStr){
                // If it isn't a number
                // If it isn't an operator, it must be a variable
                if(!isdigit(element[0])&&!checkIfOperator(element[0])){
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
    bool continue_ = true;
    while(continue_){
        std::string myExpression;
        std::cout<< "Enter a postfix expression with $ at the end: ";
        std::getline(std::cin, myExpression);
        postFix myPostFix(myExpression);

        std::string answer;
        std::cout<< "CONTINUE(y/n)?";
        std::cin>>answer;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
        if(answer != "y")
            continue_ = false;
    }
    return 0;
}