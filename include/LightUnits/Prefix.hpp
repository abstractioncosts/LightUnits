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

namespace LightUnits {
    /// @brief Based on SI prefixes
    ///
    enum class Prefix : int {
        Micro = -6,
        Milli = -3,
        One = 0,
        Kilo = 3
    };

    namespace detail {

        /// @brief Determine difference of prefixes in ordner of magnitude
        ///
        /// @example source=Milli,target=Micro
        /// DecadesDiff=(-3)-(-6)=3
        /// Ie. a unit denominated in Milli-sth. has to be multiplied by 10^3 to yield a unit denominated in Micro-sth.
        ///
        constexpr int DecadesDiff(Prefix source, Prefix target) {
            return static_cast<int>(source) - static_cast<int>(target);
        }

        /// @brief Determine order of magnitude of correction factor for multiplication
        ///
        /// @example: U=I*R
        /// [U] in mV
        /// [R] in mOhm
        /// [I] in uA
        /// Correction factor (-6) + (-3) - (-3) = -6
        /// Multiplying the raw values of I and R will yield a result which is not denominated in uA and is 10^6 larger than desired.
        ///
        constexpr int DimensionCorrectionFromMult(Prefix target, Prefix lhs, Prefix rhs) {
            return static_cast<int>(lhs) + static_cast<int>(rhs) - static_cast<int>(target);
        }

        /// @brief Determine order of magnitude of correction factor for multiplication
        ///
        /// @example: I=U/R
        /// [U] in mV
        /// [R] in mOhm
        /// [I] in uA
        /// Correction factor (-3) - (-3) - (-6) = 6
        /// Dividing the raw values of U and R will yield a result which is not denominated in uA and is 10^6 smaller than desired.
        ///
        constexpr int DimensionCorrectionFromDiv(Prefix target, Prefix lhs, Prefix rhs) {
            // Operation <Target>=<Lhs> / <Rhs>
            return static_cast<int>(lhs) - static_cast<int>(rhs) - static_cast<int>(target);
        }

        constexpr Prefix FinerResolution(Prefix a, Prefix b) {
            return (static_cast<int>(a) < static_cast<int>(b)) ? a : b;
        }
    }
}
