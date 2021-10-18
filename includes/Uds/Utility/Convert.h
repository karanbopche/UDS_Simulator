#pragma once

#include <string>
#include <vector>

class Convert{
public:
  static std::string hexToString(uint8_t value);
  static std::string vectorToHexString(std::vector<uint8_t>& value);
  static inline uint8_t hexStringToInt(const std::string& data){return stoi(data, 0, 16);}
  static std::vector<uint8_t> hexStringToVector(const std::string&);
};
