#include <gtest/gtest.h>

#include <string>

#include "grid.hpp"
#include "rules/claiming_pair.hpp"

TEST(Unit, ClaimingPairRow) {
  auto grid = Grid::of_line(std::string(81, '0')).value();

  for (auto col{2uz}; col < 9; ++col) {
    grid.eliminate_candidate(0, col, 5);
  }

  ASSERT_TRUE(grid.has_candidate(0, 0, 5));
  ASSERT_TRUE(grid.has_candidate(0, 1, 5));
  ASSERT_TRUE(grid.has_candidate(1, 2, 5));
  ASSERT_TRUE(grid.has_candidate(2, 2, 5));

  EXPECT_TRUE(ClaimingPair().apply(grid));

  EXPECT_TRUE(grid.has_candidate(0, 0, 5));
  EXPECT_TRUE(grid.has_candidate(0, 1, 5));
  EXPECT_FALSE(grid.has_candidate(1, 2, 5));
  EXPECT_FALSE(grid.has_candidate(2, 2, 5));
}

TEST(Unit, ClaimingPairColumn) {
  auto grid = Grid::of_line(std::string(81, '0')).value();

  for (auto row{2uz}; row < 9; ++row) {
    grid.eliminate_candidate(row, 0, 5);
  }

  ASSERT_TRUE(grid.has_candidate(0, 0, 5));
  ASSERT_TRUE(grid.has_candidate(1, 0, 5));
  ASSERT_TRUE(grid.has_candidate(2, 1, 5));
  ASSERT_TRUE(grid.has_candidate(2, 2, 5));

  EXPECT_TRUE(ClaimingPair().apply(grid));

  EXPECT_TRUE(grid.has_candidate(0, 0, 5));
  EXPECT_TRUE(grid.has_candidate(1, 0, 5));
  EXPECT_FALSE(grid.has_candidate(2, 1, 5));
  EXPECT_FALSE(grid.has_candidate(2, 2, 5));
}

TEST(Unit, ClaimingPairNoProgress) {
  auto grid = Grid::of_line(std::string(81, '0')).value();

  EXPECT_FALSE(ClaimingPair().apply(grid));
}
