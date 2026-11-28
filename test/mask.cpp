/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include <catch2/catch_all.hpp>

#include <fmt/format.h>

#include <magic_enum/magic_enum_format.hpp>

#include "roq/mask.hpp"

using namespace std::literals;

using namespace roq;

namespace {
enum class E : uint32_t {
  A = 1,
  B = 2,
  C = 4,
};
}

template <>
struct magic_enum::customize::enum_range<E> {
  static constexpr bool is_flags = true;
};

namespace {
// compile-time checks
static_assert(Mask<E>{E::A} == Mask<E>{E::A});
static_assert(Mask<E>{E::A} != Mask<E>{});
static_assert(Mask<E>{E::A} != Mask<E>{E::B});
static_assert(Mask<E>{E::A} == Mask<E>{}.set(E::A));
static_assert(Mask<E>{E::A, E::B} == Mask<E>{}.set(E::A).set(E::B));
static_assert(Mask<E>{E::A, E::B, E::C} == Mask<E>{}.set(E::A).set(E::B).set(E::C));
}  // namespace

// run-time checks

TEST_CASE("mask_simple", "[mask]") {
  auto mask_1 = Mask{
      E::A,
  };
  auto mask_2 = Mask{mask_1, E::B};
  // has
  CHECK(mask_1.has({E::A}) == true);
  CHECK(mask_1.has({E::B}) == false);
  CHECK(mask_2.has({E::A}) == true);
  CHECK(mask_2.has({E::B}) == true);
  CHECK(mask_2.has({E::C}) == false);
  CHECK(mask_2.has({E::A, E::B}) == true);
  CHECK(mask_2.has({E::B, E::C}) == false);
  CHECK(mask_2.has({E::A, E::B, E::C}) == false);
  // has-any
  CHECK(mask_2.has_any(E::A) == true);
  CHECK(mask_2.has_any({E::A, E::B}) == true);
  CHECK(mask_2.has_any({E::A, E::B, E::C}) == true);
  // fmt
  CHECK(fmt::format("{}"sv, Mask<E>{}) == ""sv);
  CHECK(fmt::format("{}"sv, Mask{E::A}) == "A"sv);
  CHECK(fmt::format("{}"sv, Mask{E::B, E::C}) == "B|C"sv);
  CHECK(fmt::format("{}"sv, Mask{E::A, E::B, E::C}) == "A|B|C"sv);
  CHECK(fmt::format("{}"sv, mask_1) == "A"sv);
  CHECK(fmt::format("{}"sv, mask_2) == "A|B"sv);
}
