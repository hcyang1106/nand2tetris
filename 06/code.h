#include <string>
#include <unordered_map>
#include <cassert>
#include <iostream>

class Code {

public:
    Code();

    uint16_t getComp(const std::string &);

    uint8_t getDest(const std::string &);

    uint8_t getJump(const std::string &);

private:
    std::unordered_map <std::string, uint16_t> comp;
    std::unordered_map <std::string, uint8_t> dest;
    std::unordered_map <std::string, uint8_t> jump;
};