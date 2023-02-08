//
// Copyright (C) 2023 The Android Open Source Project
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
package android.frameworks.stats;

/*
 * Mimics packages/modules/StatsD/lib/libstatssocket/include/stats_annotations.h
 * These ids must stay consistent with those in stats_annotations.h
 */
@VintfStability
@Backing(type="int")
enum AnnotationId {
    UNKNOWN = 0,
    /**
     * Annotation ID constant for logging UID field.
     */
    IS_UID = 1,

    /**
     * Annotation ID constant to indicate logged atom event's timestamp should be truncated.
     */
    TRUNCATE_TIMESTAMP = 2,

    /**
     * Annotation ID constant for a state atom's primary field.
     */
    PRIMARY_FIELD = 3,

    /**
     * Annotation ID constant for state atom's state field.
     */
    EXCLUSIVE_STATE = 4,

    /**
     * Annotation ID constant to indicate the first UID in the attribution chain
     * is a primary field.
     */
    PRIMARY_FIELD_FIRST_UID = 5,

    /**
     * Annotation ID constant to indicate which state is default for the state atom.
     */
    DEFAULT_STATE = 6,

    /**
     * Annotation ID constant to signal that all states should be reset to the default state.
     */
    TRIGGER_STATE_RESET = 7,

    /**
     * Annotation ID constant to indicate state changes need to account for nesting.
     * This should only be used with binary state atoms.
     */
    STATE_NESTED = 8,
}
