#ifndef UDS_CONFIG_H
#define UDS_CONFIG_H

#include "UdsGateway.h"
#include <vector>

std::vector<uint8_t> &getlastResponse();
void clearlastResponse();

#endif // UDS_CONFIG_H
