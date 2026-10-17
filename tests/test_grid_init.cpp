#include <gtest/gtest.h>

#include <tuple>

#include "grid.hpp"

TEST(Unit, InvalidLengthErrors) {
  const auto too_short = Grid::of_line("123");
  EXPECT_EQ(too_short.error(), ParseError::InvalidLength);

  const auto too_long = Grid::of_line(
      "123456789"
      "123456789"
      "123456789"
      "123456789"
      "123456789"
      "123456789"
      "123456789"
      "123456789"
      "1234567890");
  EXPECT_EQ(too_long.error(), ParseError::InvalidLength);
}

TEST(Unit, InvalidCharError) {
  const auto invalid_char = Grid::of_line(
      "123456789"
      "123456789"
      "123456789"
      "123456789"
      "123456789"
      "123456789"
      "123456789"
      "123456789"
      "12345678a");
  EXPECT_EQ(invalid_char.error(), ParseError::InvalidChar);
}

TEST(Unit, ValidGridInit) {
  const auto valid = Grid::of_line(
      "193000564"
      "600004001"
      "800300009"
      "070000600"
      "000090000"
      "006000010"
      "700008005"
      "200500006"
      "514000382");
  const auto checks = {
      std::tuple{0, 0, 1}, std::tuple{0, 3, 0}, std::tuple{0, 8, 4},
      std::tuple{4, 4, 9}, std::tuple{8, 0, 5}, std::tuple{8, 8, 2},
  };
  for (const auto [row, col, value] : checks) {
    ASSERT_EQ(valid->at(row, col), value);
  }
}
