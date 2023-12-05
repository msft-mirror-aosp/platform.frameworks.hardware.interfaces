/*
 * Copyright (C) 2023 The Android Open Source Project
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

package android.frameworks.vibrator;

@VintfStability
@Backing(type="int")
enum VibrationTypeMask {
    ALARM = 1 << 0, // Alarm usage
    NOTIFICATION = 1 << 1, // Notification and communication request usages
    RINGTONE = 1 << 2, // Ringtone usage
    INTERACTIVE = 1 << 3, // Touch and hardware feedback usages
    MEDIA = 1 << 4 // Media and unknown usages
}