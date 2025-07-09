#include "UdsServices/Service10.h"

const Service10_Config_T service10Config = {
    .isFunctionalAddressSupported = false,
    .p2Timer = 50U,
    .p2MaxTimer = 5000U,
    .s3TimerProgrammingSession = 20000U,
    .s3TimerExtendedSession = 5000U,
    .preconditions = NULL,
    .customSessionsListSize = 0U,
    .customSessionsList = NULL,
};
