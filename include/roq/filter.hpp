/* Copyright (c) 2017-2026, Hans Erik Thrane */

/* !!! THIS FILE HAS BEEN AUTO-GENERATED !!! */

#pragma once

#include <fmt/format.h>

#include <magic_enum/magic_enum.hpp>
#include <magic_enum/magic_enum_flags.hpp>

#include <cstdint>
#include <cstdlib>

namespace roq {

//! Enumeration of filter field flags
enum class Filter : uint64_t {
  ACCOUNT = 0x1,      //!< By account
  EXCHANGE = 0x2,     //!< By exchange
  SYMBOL = 0x4,       //!< By symbol
  STRATEGY_ID = 0x8,  //!< By strategy_id
  SIDE = 0x10,        //!< By side
};

}  // namespace roq

template <>
struct magic_enum::customize::enum_range<roq::Filter> {
  static constexpr bool is_flags = true;
};

template <>
struct fmt::formatter<roq::Filter> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(roq::Filter const &value, format_context &context) const {
    using namespace std::literals;
    return fmt::format_to(context.out(), "{}"sv, magic_enum::enum_flags_name(value));
  }
};