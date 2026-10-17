#include <gtest/gtest.h>

#include "grid.hpp"
#include "rules/pointing_elimination.hpp"

TEST(Unit, PointingEliminationRow) {
  auto grid = Grid::of_line(
                  "000000000"
                  "000000000"
                  "000000000"
                  "100000000"
                  "020000000"
                  "003000000"
                  "000000000"
                  "000000000"
                  "000000000")
                  .value();

  for (auto col{0uz}; col < 3; ++col) {
    grid.eliminate_candidate(1, col, 5);
    grid.eliminate_candidate(2, col, 5);
  }

  ASSERT_TRUE(grid.has_candidate(0, 0, 5));
  ASSERT_TRUE(grid.has_candidate(0, 4, 5));
  EXPECT_TRUE(grid.has_candidate(0, 5, 5));
  EXPECT_TRUE(grid.has_candidate(0, 8, 5));

  EXPECT_TRUE(PointingElimination().apply(grid));

  EXPECT_TRUE(grid.has_candidate(0, 0, 5));
  EXPECT_FALSE(grid.has_candidate(0, 4, 5));
  EXPECT_FALSE(grid.has_candidate(0, 5, 5));
  EXPECT_FALSE(grid.has_candidate(0, 8, 5));
}

TEST(Unit, PointingEliminationCol) {
  auto grid = Grid::of_line(
                  "000000000"
                  "000000000"
                  "000000000"
                  "100000000"
                  "020000000"
                  "003000000"
                  "000000000"
                  "000000000"
                  "000000000")
                  .value();

  for (auto row{0uz}; row < 3; ++row) {
    grid.eliminate_candidate(row, 1, 5);
    grid.eliminate_candidate(row, 2, 5);
  }

  ASSERT_TRUE(grid.has_candidate(0, 0, 5));
  ASSERT_TRUE(grid.has_candidate(4, 0, 5));
  EXPECT_TRUE(grid.has_candidate(5, 0, 5));
  EXPECT_TRUE(grid.has_candidate(8, 0, 5));

  EXPECT_TRUE(PointingElimination().apply(grid));

  EXPECT_TRUE(grid.has_candidate(0, 0, 5));
  EXPECT_FALSE(grid.has_candidate(4, 0, 5));
  EXPECT_FALSE(grid.has_candidate(5, 0, 5));
  EXPECT_FALSE(grid.has_candidate(8, 0, 5));
}
