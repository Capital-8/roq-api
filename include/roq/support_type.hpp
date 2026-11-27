/* Copyright (c) 2017-2026, Hans Erik Thrane */

/* !!! THIS FILE HAS BEEN AUTO-GENERATED !!! */

#pragma once

#include <fmt/format.h>

#include <magic_enum/magic_enum.hpp>
#include <magic_enum/magic_enum_flags.hpp>

#include <cstdint>
#include <cstdlib>

namespace roq {

//! Enumeration of support types
enum class SupportType : uint64_t {  // NOLINT(performance-enum-size)
  UNDEFINED = 0,
  REFERENCE_DATA = 0x1,    //!< Reference data
  MARKET_STATUS = 0x2,     //!< Market status
  TOP_OF_BOOK = 0x4,       //!< Top of book
  MARKET_BY_PRICE = 0x8,   //!< Market by price
  MARKET_BY_ORDER = 0x10,  //!< Market by order
  TRADE_SUMMARY = 0x20,    //!< Trade summary
  STATISTICS = 0x40,       //!< Statistics
  TIME_SERIES = 0x80,      //!< Time-series
  CREATE_ORDER = 0x10000,  //!< Create order
  MODIFY_ORDER = 0x20000,  //!< Modify order
  CANCEL_ORDER = 0x40000,  //!< Cancel order
  ORDER_ACK = 0x80000,     //!< Order ack
  ORDER = 0x100000,        //!< Order
  ORDER_STATE = 0x800000,  //!< Order
  TRADE = 0x200000,        //!< Trade
  POSITION = 0x400000,     //!< Position
  FUNDS = 0x10000000,      //!< Funds
};

}  // namespace roq

template <>
struct magic_enum::customize::enum_range<roq::SupportType> {
  static constexpr bool is_flags = true;
};

template <>
struct fmt::formatter<roq::SupportType> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(roq::SupportType const &value, format_context &context) const {
    using namespace std::literals;
    return fmt::format_to(context.out(), "{}"sv, magic_enum::enum_flags_name(value));
  }
};