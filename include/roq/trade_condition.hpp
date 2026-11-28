/* Copyright (c) 2017-2026, Hans Erik Thrane */

/* !!! THIS FILE HAS BEEN AUTO-GENERATED !!! */

#pragma once

#include <fmt/format.h>

#include <magic_enum/magic_enum.hpp>
#include <magic_enum/magic_enum_flags.hpp>

#include <cstdint>
#include <cstdlib>

namespace roq {

//! Enumeration of trade condition flags
enum class TradeCondition : uint32_t {
  IMPLIED_MATCHING = 0x1,          //!< Matching implied from spread markets
  FORCED_LIQUIDATION = 0x2,        //!< Forced order liquidation
  RETAIL_PRICE_IMPROVEMENT = 0x4,  //!< Retail Price Improvement
};

}  // namespace roq

template <>
struct magic_enum::customize::enum_range<roq::TradeCondition> {
  static constexpr bool is_flags = true;
};

template <>
struct fmt::formatter<roq::TradeCondition> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(roq::TradeCondition const &value, format_context &context) const {
    using namespace std::literals;
    return fmt::format_to(context.out(), "{}"sv, magic_enum::enum_flags_name(value));
  }
};