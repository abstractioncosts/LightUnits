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

struct OhmMilliIntegral 
{
    static LightUnits::Prefix const BasePrefix = LightUnits::Prefix::Milli;
    typedef std::int32_t ValueType;
};

typedef LightUnits::BaseUnit<LightUnits::Ohm_t, OhmMilliIntegral> Ohm;

constexpr Ohm operator"" _mOhm(unsigned long long mOhm)
{
    auto val = static_cast<Ohm::ValueType>(mOhm);
    return Ohm::From<Prefix::Milli>(val);
}

constexpr Ohm operator"" _Ohm(unsigned long long ohm)
{
    auto val = static_cast<Ohm::ValueType>(ohm);
    return Ohm::From<Prefix::One>(val);
}

constexpr Ohm operator"" _kOhm(unsigned long long kOhm)
{
    auto val = static_cast<Ohm::ValueType>(kOhm);
    return Ohm::From<Prefix::Kilo>(val);
}
