#include <iostream>
#include "Vehicle/BaseVehicle.h"
#include "Uds/Uds.h"
#include "Uds/Utility/Request.h"
#include "Uds/Utility/Response.h"

int main(){
  Uds uds(std::make_shared<BaseVehicle>());
  std::cout<<Request("3101").toString()<<std::endl;
  std::cout<<uds.execute(Request("1003")).toString()<<std::endl;
  return 0;
}
