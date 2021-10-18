#pragma once
#include "Uds/Services/BaseService.h"

class Service10: public BaseService
{
public:

  Service10();
  Response execute(Request command);
protected:
  struct ParamFormat{
    uint8_t requestedSession;
  };
private:
  const float speedLimit = 10.0; // in kmph
  const int parameterLength = 1;
};
