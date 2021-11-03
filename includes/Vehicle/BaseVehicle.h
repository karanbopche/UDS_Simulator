#pragma once

class BaseVehicle{
public:
  struct WheelSpeed{int FL, FR, RL, RR;};
  BaseVehicle();
  void setWheelSpeed(int wheelSpeed){this->wheelSpeed = {wheelSpeed,wheelSpeed,wheelSpeed,wheelSpeed};}
  void setWheelSpeed(WheelSpeed wheelSpeed){this->wheelSpeed = wheelSpeed;}
  inline float getRefSpeed() { return (this->wheelSpeed.FL + this->wheelSpeed.FR + this->wheelSpeed.RL + this->wheelSpeed.RR)/4;}
  inline WheelSpeed getSpeed(){ return this->wheelSpeed;}

  inline void PowerOn(){this->kL30 = this->ign = true;}
  inline void PowerOff(){this->kL30 = this->ign = false;}
  inline bool getIgnStatus(){return this->ign;}
  inline bool getKL30Status(){return this->kL30;}
  inline bool isOn(){return this->kL30;}

  
  
private:
  bool ign, kL30;
  WheelSpeed wheelSpeed;
};
