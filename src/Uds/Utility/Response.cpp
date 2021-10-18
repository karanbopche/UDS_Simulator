#include "Uds/Utility/Response.h"


Response::Response(std::string response){
  this->response = Convert::hexStringToVector(response);
}

Response Response::createNegative(int serviceNumber, NRC nrc){
  return Response("7F"+ Convert::hexToString(serviceNumber) + Convert::hexToString((uint8_t)nrc));
}

Response Response::createPositive(int serviceNumber, std::string params){
  return Response(Convert::hexToString(serviceNumber+0x40)+params);
}

Response Response::createPositive(int serviceNumber, std::vector<uint8_t> params){
  return Response(Convert::hexToString(serviceNumber+0x40) + Convert::vectorToHexString(params));
}


std::string Response::toString(){
  return Convert::vectorToHexString(this->response);
}
