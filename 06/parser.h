#pragma once
#include "code.h"
#include "symbolTable.h"

enum CommandType {
    A,
    C,
    Label,
    Unknown
};

class Parser {

public:
    Parser(const SymbolTable &);

    std::bitset<16> getCurrentMachineCode();

    std::string getComp();

    std::string getDest();

    std::string getJump();

    std::string getAddr();

    void setCurrentLine(const std::string &currentLine);


private:
    SymbolTable table;
    std::string comp;
    std::string dest;
    std::string jump;
    std::string addr;
    std::string currentLine;
    int16_t stackPointer;
    std::bitset<16> currentMachineCode;
    Code code;
    CommandType commandType;

    CommandType getCommandType();

    void parse();
};