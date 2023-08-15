#include "symbolTable.h"
#include <string>

SymbolTable::SymbolTable() :
        table({
                      {"SP",     "0"},
                      {"LCL",    "1"},
                      {"ARG",    "2"},
                      {"THIS",   "3"},
                      {"THAT",   "4"},
                      {"R0",     "0"},
                      {"R1",     "1"},
                      {"R2",     "2"},
                      {"R3",     "3"},
                      {"R4",     "4"},
                      {"R5",     "5"},
                      {"R6",     "6"},
                      {"R7",     "7"},
                      {"R8",     "8"},
                      {"R9",     "9"},
                      {"R10",    "10"},
                      {"R11",    "11"},
                      {"R12",    "12"},
                      {"R13",    "13"},
                      {"R14",    "14"},
                      {"R15",    "15"},
                      {"SCREEN", "16384"},
                      {"KBD",    "24576"}
              }) {


}

void SymbolTable::buildTable() {
    // first pass, create symbol table
    int count = 0;
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
        std::string llabel = "(";
        size_t llabelPos = currentLine.find(llabel);
        if (llabelPos != std::string::npos && llabelPos == 0) {
            std::string rlabel = ")";
            size_t rlabelPos = currentLine.find(rlabel);
            this->table[currentLine.substr(1, rlabelPos - 1)] = std::to_string(count);
            continue;
        }

        count++;
    }

    inf.clear();
    inf.seekg(0);
}

std::string SymbolTable::getAddr(const std::string &key) {
    return this->table[key];
}

void SymbolTable::setAddr(const std::string &key, const std::string &value) {
    this->table[key] = value;
}