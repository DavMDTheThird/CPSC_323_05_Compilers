#include <iostream>
#include <fstream>  // Include file stream library
#include <string>
#include <vector>

#ifndef P1_READFILE_H
#define P1_READFILE_H

class P1_readFile{
private:
std::vector<std::vector<std::string>> myFileWords;

public:
    P1_readFile(std::string fileName = "final.txt"){
        std::ifstream file(fileName);
        if (!file){std::cout << "Unable to open file\n";}

        std::vector<std::string> myLineWords;
        std::string line;
        while (std::getline(file, line)){// Read the file line by line
            myLineWords.clear();
            std::string word = "";
            for(int i = 0; i <= line.length(); ++i){
                if((line[i] == ' ' && word != "")||
                    line[i] == ';'||line[i] == ','||
                    line[i] == '\0'){
                    myLineWords.push_back(word);
                    if(line[i]==';' || line[i]==','){
                        std::string A; A+=line[i];
                        myLineWords.push_back(A);
                    }

                    // std::cout<<"word: "<<word<<std::endl;
                    word = "";
                }
                else if (line[i] != ' '){
                    // std::cout<<line[i]<<std::endl;
                    word += line[i];
                }
            }
            // std::cout<<std::endl;
            if(myLineWords[0] != "\0"){
                this->myFileWords.push_back(myLineWords);
            }
        }
        // popComments();
        printVec();

        file.close();  // Close the file
    }

    // void popComments(){
    //     std::vector<std::vector<std::string>> temp_ = this->myFileWords;
    //     this->myFileWords.clear();
    //     for (std::vector<std::string> line : temp_) {
    //         for (std::string word : line) {
    //         }
    //     }
    // }

    void printVec(){
        for (const auto& line : this->myFileWords) {
            for (const auto& word : line) {
                std::cout << word << " "<< std::endl;
            }
            // std::cout << std::endl;
        }
    }
};
#endif