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

#include <type_traits>

namespace LightUnits {
    namespace detail {
        template<int Exponent>
        struct ExponentToMultiplier;

        /// @brief Terminating specialization for exponent 0
        template<>
        struct ExponentToMultiplier<0> {
            enum {
                value = 1
            };
        };

        /// @brief Recursive specialization for elements larger 0
        template<int Exponent>
        struct ExponentToMultiplier {
            enum {
                value = 10 * ExponentToMultiplier<Exponent - 1>::value
            };
        };

        template<int Exponent, typename ValueType>
        constexpr typename std::enable_if<(Exponent >= 0), ValueType>::type
        MultiplyWithExponent(ValueType val) {
            return val * ExponentToMultiplier<Exponent>::value;
        }

        template<int Exponent, typename ValueType>
        constexpr typename std::enable_if<(Exponent < 0), ValueType>::type
        MultiplyWithExponent(ValueType val) {
            return val / ExponentToMultiplier<-Exponent>::value;
        }
    }
}
