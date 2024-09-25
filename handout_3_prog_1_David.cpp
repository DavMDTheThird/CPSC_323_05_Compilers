//------------------------------------------------------------------------------------------------------------- 
//          Group names: David Medina Dominguez, Donovan Jabido and Jaiveer Nayen Kapadia 
//          Assignment     : No.3 
//          Due date       : 10/25/2024. 
// Purpose: Write a program to read one token at a time from the given text file and determine whether the token 
//          is a number, an identifier or a reserved word. 
//-------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm> // Use for the find() to look if a word is within a vector
#include <iomanip> // Print columns in the terminal

class Token{
    private:
    std::string token;
    // The state has 5 states:
    // S = 0, number = 1, character = 2, unaccepted = 3, END = 4
    int state = 0;
    // Which type of token it is:
    // number = 1, identifier = 2, reserved word  = 3
    int type = 0;

    public:
    Token(std::string input){
        token = input;
    }
    int getState(){return state;}
    int getType(){return type;}
    std::string getToken(){return token;}
    void setState(int num){state = num;}
    void setType(int num){type = num;}
};

class Automata{
    private:
    std::vector<Token> myTokens;
    std::vector<std::string> reservedWords = {"while", "for", "switch", "do", "return"};

    // This functions does all the automata functionalities, it checks the current state of the 
    // identification and changes between states regarding the FA.
    // If somethig a char ins't accepted or the string has ended, it will return false.
    bool checkState(Token &token, char tokenCh){
            // std::cout<<"Token: " << token.getToken() << ", on ch: "<<tokenCh<<", has state: " 
            // << token.getState()<< std::endl;

        switch (token.getState()){
        case 0:
            if(std::isdigit(tokenCh)){
                token.setState(1);
                return true;
            }
            else if(std::isalpha(tokenCh) || tokenCh == '_'){
                token.setState(2);
                return true;
            }
            else
                token.setState(3);
            break;
        
        case 1:
            if(std::isdigit(tokenCh)){
                token.setState(1);
                return true;
            }
            else if(tokenCh == '\0'){
                token.setType(1);
                token.setState(4);
            }
            else{
                token.setState(3);
            }
            break;

        case 2:
            if(std::isalpha(tokenCh) || tokenCh == '_'){
                token.setState(2);
                return true;
            }
            else if(std::isdigit(tokenCh)){
                token.setState(2);
                return true;
            }
            else if(tokenCh == '\0'){
                if(std::find(reservedWords.begin(), reservedWords.end(),
                             token.getToken()) != reservedWords.end())
                    token.setType(3);
                else
                    token.setType(2);
                token.setState(4);
            }
            else
                token.setState(3);
            break;
        
        default:
            break;
        }
        return false;
    }

    // Function that checks the entire length of the token and pushes it to the vector of tokens
    void checkToken(std::string token){
        Token newToken(token);
        for(int i = 0; i <= token.size(); ++i){
            if(checkState(newToken, token[i])){
                // std::cout<<token[i]<<std::endl;
            }
            else{break;}
        }
        myTokens.push_back(newToken);
    }

    public:
    Automata(char* fileName){
        std::ifstream file(fileName);
        // Check if the txt file is open
        if(!file.is_open())
            std::cerr << "Unable to open file" << std::endl;
        else{
            std::string line;
            while (std::getline(file, line)){
                checkToken(line);
            }
            printTokens();
            file.close();
        }
    }

    // Function that prints out all the tokens and their respective type
    void printTokens(){
        std::cout << std::left << std::setw(13) << "Token"
                               << std::setw(13) << "Number"
                               << std::setw(13) << "identifier"
                               << std::setw(13) << "Reserved Word" << std::endl;

        for(Token token : myTokens){
            std::cout<<std::left<<std::setw(13) << token.getToken()
                                <<std::setw(13) << (token.getType() == 1?"yes":"no")
                                <<std::setw(13) << (token.getType() == 2?"yes":"no")
                                <<std::setw(13) << (token.getType() == 3?"yes":"no")
                                <<std::endl;
        }
    }
};

int main(int argc, char* argv[]){
    Automata myAutomata(argv[1]);
    return 0;
}