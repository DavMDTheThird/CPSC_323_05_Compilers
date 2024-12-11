#include <iostream>
#include <fstream>  // Include file stream library
#include <functional>
#include <sstream>

#ifndef FINALPROJECT_COMPILER_H
#define FINALPROJECT_COMPILER_H

// Node Object Class for the stack
struct Node{
    std::string element;
    Node* previous;
};

class Stack{
private:
    Node* top;

public:
    // Constructor:
    Stack(){
        this->top = nullptr;
    }

    // Push a new node to the Stack
    void push(std::string instance){
        Node* newNode = new Node();
        newNode->element = instance; 
        newNode->previous = top;
        top = newNode;
    }

    // Pops the top node of the stack, returns its value
    // Error handling should be introduced if return "!"
    std::string pop(){
        if(top == nullptr)
            return "!"; 
        std::string element_ = top->element;
        Node* top_ = top;
        top = top->previous;
        delete top_;
        return element_; // Return the popped data
    }

    // A function that prints the current Stack
    void printStack(){
        // Definition of a recursive function to print the elements in correct order 
        //      (left to right) -> (bottom of Stack to top of the Stack)
        std::function<void(Node*)> print_element = [&print_element](Node* element){
            if(element->previous == nullptr)
                std::cout<<element->element;
            else{
                print_element(element->previous);
                std::cout<<" "<<element->element;
            }
        };
        std::cout<<"Stack: ";
        if(this->top != nullptr){
            print_element(this->top);
        }
        std::cout<<std::endl;
    }
    
};



class cCompiler{
private:
    std::string fileName;
    std::vector<std::string> identifiers;
    std::string ERROR;
    std::string MISTAKE;
    int LINE;
    std::vector<std::string> rows = {"P", "I", "J", "V", "V'", "Y", "H", "H'", "Q", "W", "S", "A", "E", "E'", "T", "T'", "F", "N", "G", "D", "L"};
    std::vector<std::string> cols = {"a", "b", "c", "d", "l", "f", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "+", "-", "*", "/", "=", "\"value=\"", ",", "(",  ")", ":", ";", "print", "integer", "program", "var", "beign", "end", "$"};
    std::vector<std::string> reservedWords = {"print", "integer", "program", "var", "begin", "end", "\"value=\""};
    

    std::vector<std::vector<std::string>> predictiveParsingTable = {
{"","","","","","","","","","","","","","","","","","","","","","","","","","","","","","program I ; var J begin H end","","",""},
{"L {L|D}","L {L|D}","L {L|D}","L {L|D}","L {L|D}","L {L|D}","","","","","","","","","","","","","","","","","","","","","","","","","","",""},
{"V : Y ;","V : Y ;","V : Y ;","V : Y ;","V : Y ;","V : Y ;","","","","","","","","","","","","","","","","","","","","","","","","","","",""},
{"I V'","I V'","I V'","I V'","I V'","I V'","","","","","","","","","","","","","","","","","","","","","","","","","","",""},
{"","","","","","","","","","","","","","","","","","","","","","",", V","","","λ","","","","","","",""},
{"","","","","","","","","","","","","","","","","","","","","","","","","","","","","integer","","","",""},
{"Q H'","Q H'","Q H'","Q H'","Q H'","Q H'","","","","","","","","","","","","","","","","","","","","","","Q H'","","","","",""},
{"H","H","H","H","H","H","","","","","","","","","","","","","","","","","","","","","","H","","","","","λ"},
{"A","A","A","A","A","A","","","","","","","","","","","","","","","","","","","","","","W","","","","",""},
{"","","","","","","","","","","","","","","","","","","","","","","","","","","","print ( S I ) ;","","","","",""},
{"λ","λ","λ","λ","λ","λ","","","","","","","","","","","","","","","","\"value=\" ,","","","","","","","","","","",""},
{"I = E ;","I = E ;","I = E ;","I = E ;","I = E ;","I = E ;","","","","","","","","","","","","","","","","","","","","","","","","","","",""},
{"T E'","T E'","T E'","T E'","T E'","T E'","T E'","T E'","T E'","T E'","T E'","T E'","T E'","T E'","T E'","T E'","T E'","T E'","","","","","","T E'","","","","","","","","",""},
{"","","","","","","","","","","","","","","","","+ T E'","- T E'","","","","","","","λ","","λ","","","","","",""},
{"F T'","F T'","F T'","F T'","F T'","F T'","F T'","F T'","F T'","F T'","F T'","F T'","F T'","F T'","F T'","F T'","F T'","F T'","F T'","","","","","F T'","","","","","","","","",""},
{"","","","","","","","","","","","","","","","","λ","λ","* F T'","/ F T'","","","","","λ","","λ","","","","","",""},
{"I","I","I","I","I","I","N","N","N","N","N","N","N","N","N","N","N","N","","","","","","( E )","","","","","","","","",""},
{"","","","","","","G D {D}","G D {D}","G D {D}","G D {D}","G D {D}","G D {D}","G D {D}","G D {D}","G D {D}","G D {D}","","","","","","","","","","","","","","","","",""},
{"","","","","","","λ","λ","λ","λ","λ","λ","λ","λ","λ","λ","+","-","","","","","","","","","","","","","","",""},
{"","","","","","","0","1","2","3","4","5","6","7","8","9","","","","","","","","","","","","","","","","",""},
{"a","b","c","d","l","f","","","","","","","","","","","","","","","","","","","","","","","","","","",""}};


public:
    std::string getFileName(){return this->fileName;}

    cCompiler(std::string fileName_ = "final.txt"):fileName(fileName_),LINE(1){
        int compiler = trace();

        if(1 == compiler){
            std::cout<<"The program is ready to be compiled"<<std::endl;
        }
        else{
            if(this->ERROR == "Y"){
                this->ERROR = "integer";
            }
            else if(this->ERROR == "P"){
                this->ERROR = "program";
            }
            else if(this->ERROR == "S"){
                this->ERROR = "\"value=\"";
            }
            else if(this->ERROR == "D" || this->ERROR == "{D}"){
                this->ERROR = "a number";
            }

            if(this->ERROR == "I" || this->ERROR == "H'"){
                std::cout<<"The program has errors:"<<std::endl;
                std::cout<<"ERROR on line "<<this->LINE<<": unkown identifier '"<<this->MISTAKE<<"'"<<std::endl;
            }
            else{
                std::cout<<"The program has errors:"<<std::endl;
                std::cout<<"ERROR on line "<<this->LINE<<": expected '"<<
                            this->ERROR<<"' but '"<<this->MISTAKE<<"' was given."<<std::endl;
            }
        }
    }

    int trace(){
        std::ifstream fileIn(this->fileName);
        if (!fileIn){std::cout << "Unable to open file\n";}

        // Create my Stack for the parsing
        Stack myStack;

        //Push the end state and initial state
        myStack.push("$");
        myStack.push(this->rows[0]);

        // Falgs
        bool identifierFlag = false;
        bool beginFlag = false;
        // Read word for word the instances of the file
        std::string readW;
        while(fileIn >> readW){
        // myStack.printStack();
        // std::cout<<std::endl;
        // std::cout<<"Read: "<<readW<<std::endl;
            std::string pop = myStack.pop();
            if(pop == "!"){std::cout<<"Stack is empty"<<std::endl;break;}

            if((readW == ";" || readW == "var" || readW == "begin") && readW != "print" && readW != "\"value=\""){
                this->LINE += 1;
            }

            if (identifierFlag && readW != "," && readW != ":")
                this->identifiers.push_back(readW);
            if(pop == "var")
                identifierFlag = true;

            //If the read word is NOT a reserved word
            if(!isReservedWord(readW)){
                // Go through the word, and if there is no match the index does not advance
                unsigned int index = 0;
                do{
                    if(beginFlag && pop == "I"){
                        if(!isIdentifiers(readW)){
                            this->ERROR = "I";
                            this->MISTAKE = readW;
                            return 0;
                        }
                    }

                    if(readW == pop){
                    // std::cout<<"Match with: "<<pop<<" == "<<readW[index]<<std::endl;
                        ++index;
                    }
                    // If a match is found
                    else if(pop.length() == 1 && pop[0] == readW[index]){
                        // If the read character-word and pop element are a match
                    // std::cout<<"Match with: "<<pop<<" == "<<readW[index]<<std::endl;
                    // myStack.printStack();
                                                
                        // Go to mext element in the stack if NOT the last element
                        pop = myStack.pop();                                           
                        // Go to next character
                        ++index;

                        // If recursion of multiple characters/digits is available
                        if(pop == "{L|D}" && index < readW.size()){
                            if(isCharacter(readW[index])){myStack.push("{L|D}");myStack.push("L");}
                            else if(isDigit(readW[index])){myStack.push("{L|D}");myStack.push("D");}
                            pop = myStack.pop();}
                        else if(pop == "{D}" && index < readW.size()){
                            myStack.push("{D}");myStack.push("D");
                            pop = myStack.pop();}
                    }
                    // If a match is not found
                    else{
                    // std::cout<<"1. pop: "<<pop<<" readW: "<<readW[index]<<std::endl;
                        // Look for the character of the word in the parsing table
                        std::string readWChar; readWChar += readW[index];
                        int row = getRow(pop);
                        int col = getCol(readWChar);
                        if(row == -1 || col == -1){
                            this->ERROR = pop;
                            this->MISTAKE = readW;
                            return 0;
                        }
                        std::string tableElement = predictiveParsingTable[row][col];

                        if(tableElement != "λ")
                            pushReveseOrder(myStack, tableElement);
                        
                    // myStack.printStack();
                        // Go to mext element in the stack
                        pop = myStack.pop();
                        if(pop == "!"){std::cout<<"Stack is empty"<<std::endl;break;}
                        if(pop == ":")
                            identifierFlag = false;
                    }
                }while(index < readW.size());

                // pop out any possible recursion from the stack
                std::string temp = myStack.pop();
                (temp == "{L|D}" || temp == "{D}") ? void() : myStack.push(temp);
            }
            // If the word is a reserved word
            else{
                // If the reserved word does NOT match 
                while(pop != readW){
                // std::cout<<"2. pop: "<<pop<<" readW: "<<readW<<std::endl;
                    //Obtain the elements from the predictive parsing table
                    int row = getRow(pop);
                    int col = getCol(readW);
                    if(row == -1 || col == -1){
                        this->ERROR = pop;
                        this->MISTAKE = readW;
                        return 0;
                    }
                    std::string tableElement = predictiveParsingTable[row][col];

                    if(tableElement != "λ")
                        pushReveseOrder(myStack, tableElement);

                // myStack.printStack();
                    // Go to mext element in the stack
                    pop = myStack.pop();
                    if(pop == "!"){std::cout<<"Stack is empty"<<std::endl;break;}
                }
                if(pop == "begin")
                    beginFlag = true;
            // std::cout<<"Match with: "<<pop<<" == "<<readW<<std::endl;
            }
        }

        // pop the last element of the stack, and if it is a $, the program has no compile errors
        std::string pop = myStack.pop();
        if("$" == pop){
            printIdentifiers();
            return 1;
        }
        else{
            return 0;
        }
    }

    // Given a string instance, find it in the given columns (terminals)
    // Error handling should be added if return -1 
    int getCol(std::string instance){
        int i = 0;
        for(std::string col : this->cols){
            if(instance == col){
                return i;
            }
            ++i;
        }
        return -1;
    }

    // Given a string instance, find it in the given column (state)
    // Error handling should be added if return -1 
    int getRow(std::string instance){
        int i = 0;
        for(std::string row : this->rows){
            if(instance == row){
                return i;
            }
            ++i;
        }
        return -1;
    }

    // Function that returns True/False if a given string is within the reserved words list
    bool isReservedWord(std::string instance){
        for(std::string word : this->reservedWords){
            if(instance == word){
                return true;
            }
        }
        return false;
    }

    // Push the table instances to the Stack in reverse order
    void pushReveseOrder(Stack& myStackRef, std::string instances){
        std::vector <std::string> tableElementVec;
        std::istringstream myStringStream(instances);
        std::string instance;
        while(myStringStream >> instance){
            tableElementVec.push_back(instance);
        }
        for (std::vector<std::string>::reverse_iterator instanceIT = tableElementVec.rbegin(); 
                                                        instanceIT != tableElementVec.rend(); 
                                                        ++instanceIT){
            // std::cout<<"Pushing: "<<*instanceIT<<std::endl;
            myStackRef.push(*instanceIT);
        }
    }
    // Function that returns if a character is a number
    bool isDigit(char c) {
        return (c >= '0' && c <= '9');
    }

    // Function that returns if a character is a letter from the alphabet
    bool isCharacter(char c) {
        return ( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') );
    }

    // Funciton that prints out the identifiers
    void printIdentifiers(){
        std::cout<<"indentifiers: "<<std::endl;
        for(std::string identifier : this->identifiers){
            std::cout<<identifier<<" ";
        }
        std::cout<<std::endl;
    }

    // Funciton that prints out the identifiers
    bool isIdentifiers(std::string instance){
        for(std::string identifier : this->identifiers){
            if(instance == identifier){
                return true;
            }
        }
        return false;
    }
};
#endif