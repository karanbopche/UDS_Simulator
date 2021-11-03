#include "Uds/Utility/Response.h"

Response::Response(std::string response){
  this->response = Convert::hexStringToVector(response);
}

Response Response::createNegative(int serviceNumber, NRC nrc){
  Response res("");
  res.response.push_back(0x7F);
  res.response.push_back(serviceNumber);
  res.response.push_back(static_cast<uint8_t>(nrc));
  return res;
}

Response Response::createPositive(int serviceNumber, std::string params){
  Response res;
  res.response.push_back(serviceNumber);
  auto data = Convert::hexStringToVector(params);
  res.response.insert(res.response.end(), data.begin(), data.end());
  return Response(Convert::hexToString(serviceNumber+0x40)+params);
}

Response Response::createPositive(int serviceNumber, const std::vector<uint8_t>& params){
  Response res;
  res.response.push_back(serviceNumber+0x40);
  res.response.insert(res.response.end(), params.begin(), params.end());
  return res;
}
