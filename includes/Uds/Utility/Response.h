#pragma once

#include <string>
#include "Uds/Utility/Convert.h"

class Response
{
public:
  enum NRC{
    generalReject=0x10,
    serviceNotSupported=0x11,
    subFunctionNotSupported=0x12,
    incorrectMessageLengthOrInvalidFormat=0x13,
    responseTooLong=0x14,
    busyRepeatReques=0x21,
    conditionsNotCorrect=0x22,
    requestSequenceError=0x24,
    requestOutOfRange=0x31,
    securityAccessDenied=0x33,
    invalidKey=0x35,
    exceedNumberOfAttempts=0x36,
    requiredTimeDelayNotExpired=0x37,
    uploadDownloadNotAccepted=0x70,
    transferDataSuspended=0x71,
    generalProgrammingFailure=0x72,
    wrongBlockSequenceCounter=0x73,
    requestCorrectlyReceivedResponsePending=0x78,
    subFunctionNotSupportedInActiveSession=0x7E,
    serviceNotSupportedInActiveSession=0x7F,
    rpmTooHigh=0x81,
    rpmTooLow=0x82,
    engineIsRunning=0x83,
    engineIsNotRunning=0x84,
    engineRunTimeTooLow=0x85,
    temperatureTooHigh=0x86,
    temperatureTooLow=0x87,
    vehicleSpeedTooHigh=0x88,
    vehicleSpeedTooLow=0x89,
    throttlePedalTooHigh=0x8A,
    throttlePedalTooLow=0x8B,
    transmissionRangeNotInNeutral=0x8C,
    transmissionRangeNotInGear=0x8D,
    brakeSwitchNotClosed=0x8F,
    shifterLeverNotInPark=0x90,
    torqueConverterClutchLocked=0x91,
    voltageTooHigh=0x92,
    voltageTooLow=0x93,
  };
  explicit Response(std::string response);
  static Response createNegative(int serviceNumber, NRC nrc);
  static Response createPositive(int serviceNumber, std::string params="");
  static Response createPositive(int serviceNumber, std::vector<uint8_t> params);
  std::string toString();
  inline bool isPositive(){return this->response[0]!=0x7F;}
protected:
  std::vector<uint8_t> response;
};
