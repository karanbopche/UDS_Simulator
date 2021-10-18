#pragma once

#include <string>
#include <memory>
#include "Vehicle/BaseVehicle.h"
#include "Uds/Utility/Response.h"
#include "Uds/Utility/Request.h"

class Uds;

class BaseService{
public:
  BaseService(int serviceId);
  void setVehicle(std::shared_ptr<BaseVehicle> vehicle){this->vehicle = vehicle;}
  void setUds(const Uds* uds) {this->uds = uds;}
  virtual Response execute(Request command) = 0;
  inline int getServiceId(){return this->serviceId;}

protected:
  const int serviceId;
  const Uds* uds;
  std::shared_ptr<BaseVehicle> vehicle;
};
