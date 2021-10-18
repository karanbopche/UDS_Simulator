#include "Uds/Uds.h"

Uds::Uds(std::shared_ptr<BaseVehicle> vehicle) {
  this->vehicle = vehicle;
}

void Uds::registerService(std::shared_ptr<BaseService> service){
  this->services[service->getServiceId()] = service;
  service->setVehicle(this->vehicle);
  service->setUds(this);
}

void Uds::unRegisterService(int serviceId){
  this->services.erase(serviceId);
}

void Uds::unRegisterService(std::shared_ptr<BaseService> service){
  this->services.erase(service->getServiceId());
}

Response Uds::execute(Request command){
  if(services.find(command.getServiceId()) != services.end()){
    return services[command.getServiceId()]->execute(command);
  }
  return Response::createNegative(command.getServiceId(), Response::NRC::serviceNotSupported);
}
