#include "parser.h"
#include <string>
#include <bitset>
#include <cctype>

Parser::Parser(const SymbolTable &table) : table(table), stackPointer(16),
                                           commandType(Unknown) {
}

void Parser::setCurrentLine(const std::string &currentLine) {
    this->currentLine = currentLine;
}

std::bitset<16> Parser::getCurrentMachineCode() {
    this->parse();
    return this->currentMachineCode;
}

CommandType Parser::getCommandType() {
    std::string at = "@";
    size_t atPos = this->currentLine.find(at);
    if (atPos != std::string::npos) {
        this->commandType = A;
        return A;
    }

    this->commandType = C;
    return C;
}

void Parser::parse() {
    CommandType type = this->getCommandType();
    if (type == A) {
        this->currentMachineCode = std::bitset<16>(std::stoi(this->getAddr()));
    } else if (type == C) {
        std::bitset<16> comp = (this->code).getComp(this->getComp());
        std::bitset<16> dest = (this->code).getDest(this->getDest());
        std::bitset<16> jump = (this->code).getJump(this->getJump());
        this->currentMachineCode = comp | dest | jump;
    }
}

std::string Parser::getAddr() {
    std::string at = "@";
    size_t atPos = this->currentLine.find(at);

    this->addr = this->currentLine.substr(atPos + 1);

    if (!std::isdigit(this->addr.front())) {
        this->addr = this->table.getAddr(this->addr);
    }

    if (this->addr == "") {
        this->addr = std::to_string(this->stackPointer);
        this->table.setAddr(this->currentLine.substr(atPos + 1), this->addr);
        this->stackPointer++;
    }

    return this->addr;
}

std::string Parser::getComp() {
    std::string equal = "=";
    size_t equalPos = this->currentLine.find(equal);
    if (equalPos != std::string::npos) {
        this->comp = this->currentLine.substr(equalPos + 1);
    }

    std::string semicolon = ";";
    size_t pos = this->currentLine.find(semicolon);
    if (pos != std::string::npos) {
        this->comp = this->currentLine.substr(0, pos);
    }

    return this->comp;
}

std::string Parser::getDest() {
    std::string equal = "=";
    size_t equalPos = this->currentLine.find(equal);
    if (equalPos == std::string::npos) {
        this->dest = "NONE";
    } else {
        this->dest = this->currentLine.substr(0, equalPos);
    }

    return this->dest;
}

std::string Parser::getJump() {
    std::string semicolon = ";";
    size_t pos = this->currentLine.find(semicolon);
    if (pos == std::string::npos) {
        this->jump = "NONE";
    } else {
        this->jump = this->currentLine.substr(pos + 1);
    }

    return this->jump;
}