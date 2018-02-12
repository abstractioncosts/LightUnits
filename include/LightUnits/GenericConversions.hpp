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

#include "MultiplyWithExponent.hpp"
#include "ValueSystem.hpp"
#include "Prefix.hpp"

namespace LightUnits {
    /// @brief Multiplication of two units yielding a third unit
    ///
    /// Units within the "International Systems of Units" (SI) relate to each other.
    /// E.g. a multiplication of Ampere and Ohm will yield Volt.
    /// This function allows for these conversions and takes care of different representations in the
    /// underlyings power of magnitude.
    /// (1) Both raw values are multiplied and stored in a temporary long long type.
    /// (2) This temporary is multiplied by a correction factor to adjust for the given magnitudes.
    /// (3) Conversion back to the target underlying.
    ///
    template<typename ValueSys, typename Result, typename Lhs, typename Rhs>
    constexpr Result UnitMult(Lhs const &lhs, Rhs const &rhs) {
        using MultValueType = typename MultiplicationResultHelper<ValueSys, typename Lhs::ValueType, typename Rhs::ValueType>::type;

        auto mult_undefinedDimension =
                static_cast<MultValueType>(lhs.template To<Lhs::BasePrefix>())
                * rhs.template To<Rhs::BasePrefix>();

        auto mult_targetBasePrefix = detail::MultiplyWithExponent<
                detail::DimensionCorrectionFromMult(Result::BasePrefix, Lhs::BasePrefix, Rhs::BasePrefix)>(
                mult_undefinedDimension);

        return Result::template From<Result::BasePrefix>(
                static_cast<typename Result::ValueType>(mult_targetBasePrefix)
        );
    }

    /// @brief Division of two units yielding a third unit
    ///
    /// \sa UnitMult
    ///
    template<typename ValueSys, typename Result, typename Lhs, typename Rhs>
    constexpr Result UnitDiv(Lhs const &lhs, Rhs const &rhs) {
        auto lhs_raw = lhs.template To<Lhs::BasePrefix>();
        auto rhs_raw = rhs.template To<Rhs::BasePrefix>();

        using TCorrection = typename LightUnits::LargerType<ValueSys, typename Lhs::ValueType>::type;

        constexpr int magnitudeCorrection = detail::DimensionCorrectionFromDiv(Result::BasePrefix, Lhs::BasePrefix, Rhs::BasePrefix);
        auto lhs_raw_corrected = detail::MultiplyWithExponent<magnitudeCorrection>(static_cast<TCorrection>(lhs_raw));

        auto division_raw = lhs_raw_corrected / rhs_raw;

        return Result::template From<Result::BasePrefix>(
                static_cast<typename Result::ValueType>(division_raw));
    }
}
