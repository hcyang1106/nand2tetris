#include "parser.h"
#include <string>
#include <bitset>

Parser::Parser(const std::string &currentLine) {
    this->currentLine = currentLine;
    this->commandType = Unknown;
}

std::bitset<16> Parser::getCurrentMachineCode() {
    this->parse();
    return this->currentMachineCode;
}

CommandType Parser::getCommandType() {
    if (this->commandType != Unknown) {
        return this->commandType;
    }

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
//        std::cout << "comp" << comp << std::endl;
//        std::cout << "dest" << dest << std::endl;
//        std::cout << "jump" << jump << std::endl;
        this->currentMachineCode = comp | dest | jump;
    }
}

std::string Parser::getAddr() {
    if (this->addr != "") {
        return this->addr;
    }

    std::string at = "@";
    size_t atPos = this->currentLine.find(at);
    if (atPos != std::string::npos) {
        this->addr = this->currentLine.substr(atPos + 1);
    }

    return this->addr;
}

std::string Parser::getComp() {
    if (this->comp != "") {
        return this->comp;
    }

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
    if (this->dest != "") {
        return this->dest;
    }

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
    if (this->jump != "") {
        return this->jump;
    }

    std::string semicolon = ";";
    size_t pos = this->currentLine.find(semicolon);
    if (pos == std::string::npos) {
        this->jump = "NONE";
    } else {
        this->jump = this->currentLine.substr(pos + 1);
    }

    return this->jump;
}