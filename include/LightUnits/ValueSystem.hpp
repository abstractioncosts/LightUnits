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
    /// @brief Defines a strictly ordered systems of types ascending in size
    ///
    /// These types will be used for conversions between units.
    /// Requirements:
    /// - Each list item has to have at least double the size in bits than its predecessor.
    /// - A list must consist entirely of either signed or unsigned items
    ///
    /// Example for valid lists:
    ///     USys<int32_t>, USys<int8_t, int16_t>, USys<int8_t, int16_t, int64_t>
    ///
    template<typename ... Ts>
    struct ValueSystem;

    namespace detail {
        template<typename Sys, typename Elem>
        struct HasElement;

        template<typename Sys0, typename ...Sys, typename Elem>
        struct HasElement<ValueSystem<Sys0, Sys...>, Elem> {
            static bool const Value = std::is_same<Sys0, Elem>::value || HasElement<ValueSystem<Sys...>, Elem>::Value;
        };

        template<typename Elem>
        struct HasElement<ValueSystem<>, Elem> {
            static bool const Value = false;
        };

        template<typename Sys>
        struct Count;

        template<typename Sys0, typename ...Sys>
        struct Count<ValueSystem<Sys0, Sys...>>
            : std::integral_constant<std::size_t, 1u + Count<ValueSystem<Sys...>>::value> {
        };

        template<>
        struct Count<ValueSystem<>>
            : std::integral_constant<std::size_t, 0u> {
        };

        template<typename Sys, typename Elem>
        struct PositionOf;

        template<typename ...Sys, typename Elem>
        struct PositionOf<ValueSystem<Elem, Sys...>, Elem>
            : std::integral_constant<std::size_t, 0> {
        };

        template<typename Sys0, typename ...Sys, typename Elem>
        struct PositionOf<ValueSystem<Sys0, Sys...>, Elem>
            : std::integral_constant<std::size_t, 1u + PositionOf<ValueSystem<Sys...>, Elem>::value> {
        };

        template<typename T>
        struct assert_false : std::false_type {
        };

        template<typename Elem>
        struct PositionOf<ValueSystem<>, Elem> {
            // Item not found in list. Throw error.
            // To fullfil c++ "well-formed" requirements, make error message formally dependent on type.
            static_assert(assert_false<Elem>::value, "Item not contained in list.");
        };

        template<typename Sys, typename T1, typename T2>
        struct LargerPositionOf
            : std::integral_constant<std::size_t,
            PositionOf<Sys, T1>::value >= PositionOf<Sys, T2>::value ?
            PositionOf<Sys, T1>::value : PositionOf<Sys, T2>::value> {
        };

        template<typename Sys, std::size_t index>
        struct Element;

        template<typename Sys0, typename ...Sys, std::size_t index>
        struct Element<ValueSystem<Sys0, Sys...>, index> {
            using type = typename Element<ValueSystem<Sys...>, index - 1>::type;
        };

        template<typename Sys0, typename ...Sys>
        struct Element<ValueSystem<Sys0, Sys...>, 0> {
            using type = Sys0;
        };
    }

    template<typename Sys, typename T_Lhs, typename T_Rhs>
    struct MultiplicationResultHelper {
        typedef typename detail::Element<Sys, detail::LargerPositionOf<Sys, T_Lhs, T_Rhs>::value + 1>::type type;
    };

    template <typename Sys, typename T>
    struct LargerType {
        typedef typename detail::Element<Sys, detail::PositionOf<Sys, T>::value+1>::type type;
    };


}

