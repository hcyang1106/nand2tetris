#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "parser.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " [input_file] [output_file]" << std::endl;
        return 1;
    }

    std::ifstream inf{argv[1]};
    if (!inf) {
        std::cout << argv[1] << " could not be opened for reading!\n";
        return 1;
    }

    std::ofstream outf{argv[2]};
    if (!outf) {
        std::cout << argv[2] << " could not be opened for writing!\n";
        return 1;
    }

    std::string currentLine;
    while (!std::getline(inf, currentLine).eof()) {
        // empty line
        if (currentLine.compare("\r") == 0) {
            continue;
        }

        // comment line
        std::string doubleSlash = "//";
        size_t doubleSlashPos = currentLine.find(doubleSlash);
        if (doubleSlashPos == 0) {
            continue;
        }

        // remove \r
        currentLine.pop_back();
        Parser parser(currentLine);
//        std::cout << "comp: " <<  parser.getComp() << std::endl;
//        std::cout << "dest: " <<  parser.getDest() << std::endl;
//        std::cout << "jump: " <<  parser.getJump() << std::endl;
//        std::cout << "addr: " <<  parser.getAddr() << std::endl;
        outf << parser.getCurrentMachineCode() << std::endl;
    }
}