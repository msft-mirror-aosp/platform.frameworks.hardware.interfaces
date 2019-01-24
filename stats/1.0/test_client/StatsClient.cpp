/*
 * Copyright (C) 2019 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <android/frameworks/stats/1.0/IStats.h>

#include <statslog.h>
#include <utils/StrongPointer.h>

#include <getopt.h>
#include <iostream>

using android::frameworks::stats::V1_0::BatteryCausedShutdown;
using android::frameworks::stats::V1_0::BatteryHealthSnapshotArgs;
using android::frameworks::stats::V1_0::ChargeCycles;
using android::frameworks::stats::V1_0::HardwareFailed;
using android::frameworks::stats::V1_0::IStats;
using android::frameworks::stats::V1_0::SlowIo;
using android::frameworks::stats::V1_0::SpeakerImpedance;
using android::frameworks::stats::V1_0::UsbPortOverheatEvent;

void expect_message(int32_t action) {
    std::cout << "expect the following log in logcat:\n";
    std::cout << "statsd.*(" << action << ")0x10000->\n";
}

void show_help() {
    std::cout << "Stats HAL client\n";
    std::cout << " arguments:\n";
    std::cout << " -S or --SpeakerImpedance\n";
    std::cout << " -f or --HardwareFailed\n";
    std::cout << " -y or --ChargeCycles\n";
    std::cout << " -n or --BatteryHealthSnapshot\n";
    std::cout << " -i or --SlowIo\n";
    std::cout << " -s or --BatteryCausedShutdown\n";
    std::cout << " -u or --UsbPortOverheatEvent\n";
    std::cout << "Please enable statsd logging using 'cmd stats print-logs'";
    std::cout << "\n\n you can use multiple arguments to trigger multiple events.\n";
}

int main(int argc, char* argv[]) {
    android::sp<IStats> client = IStats::tryGetService();
    if (!client) {
        std::cerr << "No Stats HAL";
        return 1;
    }

    static struct option opts[] = {
        {"SpeakerImpedance", no_argument, 0, 'S'},
        {"HardwareFailed", no_argument, 0, 'f'},
        {"ChargeCycles", no_argument, 0, 'y'},
        {"BatteryHealthSnapshot", no_argument, 0, 'n'},
        {"SlowIo", no_argument, 0, 'i'},
        {"BatteryCausedShutdown", no_argument, 0, 's'},
        {"UsbPortOverheatEvent", no_argument, 0, 'u'},
    };

    int c;
    int hal_calls = 0;
    while ((c = getopt_long(argc, argv, "Sfynisu", opts, nullptr)) != -1) {
        switch (c) {
            case 'S': {
                SpeakerImpedance left_obj = {.speakerLocation = 0,
                                             .milliOhms = static_cast<int32_t>(1234 * 1000)};
                client->reportSpeakerImpedance(left_obj);
                expect_message(android::util::SPEAKER_IMPEDANCE_REPORTED);
                ++hal_calls;
                break;
            }
            case 'f': {
                HardwareFailed failed = {.hardwareType = HardwareFailed::HardwareType::CODEC,
                                         .hardwareLocation = 0,
                                         .errorCode = HardwareFailed::HardwareErrorCode::COMPLETE};
                client->reportHardwareFailed(failed);
                expect_message(android::util::HARDWARE_FAILED);
                ++hal_calls;
                break;
            }
            case 'y': {
                std::vector<int> charge_cycles = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
                ChargeCycles cycles;
                cycles.cycleBucket = charge_cycles;
                client->reportChargeCycles(cycles);
                expect_message(android::util::CHARGE_CYCLES_REPORTED);
                ++hal_calls;
                break;
            }
            case 'n': {
                BatteryHealthSnapshotArgs args{.temperatureDeciC = 3000,
                                               .voltageMicroV = 1,
                                               .currentMicroA = 2,
                                               .openCircuitVoltageMicroV = 3,
                                               .resistanceMicroOhm = 5,
                                               .levelPercent = 101};
                client->reportBatteryHealthSnapshot(args);
                expect_message(android::util::BATTERY_HEALTH_SNAPSHOT);
                ++hal_calls;
                break;
            }
            case 'i': {
                SlowIo slowio = {.operation = SlowIo::IoOperation::READ, .count = 5};
                client->reportSlowIo(slowio);
                expect_message(android::util::SLOW_IO);
                ++hal_calls;
                break;
            }
            case 's': {
                BatteryCausedShutdown shutdown = {.voltageMicroV = 3};
                client->reportBatteryCausedShutdown(shutdown);
                expect_message(android::util::BATTERY_CAUSED_SHUTDOWN);
                ++hal_calls;
                break;
            }
            case 'u': {
                UsbPortOverheatEvent event = {.maxTemperatureDeciC = 220,
                                              .plugTemperatureDeciC = 210,
                                              .timeToOverheat = 1,
                                              .timeToHysteresis = 2,
                                              .timeToInactive = 3};
                client->reportUsbPortOverheatEvent(event);
                expect_message(android::util::USB_PORT_OVERHEAT_EVENT_REPORTED);
                ++hal_calls;
                break;
            }
        }
    }

    if (hal_calls == 0) {
        show_help();
    } else {
        std::cout << hal_calls << " HAL methods called.\n";
        std::cout << "try: logcat | grep \"statsd.*0x1000\"\n";
    }
    return 0;
}