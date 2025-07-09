#include "UdsConfig.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(SERVICE_22, read_DID_F188) {
    uint8_t request[] = {0x22, 0xF1, 0x88};
    clearlastResponse();
    Uds_Inject_Request(request, sizeof(request), false);
    ASSERT_THAT(getlastResponse(), ::testing::ElementsAre(0x62, 0xF1, 0x88, 0x88, 0x88, 0x88, 0x88));
}

TEST(SERVICE_22, read_DID_functional_address) {
    uint8_t request[] = {0x22, 0xF1, 0x88};
    clearlastResponse();
    Uds_Inject_Request(request, sizeof(request), true);
    ASSERT_THAT(getlastResponse(), ::testing::ElementsAre(0x62, 0xF1, 0x88, 0x88, 0x88, 0x88, 0x88));
}

TEST(SERVICE_22, read_multiple_DIDs) {
    uint8_t request[] = {0x22, 0xF1, 0x88, 0xF1, 0x99};
    clearlastResponse();
    Uds_Inject_Request(request, sizeof(request), true);
    ASSERT_THAT(getlastResponse(),
                ::testing::ElementsAre(0x62, 0xF1, 0x88, 0x88, 0x88, 0x88, 0x88, 0xF1, 0x99, 0x99, 0x99, 0x99, 0x99));
}

TEST(SERVICE_22, read_multiple_DIDs_with_one_invalid_DID) {
    uint8_t request[] = {0x22, 0xF1, 0x88, 0xF1, 0x22};
    clearlastResponse();
    Uds_Inject_Request(request, sizeof(request), true);
    ASSERT_THAT(getlastResponse(), ::testing::ElementsAre(0x62, 0xF1, 0x88, 0x88, 0x88, 0x88, 0x88));
}

TEST(SERVICE_22, read_multiple_DIDs_with_all_invalid_DID) {
    uint8_t request[] = {0x22, 0xF1, 0x91, 0xF1, 0x22};
    clearlastResponse();
    Uds_Inject_Request(request, sizeof(request), true);
    ASSERT_THAT(getlastResponse(), ::testing::ElementsAre(0x7F, 0x22, NRC_REQUEST_OUT_OF_RANGE));
}
