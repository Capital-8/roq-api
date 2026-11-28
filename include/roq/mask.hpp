/* Copyright (c) 2017-2026, Hans Erik Thrane */

#pragma once

#include <fmt/format.h>

#include <magic_enum/magic_enum.hpp>
#include <magic_enum/magic_enum_flags.hpp>

#include <initializer_list>

namespace roq {

template <typename T>
  requires magic_enum::is_flags_enum_v<T>
struct Mask final {
  using value_type = T;
  using underlying_type = typename std::underlying_type_t<value_type>;

  constexpr Mask() = default;

  constexpr explicit Mask(underlying_type mask) : value_{mask} {}

  constexpr explicit Mask(T flag) : value_{static_cast<underlying_type>(flag)} {}

  constexpr Mask(std::initializer_list<T> flags) {
    for (auto &flag : flags) {
      value_ |= static_cast<underlying_type>(flag);
    }
  }

  template <typename... Args>
  constexpr Mask(Mask const &other, Args &&...args) : value_{other.value_ | Mask{std::forward<Args>(args)...}.get()} {}

  constexpr auto operator<=>(Mask const &) const = default;

  constexpr bool empty() const { return value_ == underlying_type{}; }

  constexpr void reset() { value_ = underlying_type{}; }

  constexpr underlying_type get() const { return value_; }

  constexpr bool is_same(T flag) const { return value_ == static_cast<underlying_type>(flag); }

  // has

  constexpr bool has(T flag) const { return magic_enum::enum_flags_test(T{value_}, flag); }

  constexpr bool has(std::initializer_list<T> flags) const {
    underlying_type value = {};
    for (auto &flag : flags) {
      value |= static_cast<underlying_type>(flag);
    }
    return magic_enum::enum_flags_test(T{value_}, T{value});
  }

  constexpr bool has(Mask rhs) const { return magic_enum::enum_flags_test(T{value_}, T{rhs.value_}); }

  // has-any

  constexpr bool has_any(T flag) const { return magic_enum::enum_flags_test_any(T{value_}, flag); }

  constexpr bool has_any(std::initializer_list<T> flags) const {
    underlying_type value = {};
    for (auto &flag : flags) {
      value |= static_cast<underlying_type>(flag);
    }
    return magic_enum::enum_flags_test_any(T{value_}, T{value});
  }

  constexpr bool has_any(Mask rhs) const { return magic_enum::enum_flags_test_any(T{value_}, T{rhs.value_}); }

  // has-none

  constexpr bool has_none(T flag) const { return !has_any(flag); }

  constexpr bool has_none(std::initializer_list<T> flags) const { return !has_any(flags); }

  constexpr bool has_none(Mask rhs) const { return !has_any(rhs); }

  // set

  constexpr Mask &set(T flag) {
    value_ |= static_cast<underlying_type>(flag);
    return *this;
  }

  constexpr Mask &set(Mask rhs) {
    value_ |= rhs.value_;
    return *this;
  }

  // remove

  constexpr Mask &remove(T flag) {
    value_ &= ~static_cast<underlying_type>(flag);
    return *this;
  }

  constexpr Mask &remove(Mask rhs) {
    value_ &= ~rhs.value_;
    return *this;
  }

  // logical

  constexpr Mask negate() const { return Mask{~value_}; }

  constexpr Mask logical_and(Mask rhs) const { return Mask{value_ & rhs.value_}; }

  constexpr Mask &set(std::initializer_list<T> flags) {
    for (auto &flag : flags) {
      value_ |= static_cast<underlying_type>(flag);
    }
    return *this;
  }

  constexpr Mask operator~() const { return negate(); }

  constexpr Mask operator&(Mask rhs) const { return logical_and(rhs); }

  constexpr Mask &operator|=(T flag) {
    set(flag);
    return *this;
  }

  constexpr Mask &operator|=(Mask rhs) {
    set(rhs);
    return *this;
  }

 private:
  underlying_type value_ = {};
};

}  // namespace roq

template <typename T>
struct fmt::formatter<roq::Mask<T>> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(roq::Mask<T> const &value, format_context &context) const {
    using namespace std::literals;
    T value_2{value.get()};
    return fmt::format_to(context.out(), "{}"sv, magic_enum::enum_flags_name(value_2));
  }
};
