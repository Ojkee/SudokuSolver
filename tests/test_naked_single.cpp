#include <gtest/gtest.h>

#include "rules/naked_single.hpp"

TEST(Unit, NakedSingleRow) {
  auto grid =
      Grid::of_line(std::string("123456780") + std::string(72, '0')).value();

  ASSERT_TRUE(grid.empty(0, 8));
  EXPECT_TRUE(NakedSingle().apply(grid));
  EXPECT_EQ(grid.at(0, 8), 9);
}

TEST(Unit, NakedSingleColumn) {
  auto grid = Grid::of_line(
                  "100000000"
                  "200000000"
                  "300000000"
                  "400000000"
                  "500000000"
                  "600000000"
                  "700000000"
                  "800000000"
                  "000000000")
                  .value();

  ASSERT_TRUE(grid.empty(8, 0));
  EXPECT_TRUE(NakedSingle().apply(grid));
  EXPECT_EQ(grid.at(8, 0), 9);
}

TEST(Unit, NakedSingleBox) {
  auto grid = Grid::of_line(
                  "000000000"
                  "000000000"
                  "000000000"
                  "000123000"
                  "000456000"
                  "000780000"
                  "000000000"
                  "000000000"
                  "000000000")
                  .value();

  ASSERT_TRUE(grid.empty(5, 5));
  EXPECT_TRUE(NakedSingle().apply(grid));
  EXPECT_EQ(grid.at(5, 5), 9);
}

TEST(Unit, NakedSingleRowColumnAndBox) {
  auto grid = Grid::of_line(
                  "000040000"
                  "000050000"
                  "000060000"
                  "000700000"
                  "123000000"
                  "000008000"
                  "000000000"
                  "000000000"
                  "000000000")
                  .value();

  ASSERT_TRUE(grid.empty(4, 4));
  EXPECT_TRUE(NakedSingle().apply(grid));
  EXPECT_EQ(grid.at(4, 4), 9);
}

TEST(Unit, NakedSingleNoProgress) {
  auto grid = Grid::of_line(std::string(81, '0')).value();

  EXPECT_FALSE(NakedSingle().apply(grid));
}
