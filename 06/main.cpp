#include <iostream>
#include <string>
#include "parser.h"
#include "symbolTable.h"

std::ifstream inf;
std::ofstream outf;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " [input_file] [output_file]" << std::endl;
        return 1;
    }

    inf.open(argv[1]);
    if (!inf) {
        std::cout << argv[1] << " could not be opened for reading!\n";
        return 1;
    }

    outf.open(argv[2]);
    if (!outf) {
        std::cout << argv[2] << " could not be opened for writing!\n";
        return 1;
    }

    // setup symbol table
    SymbolTable table;
    table.buildTable();

    Parser parser(table);
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

        // label line
        std::string label = "(";
        size_t labelPos = currentLine.find(label);
        if (labelPos == 0) {
            continue;
        }

        // remove comment behind
        if (doubleSlashPos != std::string::npos && doubleSlashPos != 0) {
            currentLine = currentLine.substr(0, doubleSlashPos);
        }

        // remove spaces
        const std::string whitespace = " \n\r\t\f\v";
        size_t start = currentLine.find_first_not_of(whitespace);
        currentLine = currentLine.substr(start);

        size_t end = currentLine.find_last_not_of(whitespace);
        currentLine = currentLine.substr(0, end + 1);

        parser.setCurrentLine(currentLine);
        outf << parser.getCurrentMachineCode() << std::endl;
    }
}