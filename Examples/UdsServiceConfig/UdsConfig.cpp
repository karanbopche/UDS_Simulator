#include "UdsConfig.h"

extern "C" const Service10_Config_T service10Config;
extern "C" const Service11_Config_T service11Config;
extern "C" const Service22_Config_T service22Config;
extern "C" const Service27_Config_T service27Config;
extern "C" const Service28_Config_T service28Config;
extern "C" const Service2E_Config_T service2EConfig;
extern "C" const Service3E_Config_T service3EConfig;
extern "C" const Service31_Config_T service31Config;
extern "C" const Service34_Config_T service34Config;
extern "C" const Service36_Config_T service36Config;
extern "C" const Service37_Config_T service37Config;
extern "C" const Service85_Config_T service85Config;

static uint16_t Uds_Receive_Wrapper(uint8_t *const data);
static void Uds_Send_Wrapper(uint8_t const *const data, const uint16_t length);

extern "C" {
const Uds_Config_T Uds_Gateway_Configurations = {
    .send = Uds_Send_Wrapper,
    .receive = Uds_Receive_Wrapper,
    .services =
        {
            .service10 = &service10Config,
            .service11 = &service11Config,
            .service22 = &service22Config,
            .service27 = &service27Config,
            .service28 = &service28Config,
            .service2E = &service2EConfig,
            .service3E = &service3EConfig,
            .service31 = &service31Config,
            .service34 = &service34Config,
            .service36 = &service36Config,
            .service37 = &service37Config,
            .service85 = &service85Config,
        },
};
}
static std::vector<uint8_t> lastResponse;

static void Uds_Send_Wrapper(uint8_t const *const data, const uint16_t length) {
    lastResponse = std::vector<uint8_t>(data, data + length);
}

static uint16_t Uds_Receive_Wrapper(uint8_t *const data) {
    uint16_t receivedBytes = 0;
    return receivedBytes;
}

std::vector<uint8_t> &getlastResponse() { return lastResponse; }

void clearlastResponse() { lastResponse.clear(); }
