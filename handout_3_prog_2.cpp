//------------------------------------------------------------------------------------------------------------- 
//          Group names: David Medina Dominguez, Donovan Jabido and Jaiveer Nayen Kapadia 
//          Assignment     : No.3 
//          Due date       : 10/25/2024. 
// Purpose: Write a program to determine whether an input string is accepted or rejected by the grammar. 
//          Hint, first you have to complete the FA. 
//-------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <string>

class Automata{
    private:
    // The state has only 4 states:
    // S = 0, B = 1, C = 2, END = 3
    int state = 0;
  
    // This function is the FA, checks and changes the state regarding the next element of an input.
    // If there is something that is not accpeted, it returns false.
    bool checkAutomata(char next){
        switch(state){
            case 0:
                if(next == 'a')
                    return true;
                else if(next == 'b'){
                    state = 1;
                    return true;
                }
                else if(next = 'c'){
                    state = 2;
                    return true;
                }
                break;

            case 1:
                if(next == 'b')
                    return true;
                else if(next == 'a'){
                    state = 2;
                    return true;
                }
                else if (next == '$' || next == '\0'){
                    state = 3;
                    return true;
                }
                break;

            case 2:
                if(next == 'a'){
                    state = 0;
                    return true;
                }
                else if (next == '$' || next == '\0'){
                    state = 3;
                    return true;
                }
                break;                 

            default:
                break;
        }
        return false;
    }
    
    public:
    // Constructor that tells you if the input is accepted or not by the FA.
    Automata(std::string input){
        for(int i = 0; i < input.length();++i){
            if(checkAutomata(input[i])){
                if(state == 3){
                    std::cout<<"String '"<<input<<"' is accepted"<<std::endl;
                    break;
                }
            }
            else{
                std::cout<<"String '"<<input<<"' is NOT accepted"<<std::endl;
                break;
            }
        }
    }
};

int main(int argc, char* argv[]){
    for(int i = 1; i < argc; ++i){
        Automata myAutomata(argv[i]);
    }    
    return 0;
}