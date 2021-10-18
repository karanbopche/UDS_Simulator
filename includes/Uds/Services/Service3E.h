#pragma once

#include <memory>
#include "Uds/Services/BaseService.h"
#include "Vehicle/BaseVehicle.h"
#include "Uds/Utility/Response.h"
#include "Uds/Utility/Request.h"

class Service3E : public BaseService
{
public:
  Service3E();
  Response execute(Request command);
};
