/*  Copyright 2018 Daniel Penning
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#pragma once

#include <LightUnits/ValueSystem.hpp>
#include <cstdint>
#include <limits>

// int statt int32_t verwenden, da int32_t beispielsweise bei ARM Cortex Targets intern typedef auf long int hat (beides 32-bit)
// long int hat aber andere Promotion Regeln, so dass man Integer im Zusammenhang mit den Units
// bei int32_t immer mit long-Suffix (1l statt 1 etc) benutzen muss, oder es zu einem ambiguous-error kommt
//
using IntegralValueSystem = LightUnits::ValueSystem<std::int8_t, std::int16_t, int, std::int64_t>;

static_assert(sizeof(int) == sizeof(std::int32_t), "int is supposed to be a 4-byte type");
static_assert(std::numeric_limits<int>::max() == std::numeric_limits<std::int32_t>::max(), "int is supposed to be identical to int32_t in range");
static_assert(std::numeric_limits<int>::min() == std::numeric_limits<std::int32_t>::min(), "int is supposed to be identical to int32_t in range");
