#include "Uds/Services/Service3E.h"

Service3E::Service3E(): BaseService(0x3E) {}

Response Service3E::execute(Request command){
  return Response::createNegative(this->serviceId, Response::NRC::generalReject);
}
