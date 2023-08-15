#pragma once

#include <iostream>
#include <fstream>
#include <unordered_map>

extern std::ifstream inf;

class SymbolTable {
public:
    SymbolTable();

    void buildTable();

    std::string getAddr(const std::string &);

    void setAddr(const std::string &, const std::string &);

private:
    std::unordered_map<std::string, std::string> table;
};