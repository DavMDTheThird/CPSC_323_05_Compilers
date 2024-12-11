#include <iostream>
#include <fstream>  // Include file stream library

#ifndef FINALPROJECT_READFILE_H
#define FINALPROJECT_READFILE_H

class ReadFile{
private:
    std::string fileName;

public:
    std::string getFileName(){return this->fileName;}

    ReadFile(std::string fileName_ = "final.txt"){
        this->fileName = "";
        int i = 0;
        while(fileName_[i] != '.'){
            this->fileName += fileName_[i];
            ++i;
        }
        // Set up the name of the txt file
        this->fileName += "24.txt";

        std::ofstream fileOut(this->fileName);
        
        std::ifstream fileIn(fileName_);
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
                // Write the txt file with spaces in between tokens
                fileOut << word;
                fileOut << " ";
                // std::cout << word << " ";
                if(word[word.length()-1] == ';'){
                    fileOut << "\n";
                }
                else if(word == "var" || word == "begin" || word == "end"){
                    fileOut << "\n";
                }
            }
            else{
                // If the end of a comment is detected, start pushing words once again to the txt file
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