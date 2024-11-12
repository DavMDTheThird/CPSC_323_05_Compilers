#include <iostream>
#include <fstream>  // Include file stream library

#ifndef P1_READFILE_H
#define P1_READFILE_H

class P1_readFile{
private:

public:
    P1_readFile(std::string fileName = "final.txt"){
        std::string fileTitle;
        int i = 0;
        while(fileName[i] != '.'){
            fileTitle += fileName[i];
            ++i;
        }
        fileTitle += "f24.txt";

        std::ofstream fileOut(fileTitle);
        
        std::ifstream fileIn(fileName);
        if (!fileIn){std::cout << "Unable to open file\n";}
        if (!fileOut){std::cout << "Unable to create file\n";}

        std::string word;
        bool comment = false;
        while(fileIn >> word){
            if(word[0] == '('){
                if(word[1] == '*'){
                    comment = true;
                }
            }
            if(!comment){
                fileOut << word;
                fileOut << " ";
                // std::cout << word << " ";
                if(word[word.length()-1] == ';'){
                fileOut << "\n";
                }
            }
            else{
                if(word[word.length()-1] == ')'){
                    if(word[word.length()-2] == '*'){
                        comment = false;
                    }
                }
            }
        }

        fileIn.close();
        fileOut.close();
    }
};
#endif