#include "Uds/Utility/Convert.h"

std::string Convert::hexToString(uint8_t value){
  char buffer[3];
  static const char* characters = "0123456789ABCDEF";
  buffer[2] = 0;
  buffer[1] = characters[value%16];
  buffer[0] = characters[value/16];
  return buffer;
}

std::string Convert::vectorToHexString(std::vector<uint8_t>& param){
  std::string result;
  for(int value: param){
    result += hexToString(value);
  }
  return result;
}

std::vector<uint8_t> Convert::hexStringToVector(const std::string& str){
  std::vector<uint8_t> vect;
  size_t length = str.length()/2;
  for(size_t i=0;i<length;i++){
    uint8_t value = hexStringToInt(str.substr(i*2, 2));
    vect.push_back(value);
  }
  return vect;
}
