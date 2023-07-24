#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <ctype.h>

std::ifstream openFile(char*);
void closeFile(std::ifstream*);
void printOutput(std::string, char*);
std::streampos countBytes(std::ifstream*);
int countLines(std::ifstream*);
int countWords(std::ifstream*);

int main(int argc, char** argv) {
    char* fileName;
    std::ifstream myFile;
    std::streampos bytes;
    int lines;
    int words;
    opterr = 0;
    int c;

    if(argc == 2) {
        fileName = argv[1];
        myFile = openFile(fileName);
        bytes = countBytes(&myFile);
        myFile = openFile(fileName);
        lines = countLines(&myFile);
        myFile = openFile(fileName);
        words = countWords(&myFile);
        printOutput(std::to_string(bytes) + " " + std::to_string(lines) + " " + std::to_string(words), fileName);
    }

    //parsing the command and getting the options
    while((c=getopt(argc, argv, "c:l:w:")) != -1) {
        switch(c) {
            case 'c':
                fileName = optarg;
                myFile = openFile(fileName);
                bytes = countBytes(&myFile);
                closeFile(&myFile);
                printOutput(std::to_string(bytes), fileName);
                break;
            case 'l':
                fileName = optarg;
                myFile = openFile(fileName);
                lines = countLines(&myFile);
                closeFile(&myFile);
                printOutput(std::to_string(lines), fileName);
                break;
            case 'w':
                fileName = optarg;
                myFile = openFile(fileName);
                words = countWords(&myFile);
                closeFile(&myFile);
                printOutput(std::to_string(words), fileName);
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
        std::cerr << fileName << std::endl;
        std::cerr << "Error opening the file\n"; 
    }
    return myFile;
}

void closeFile(std::ifstream* myFile) {
    myFile->close();
}

void printOutput(std::string param, char* fileName) {
    std::cout << param << " " << fileName << std::endl;
}



std::streampos countBytes(std::ifstream* myFile) {
    // Move the file pointer to EOF
    myFile->seekg(0, std::ios::end);

    // Get the new current file pointer position, since we moved the pointer to EOF, this gives the total bytes
    std::streampos bytes = myFile->tellg();
    closeFile(myFile);
    return bytes;
}

int countLines(std::ifstream* myFile) {
    int lineCount = 0;
    std::string throwaway;
    
    // count lines, getline defaulted at delim \n
    while(std::getline(*myFile, throwaway)) { lineCount++; }
    closeFile(myFile);
    return lineCount;
}

int countWords(std::ifstream* myFile) {
    int wordCount = 0;
    std::string eachLine;
    std::string word;

    while(getline(*myFile, eachLine)) {
        std::stringstream lineStream(eachLine);

        while(lineStream >> word) {
            wordCount++;
        }
    }
    closeFile(myFile);
    return wordCount;
}