#pragma once

#include <memory>
#include <map>
#include "Uds/Services/BaseService.h"
#include "Uds/Utility/Request.h"
#include "Uds/Utility/Response.h"

class Uds{
public:
  enum Session{Default, Programming, Extended};
  Uds(std::shared_ptr<BaseVehicle> vehicle);
  void setVehicle(std::shared_ptr<BaseVehicle> vehicle);
  void registerService(std::shared_ptr<BaseService> service);
  void unRegisterService(std::shared_ptr<BaseService> service);
  void unRegisterService(int serviceId);
  inline Session getCurrentSession(){return this->session;}
  Response execute(Request command);
private:
  std::map<int, std::shared_ptr<BaseService> > services;
  Session session;
  std::shared_ptr<BaseVehicle> vehicle;
};
