#pragma once

class BaseVehicle{
public:
  struct WheelSpeed{int FL, FR, RL, RR;};
  BaseVehicle();
  void setWheelSpeed(WheelSpeed wheelSpeed){this->wheelSpeed = wheelSpeed;}
  inline float getRefSpeed() { return (this->wheelSpeed.FL + this->wheelSpeed.FR + this->wheelSpeed.RL + this->wheelSpeed.RR)/4;}
  inline WheelSpeed getSpeed(){ return this->wheelSpeed;}

private:
  WheelSpeed wheelSpeed;
};
