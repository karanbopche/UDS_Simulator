#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <exception>


void startTests();
typedef bool(*TestFunction)(void);
void TC_run(TestFunction testFunction, const char* msg="");
void TC_message(const char*);

template<class T, class C>
void assertCompare(T expected, C measured, const char* msg=""){
  if(expected == measured){
    std::cout<<"assertion PASSED: "<<msg<<" expected:"<<expected<<" measured:"<<measured<<"\n\n";
  }
  else{
    std::stringstream out;
    out<<"assertion FAILED: "<<msg<<" expected:"<<expected<<" measured:"<<measured<<"\n\n";
    throw std::runtime_error(out.str());
  }
}

template<class T, class C>
void assert(T expected, C measured, const char* msg=""){
  if(expected == measured){
    std::cout<<"assertion PASSED: "<<msg<<"\n\n";
  }
  else{
    std::stringstream out;
    out<<msg<<"assertion FAILED: "<<msg<<"\n\n";
    throw std::runtime_error(out.str());
  }
}

#define assertException(exceptiontype, expression) { \
  try {\
    expression;\
  }\
  catch(exceptiontype ex){\
    std::cout<<"assertion PASSED: exception "<<##exceptiontype<<" raised\n\n";\
  }\
  catch(...){\
    std::stringstream out;\
    out<<"assertion FAILED: "<<msg<<" expected:"<<expected<<" measured:"<<measured<<"\n\n";\
    throw std::runtime_error(out.str());\
  }\
}
