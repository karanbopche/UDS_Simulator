#pragma once

#include <vector>
#include <string>
#include "Uds/Utility/Convert.h"

class Request
{
public:
  Request(std::string command);
  Request(const std::vector<uint8_t>& command);
  inline uint8_t getServiceId(){return this->requestId;}
  inline std::vector<uint8_t>& getParameter(){return this->params;}
  std::string toString();
  inline uint8_t& operator[] (int index){return this->params[index];}
  inline size_t paramLength(){return this->params.size();}

private:
  inline std::vector<uint8_t> hexStringToVector(std::string data);
  inline int hexStringToInt(std::string data);
  uint8_t requestId;
  std::vector<uint8_t> params;
};
 