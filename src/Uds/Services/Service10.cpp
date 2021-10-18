#include "Uds/Services/Service10.h"

Service10::Service10(): BaseService(0x10){

}

Response Service10::execute(Request command){
  bool result = true;

  if(result) Response::createPositive(this->serviceId, "");
  return Response::createNegative(this->serviceId, Response::NRC::generalReject);
}
