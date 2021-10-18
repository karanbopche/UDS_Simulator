#include <iostream>
#include "Uds/Uds.h"
#include "Uds/Services/Service10.h"
#include "Uds/Services/Service3E.h"

int main(){
  std::string command;
  std::shared_ptr<BaseVehicle> vehicle = std::make_shared<BaseVehicle>();
  Uds uds(vehicle);
  uds.registerService(std::make_shared<Service10>());
  uds.registerService(std::make_shared<Service3E>());

  std::cout<<"Welcome to Uds Simulator."<<std::endl;
  while(1){
    std::cout<<"Enter Command to execute: 0x";
    std::cin>>command;
    if(command == "exit") break;
    std::cout<<"response from UDS       : 0x"<<uds.execute(Request(command)).toString()<<std::endl;
  }
}
