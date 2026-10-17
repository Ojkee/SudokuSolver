#include <gtest/gtest.h>

#include "rules/hidden_single.hpp"

TEST(Unit, HiddenSingle) {
  auto grid = Grid::of_line(
                  "000000000"
                  "000100000"
                  "000000100"
                  "010000000"
                  "000000000"
                  "000000000"
                  "001000000"
                  "000000000"
                  "000000000")
                  .value();

  ASSERT_TRUE(grid.empty(0, 0));

  EXPECT_TRUE(HiddenSingle().apply(grid));
  EXPECT_EQ(grid.at(0, 0), 1);
}

TEST(Unit, HiddenSingleNoProgress) {
  auto grid = Grid::of_line(std::string(81, '0')).value();

  EXPECT_FALSE(HiddenSingle().apply(grid));
}
