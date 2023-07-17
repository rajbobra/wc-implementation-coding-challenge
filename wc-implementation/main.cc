#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <ctype.h>

std::ifstream openFile(char*);
void countBytes(std::ifstream*, char*);
void countLines(std::ifstream*, char*);

int main(int argc, char** argv) {
    char* fileName;
    std::ifstream myFile;
    opterr = 0;
    int c;

    //parsing the command and getting the options
    while((c=getopt(argc, argv, "c:l:")) != -1) {
        switch(c) {
            case 'c':
                fileName = optarg;
                myFile = openFile(fileName);
                countBytes(&myFile, fileName);
                break;
            case 'l':
                fileName = optarg;
                myFile = openFile(fileName);
                countLines(&myFile, fileName);
                break;
            case '?':
                std::cerr << "Unknown option or missing argument\n";
                return 1;
            default:
                std::cerr << "Error!!\n";
                return 1;
        }
    }
    
    return 0;
}

std::ifstream openFile(char* fileName) {

    std::ifstream myFile;
    myFile.open(fileName, std::ios::binary);
        
    if(!myFile) { 
        std::cerr << "Error opening the file\n"; 
    }
    return myFile;
}

void countBytes(std::ifstream* myFile, char* fileName) {
    // Move the file pointer to EOF
    myFile->seekg(0, std::ios::end);

    // Get the new current file pointer position, since we moved the pointer to EOF, this gives the total bytes
    std::streampos bytes = myFile->tellg();

    std::cout << std::to_string(bytes) << " " << fileName << std::endl;

    myFile->close();
}

void countLines(std::ifstream* myFile, char* fileName) {
    int lines = 0;
    std::string throwaway;
    
    // count lines, getline defaulted at delim \n
    while(std::getline(*myFile, throwaway)) { lines++; }

    std::cout << std::to_string(lines) << " " << fileName << std::endl;

    myFile->close();
}