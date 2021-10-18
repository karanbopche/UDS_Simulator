#include "Uds/Utility/Request.h"

Request::Request(std::string command){
  this->params = Convert::hexStringToVector(command.substr(2));
  this->requestId = Convert::hexStringToInt(command.substr(0,2));
}

Request::Request(const std::vector<uint8_t>& command) : requestId(command[0]), params(command.begin()+1, command.end()){
}

std::string Request::toString()
{
  return Convert::hexToString(requestId) + Convert::vectorToHexString(this->params);
}
