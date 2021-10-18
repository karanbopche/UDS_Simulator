#include "testCase.h"
#include "Uds/Utility/Response.h"

bool test_response(){
  assertCompare("2E0102", Response("2E0102").toString());
  assertCompare("6E0102", Response::createPositive(0x2E, "0102").toString());
  assertCompare("7F2E31", Response::createNegative(0x2E, Response::NRC::requestOutOfRange).toString());
  assertCompare(false, Response::createNegative(0x31, Response::NRC::requestOutOfRange).isPositive());
  return true;
}

void startTests(){
  TC_message("Testing Response Class");
  TC_run(test_response);
}
