#include "Uds/Utility/Convert.h"
#include "testFramework/testCase.h"

bool test_Convert(){
  assertCompare(std::string("33"), Convert::hexToString(0x33));
  assertCompare((uint8_t)0x33, Convert::hexStringToInt("33"));

  std::vector<uint8_t> data = {0x33, 0x22, 0x11};
  assertCompare(std::string("332211"), Convert::vectorToHexString(data));
  assert(data, Convert::hexStringToVector("332211"), "testing hexStringToDeque");
  return true;
}

void startTests(){
  TC_message("testing Convert Class.");
  TC_run(test_Convert);
}
