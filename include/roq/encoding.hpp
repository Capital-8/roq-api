/* Copyright (c) 2017-2026, Hans Erik Thrane */

/* !!! THIS FILE HAS BEEN AUTO-GENERATED !!! */

#pragma once

#include <fmt/format.h>

#include <magic_enum/magic_enum.hpp>
#include <magic_enum/magic_enum_flags.hpp>

#include <cstdint>
#include <cstdlib>

namespace roq {

//! Enumeration of message encoding type flags (informational, only)
enum class Encoding : uint32_t {
  FIX = 0x1,   //!< FIX
  JSON = 0x2,  //!< JSON
  SBE = 0x4,   //!< SBE
  FBS = 0x8,   //!< FlatBuffers
};

}  // namespace roq

template <>
struct magic_enum::customize::enum_range<roq::Encoding> {
  static constexpr bool is_flags = true;
};

template <>
struct fmt::formatter<roq::Encoding> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(roq::Encoding const &value, format_context &context) const {
    using namespace std::literals;
    return fmt::format_to(context.out(), "{}"sv, magic_enum::enum_flags_name(value));
  }
};