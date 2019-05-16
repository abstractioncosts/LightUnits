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

// Use int instead of int32_t, because int32_t is sometimes (e.g. arm gcc for cortex-m targets) type-deffed to long int
// long int is also 32-bit on these platforms, but causes different C++ integer promotion rules to apply
// E.g. for int32_t, you always need to use the long-suffix (1l instead of 1) to prevent an "ambiguous-error" when using this library
//
using IntegralValueSystem = LightUnits::ValueSystem<std::int8_t, std::int16_t, int, std::int64_t>;

static_assert(sizeof(int) == sizeof(std::int32_t), "int is supposed to be a 4-byte type");
static_assert(std::numeric_limits<int>::max() == std::numeric_limits<std::int32_t>::max(), "int is supposed to be identical to int32_t in range");
static_assert(std::numeric_limits<int>::min() == std::numeric_limits<std::int32_t>::min(), "int is supposed to be identical to int32_t in range");
