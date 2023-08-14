#include "code.h"

enum CommandType {
    A,
    C,
    Label,
    Unknown
};

class Parser {

public:
    Parser(const std::string &);

    std::bitset<16> getCurrentMachineCode();

    std::string getComp();

    std::string getDest();

    std::string getJump();

    std::string getAddr();


private:
    std::string comp;
    std::string dest;
    std::string jump;
    std::string addr;
    std::string currentLine;
    std::bitset<16> currentMachineCode;
    Code code;
    CommandType commandType;

    CommandType getCommandType();

    void parse();
};