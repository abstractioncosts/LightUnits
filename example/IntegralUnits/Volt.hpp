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

#include <cstdint>
#include <LightUnits/TypeTags.hpp>
#include <LightUnits/BaseUnit.hpp>

struct VoltMilliIntegral 
{
    static LightUnits::Prefix const BasePrefix = LightUnits::Prefix::Milli;
    typedef std::int32_t ValueType;
};

typedef LightUnits::BaseUnit<LightUnits::Volt_t, VoltMilliIntegral> Volt;

constexpr Volt operator"" _mV(unsigned long long mV)
{
    auto val = static_cast<Volt::ValueType>(mV);
    return Volt::From<Prefix::Milli>(val);
}

constexpr Volt operator"" _V(unsigned long long V)
{
    auto val = static_cast<Volt::ValueType>(V);
    return Volt::From<Prefix::One>(val);
}
