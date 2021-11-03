#include "Uds/Services/Service10.h"

Service10::Service10(): BaseService(0x10){

}

Response Service10::execute(Request command){
  bool result = true;
  if (command.paramLength() != 1) 
    return Response::createNegative(this->serviceId, Response::NRC::incorrectMessageLengthOrInvalidFormat);
  if(command[1] > 3)
    return Response::createNegative(this->serviceId,Response::NRC::requestOutOfRange);
  if(vehicle->getRefSpeed() >= this->speedLimit)
    return Response::createNegative(this->serviceId, Response::NRC::conditionsNotCorrect);

  if(result) return Response::createPositive(this->serviceId, (std::vector<uint8_t>){command[0]});
  return Response::createNegative(this->serviceId, Response::NRC::generalReject);
}
