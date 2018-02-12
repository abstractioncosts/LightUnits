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

#include "IntegralValueSystem.hpp"
#include <LightUnits/GenericConversions.hpp>
#include "Ampere.hpp"
#include "Volt.hpp"
#include "Ohm.hpp"

constexpr Volt operator*(Ampere const& lhs, Ohm const& rhs)
{
    return LightUnits::UnitMult<IntegralValueSystem,Volt>(lhs, rhs);
}

constexpr Volt operator*(Ohm const& lhs, Ampere const& rhs)
{
    return rhs*lhs;
}

constexpr Ampere operator/(Volt const& lhs, Ohm const& rhs)
{
    return LightUnits::UnitDiv<IntegralValueSystem, Ampere>(lhs, rhs);
}

constexpr Ohm operator||(Ohm const& lhs, Ohm const& rhs)
{
    auto raw1 = lhs.To<Ohm::BasePrefix>();
    auto raw2 = rhs.To<Ohm::BasePrefix>();
    auto rawr1r2 = static_cast<LightUnits::MultiplicationResultHelper<IntegralValueSystem, Ohm::ValueType, Ohm::ValueType>::type>(raw1)*raw2;
    return  Ohm::From<Ohm::BasePrefix>(
        static_cast<Ohm::ValueType>( rawr1r2 / (raw1+raw2) ));
} 
