#include "testFramework/testCase.h"
#include "Vehicle/BaseVehicle.h"
#include "Uds/Services/Service10.h"
#include "Uds/Uds.h"

bool test_uds(){
  Uds uds(std::make_shared<BaseVehicle>());
  assertCompare("7F1011", uds.execute(Request("1003")).toString());
  uds.registerService(std::make_shared<Service10>());
  assertCompare("5003", uds.execute(Request("1003")).toString());
  

  return true;

}

void startTests(){
  TC_message("Testing UDS class");
  TC_run(test_uds);
}
