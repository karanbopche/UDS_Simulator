#include "testFramework/testCase.h"
#include "Uds/Utility/Request.h"

bool test_Request(){
  assertCompare((int)0x31, (int)Request("3101").getServiceId());
  assertCompare("2E010C", Request("2E010C").toString());
  std::vector<uint8_t> params = {0x01, 0x02};
  assert(params, Request("2E0102").getParameter(), "checking parameters of request");
  return true;
}

void startTests(){
  TC_message("Testing Request Class");
  TC_run(test_Request);
}
