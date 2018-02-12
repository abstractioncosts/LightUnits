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

// TODO: Clarify definition here. Make sure that used type is one from the IntegralValueSystem
// Do not use "using Prefix="

struct AmpereMicroIntegral
{
    static LightUnits::Prefix const BasePrefix = LightUnits::Prefix::Micro;
    typedef std::int32_t ValueType;
};

typedef LightUnits::BaseUnit<LightUnits::Ampere_t, AmpereMicroIntegral> Ampere;

using Prefix = LightUnits::Prefix;

constexpr Ampere operator"" _uA(unsigned long long uA)
{
    auto val = static_cast<Ampere::ValueType>(uA);
    return Ampere::From<Prefix::Micro>(val);
}

constexpr Ampere operator"" _mA(unsigned long long mA)
{
    auto val = static_cast<Ampere::ValueType>(mA);
    return Ampere::From<Prefix::Milli>(val);
}

constexpr Ampere operator"" _A(unsigned long long A)
{
    auto val = static_cast<Ampere::ValueType>(A);
    return Ampere::From<Prefix::One>(val);
}
