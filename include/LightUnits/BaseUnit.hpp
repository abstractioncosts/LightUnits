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

#include "Prefix.hpp"
#include "MultiplyWithExponent.hpp"
#include <limits>

namespace LightUnits {
    template<typename TypeTag, typename T_Representation>
    class BaseUnit : public T_Representation {
    public:
        using ValueType = typename T_Representation::ValueType;

        BaseUnit() = default;

        /// Assignment operators
        inline constexpr BaseUnit &operator=(BaseUnit const &rhs) {
            m_value = rhs.Raw();
            return *this;
        }

        /// Arithmetic operators
        inline constexpr BaseUnit &operator+=(BaseUnit const &rhs) {
            m_value += rhs.Raw();
            return *this;
        }

        inline constexpr BaseUnit &operator-=(BaseUnit const &rhs) {
            m_value -= rhs.Raw();
            return *this;
        }

        inline constexpr BaseUnit operator-() const {
            return BaseUnit(-m_value);
        }

        inline constexpr BaseUnit operator+(BaseUnit const &rhs) const {
            return BaseUnit(m_value + rhs.Raw());
        }

        inline constexpr BaseUnit operator-(BaseUnit const &rhs) const {
            return BaseUnit(m_value - rhs.Raw());
        }


        friend inline constexpr BaseUnit operator*(BaseUnit const &lhs, ValueType const &rhs) {
            return BaseUnit(lhs.m_value * rhs);
        }

        friend inline constexpr BaseUnit operator*(ValueType const &lhs, BaseUnit const &rhs) {
            return rhs * lhs;
        }

        friend inline constexpr BaseUnit operator*(BaseUnit const& lhs, float const& rhs)
        {
            float scaled = rhs * lhs.m_value;
            return BaseUnit(static_cast<ValueType>(scaled));
        }

        friend inline constexpr BaseUnit operator*(float const& lhs, BaseUnit const& rhs)
        {
            return rhs * lhs;
        }

        inline constexpr float operator/(BaseUnit const &rhs) const {
            return static_cast<float>(Raw()) / rhs.Raw();
        }

        friend inline constexpr BaseUnit operator/(BaseUnit const &lhs, ValueType const &rhs) {
            return BaseUnit(lhs.m_value / rhs);
        }

        friend inline constexpr BaseUnit operator/(BaseUnit const &lhs, float const &rhs) {
            float scaled = lhs.m_value / rhs;
            return BaseUnit(static_cast<ValueType>(scaled));
        }

        /// Modulo operator for Unit modulo Unit returns Unit
        ///
        /// \example        5s % 3s = (2s) = 3s*1 + (2s)
        /// Consistent to   5s / 3s = (1)  = 3s*(1) + 2s
        ///
        /// \returns Remainder of lhs / rhs
        ///
        friend inline constexpr BaseUnit operator%(BaseUnit const& lhs, BaseUnit const& rhs)
        {
            ValueType remainder = lhs.m_value % rhs.m_value;
            return BaseUnit(remainder);
        }

        /// Comparision operators
        friend constexpr bool operator==(BaseUnit const &lhs, BaseUnit const &rhs) {
            return lhs.m_value == rhs.m_value;
        }

        friend constexpr bool operator!=(BaseUnit const &lhs, BaseUnit const &rhs) {
            return lhs.m_value != rhs.m_value;
        }

        friend constexpr bool operator<(BaseUnit const &lhs, BaseUnit const &rhs) {
            return lhs.m_value < rhs.m_value;
        }

        friend constexpr bool operator>(BaseUnit const &lhs, BaseUnit const &rhs) {
            return lhs.m_value > rhs.m_value;
        }

        friend constexpr bool operator<=(BaseUnit const &lhs, BaseUnit const &rhs) {
            return lhs.m_value <= rhs.m_value;
        }

        friend constexpr bool operator>=(BaseUnit const &lhs, BaseUnit const &rhs) {
            return lhs.m_value >= rhs.m_value;
        }

        /// Non-operator member functions

        template<Prefix source>
        static constexpr BaseUnit From(ValueType val) {
            ValueType res = detail::MultiplyWithExponent<
                    detail::DecadesDiff(source, T_Representation::BasePrefix)>(val);
            return BaseUnit(res);
        }

        /// Converts the given float value with maximum precision to underlying representation
        ///
        /// \example underlying representation int / BasePrefix Milli
        ///          A value of 1,0204f will get converted to 1020. The last digit 4 exceeds the target
        ///          precision and is discarded.
        ///
        static constexpr BaseUnit FromFloat(float val) {
            constexpr int exp = detail::DecadesDiff(Prefix::One, T_Representation::BasePrefix);
            float val_correctExp = val * detail::ExponentToMultiplier<exp>::value;
            return BaseUnit::From<T_Representation::BasePrefix>( static_cast<BaseUnit::ValueType>(val_correctExp));
        }

        template<Prefix target>
        constexpr ValueType To() const {
            return detail::MultiplyWithExponent<
                    detail::DecadesDiff(T_Representation::BasePrefix, target)>(m_value);
        }

        /// Converts the value to a float representation
        ///
        constexpr float ToFloat() const {
            constexpr int exp = detail::DecadesDiff(Prefix::One, T_Representation::BasePrefix);
            float val_correctExp = static_cast<float>(m_value) / detail::ExponentToMultiplier<exp>::value;
            return val_correctExp;
        }

    protected:
        explicit constexpr BaseUnit(ValueType value)
                : m_value(value) {

        }

        inline constexpr ValueType Raw() const {
            return m_value;
        }

    protected:
        ValueType m_value;

        friend struct std::numeric_limits<LightUnits::BaseUnit<TypeTag, T_Representation>>;
    };
}

namespace std
{
    template<typename Tag, typename Rep>
    struct numeric_limits<LightUnits::BaseUnit<Tag, Rep>> {
        static constexpr bool is_specialized = true;

        static constexpr LightUnits::BaseUnit<Tag, Rep> min() {
            return LightUnits::BaseUnit<Tag, Rep>(
                    std::numeric_limits<typename LightUnits::BaseUnit<Tag, Rep>::ValueType>::min()
            );
        };

        static constexpr LightUnits::BaseUnit<Tag, Rep> max() {
            return LightUnits::BaseUnit<Tag, Rep>(
                    std::numeric_limits<typename LightUnits::BaseUnit<Tag, Rep>::ValueType>::max()
            );
        };
    };
}
