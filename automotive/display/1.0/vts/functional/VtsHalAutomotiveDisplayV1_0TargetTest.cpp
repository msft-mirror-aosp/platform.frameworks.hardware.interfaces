//
// Copyright (C) 2020 The Android Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#define LOG_TAG "VtsHalAutomotiveDisplayTest"
#include <android-base/logging.h>

#include <android/frameworks/automotive/display/1.0/ICarWindowService.h>
#include <android/hardware/graphics/bufferqueue/2.0/IGraphicBufferProducer.h>
#include <utils/Log.h>

#include <gtest/gtest.h>
#include <hidl/GtestPrinter.h>
#include <hidl/ServiceManagement.h>

using namespace ::android::frameworks::automotive::display::V1_0;
using ::android::hardware::graphics::bufferqueue::V2_0::IGraphicBufferProducer;
using ::android::sp;

// The main test class for Automotive Display Service
class AutomotiveDisplayHidlTest : public ::testing::TestWithParam<std::string> {
public:
    virtual void SetUp() override {
        // Make sure we can connect to the service
        mCarWindowService = ICarWindowService::getService(GetParam());
        ASSERT_NE(mCarWindowService.get(), nullptr);
    }

    virtual void TearDown() override {}

    sp<ICarWindowService> mCarWindowService;    // Every test needs access to the service
};

TEST_P(AutomotiveDisplayHidlTest, getIGBP) {
    ALOGI("Test getIGraphicBufferProducer method");

    sp<IGraphicBufferProducer> igbp = mCarWindowService->getIGraphicBufferProducer();
    ASSERT_NE(igbp, nullptr);
}

TEST_P(AutomotiveDisplayHidlTest, showWindow) {
    ALOGI("Test showWindow method");

    ASSERT_EQ(mCarWindowService->showWindow(), true);
}

TEST_P(AutomotiveDisplayHidlTest, hideWindow) {
    ALOGI("Test hideWindow method");

    ASSERT_EQ(mCarWindowService->hideWindow(), true);
}

INSTANTIATE_TEST_SUITE_P(
    PerInstance,
    AutomotiveDisplayHidlTest,
    testing::ValuesIn(
        android::hardware::getAllHalInstanceNames(ICarWindowService::descriptor)
    ),
    android::hardware::PrintInstanceNameToString
);
