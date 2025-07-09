#include "UdsConfig.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(SERVICE_3E, tester_present) {
    uint8_t request[] = {0x3E, 0x00};
    clearlastResponse();
    Uds_Inject_Request(request, sizeof(request), false);
    ASSERT_THAT(getlastResponse(), ::testing::ElementsAre(0x7E, 0x00));
}

TEST(SERVICE_3E, tester_present_subfunction_not_supported) {
    uint8_t request[] = {0x3E, 0x01};
    clearlastResponse();
    Uds_Inject_Request(request, sizeof(request), false);
    ASSERT_THAT(getlastResponse(), ::testing::ElementsAre(0x7F, 0x3E, NRC_SUBFUNCTION_NOT_SUPPORTED));
}

TEST(SERVICE_3E, tester_present_invalid_length) {
    uint8_t request[] = {0x3E, 0x00, 0x00};
    clearlastResponse();
    Uds_Inject_Request(request, sizeof(request), false);
    ASSERT_THAT(getlastResponse(), ::testing::ElementsAre(0x7F, 0x3E, NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT));
}
