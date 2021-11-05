
#include "testCase.h"

extern void startTests();

void TC_run(TestFunction testFunction, const char* msg){
  static const char* resultString[] = {"FAILED", "PASSED"};
  bool result = false;
  std::cout<<std::endl;
  std::cout<<"Starting Test: "<<msg<<std::endl;
  try{
    if(testFunction)
      result = testFunction();
  }
  catch(std::exception& ex){
    std::cout<<"exception: "<<ex.what()<<std::endl;
  }
  std::cout<<"Test case Result: "<<resultString[(int)result]<<std::endl;
  std::cout<<std::endl;
}


int main(){
  startTests();
  return 0;
}

void TC_message(const char* msg){
  std::cout<<"TC_message: "<<msg<<std::endl;
}
