#include <iostream>
#include <vector>
#include <fstream>

#ifndef FINALPROJECT_TRANSLATION_H
#define FINALPROJECT_TRANSLATION_H

class TranslateFile{
private:
    std::string fileName;
    // N variables. They are going to be stored from 1 to n. Leaving the index 0 for their type 
    std::vector<std::vector<std::string>> variables;

public:
    std::string getFileName(){return this->fileName;}

    TranslateFile(std::string fileName_ = "final24.txt"){
        this->fileName = "";
        int i = 0;
        while(fileName_[i] != '.'){
            this->fileName += fileName_[i];
            ++i;
        }
        this->fileName += ".cpp";

        std::ofstream fileOut(this->fileName);
        
        std::ifstream fileIn(fileName_);
        if (!fileIn){std::cout << "Unable to open file\n";}
        if (!fileOut){std::cout << "Unable to create file\n";}

        std::string word;
        std::vector<std::string> variable;
        bool var = false;
        bool type = false;
        bool printing = false;
        bool mainProgram = false;
        while(fileIn >> word){
            if(!mainProgram){
                if(word == "begin"){
                    // Start of the c++ file:
                    fileOut << "#include <iostream>\n";
                    fileOut << "using namespace std;\n";
                    fileOut << "int main()\n";
                    fileOut << "{\n";
                    for(std::vector<std::string> myVariables : this->variables){
                        // Here would be the other types, but only integer was asked for
                        if(myVariables[0] == "integer"){
                            fileOut << "int ";
                        }
                        for(int i = 1; i < myVariables.size(); ++i){
                            fileOut << myVariables[i];
                            fileOut << " ";
                            if(i < myVariables.size()-1){
                                fileOut << ", ";
                            }
                        }
                        fileOut << ";\n";
                    }
                    mainProgram = true; 
                }
                else if(word == "var"){
                    var = true;
                    type = false;
                    variable.clear();
                    variable.push_back("type");
                }
                else if(var){
                    if(type){
                        variable[0] = word;
                        type = false;
                    }
                    else if(word == ":"){
                        type = true;
                    }
                    else if(word != ";" && word != ","){
                        variable.push_back(word);
                    }
                    else if(word == ";"){
                        this->variables.push_back(variable);
                        var = false;
                        type = false;
                    }
                    // else{
                    //     var = false;
                    // }
                }
            }
            else{
                if(!printing){
                    if(word == "print"){
                        fileOut << "cout";
                        printing = true;
                    }
                    else if(word == "end"){
                        fileOut << "// system ( \"pause\" ) ;\n";
                        fileOut << "return 0 ;\n";
                        fileOut << "}";
                    }
                    else if(word == ";"){
                        fileOut << ";\n";
                    }
                    else{
                        fileOut << word;
                        fileOut << " ";
                    }  
                }
                else{
                    if(word == "("){
                        fileOut << "<< ";
                    }
                    else if(word == ","){
                        fileOut << "<< ";
                    }
                    else if(word == ")"){
                        fileOut << "<<endl ";
                        printing = false;
                    }
                    else{
                        fileOut << word;
                        fileOut << " ";
                    }
                }
            }
        }

        
        fileIn.close();
        fileOut.close();
    }

};
#endif