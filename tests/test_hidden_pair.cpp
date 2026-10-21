#include <gtest/gtest.h>

#include <string>

#include "grid.hpp"
#include "rules/hidden_pair.hpp"

TEST(Unit, HiddenPairGroup) {
  auto grid = Grid::of_line(std::string(81, '0')).value();

  for (auto row{0uz}; row < 3; ++row) {
    for (auto col{0uz}; col < 3; ++col) {
      if ((row == 0 && col == 0) || (row == 1 && col == 1)) {
        continue;
      }
      grid.eliminate_candidate(row, col, 1);
      grid.eliminate_candidate(row, col, 2);
    }
  }

  ASSERT_TRUE(grid.has_candidate(0, 0, 1));
  ASSERT_TRUE(grid.has_candidate(0, 0, 2));
  ASSERT_TRUE(grid.has_candidate(1, 1, 1));
  ASSERT_TRUE(grid.has_candidate(1, 1, 2));
  ASSERT_TRUE(grid.has_candidate(0, 0, 3));
  ASSERT_TRUE(grid.has_candidate(1, 1, 3));

  EXPECT_TRUE(HiddenPair().apply(grid));

  EXPECT_TRUE(grid.has_candidate(0, 0, 1));
  EXPECT_TRUE(grid.has_candidate(0, 0, 2));
  EXPECT_TRUE(grid.has_candidate(1, 1, 1));
  EXPECT_TRUE(grid.has_candidate(1, 1, 2));

  EXPECT_FALSE(grid.has_candidate(0, 0, 3));
  EXPECT_FALSE(grid.has_candidate(1, 1, 3));
}

TEST(Unit, HiddenPairRow) {
  auto grid = Grid::of_line(std::string(81, '0')).value();

  for (auto col{0uz}; col < 9; ++col) {
    if (col == 1 || col == 7) continue;

    grid.eliminate_candidate(4, col, 1);
    grid.eliminate_candidate(4, col, 2);
  }

  ASSERT_TRUE(grid.has_candidate(4, 1, 1));
  ASSERT_TRUE(grid.has_candidate(4, 1, 2));
  ASSERT_TRUE(grid.has_candidate(4, 7, 1));
  ASSERT_TRUE(grid.has_candidate(4, 7, 2));
  ASSERT_TRUE(grid.has_candidate(4, 1, 3));
  ASSERT_TRUE(grid.has_candidate(4, 7, 3));

  EXPECT_TRUE(HiddenPair().apply(grid));

  EXPECT_TRUE(grid.has_candidate(4, 1, 1));
  EXPECT_TRUE(grid.has_candidate(4, 1, 2));
  EXPECT_TRUE(grid.has_candidate(4, 7, 1));
  EXPECT_TRUE(grid.has_candidate(4, 7, 2));

  EXPECT_FALSE(grid.has_candidate(4, 1, 3));
  EXPECT_FALSE(grid.has_candidate(4, 7, 3));
}

TEST(Unit, HiddenPairColumn) {
  auto grid = Grid::of_line(std::string(81, '0')).value();

  for (auto row{0uz}; row < 9; ++row) {
    if (row == 1 || row == 7) continue;

    grid.eliminate_candidate(row, 5, 1);
    grid.eliminate_candidate(row, 5, 2);
  }

  ASSERT_TRUE(grid.has_candidate(1, 5, 1));
  ASSERT_TRUE(grid.has_candidate(1, 5, 2));
  ASSERT_TRUE(grid.has_candidate(7, 5, 1));
  ASSERT_TRUE(grid.has_candidate(7, 5, 2));
  ASSERT_TRUE(grid.has_candidate(1, 5, 3));
  ASSERT_TRUE(grid.has_candidate(7, 5, 3));

  EXPECT_TRUE(HiddenPair().apply(grid));

  EXPECT_TRUE(grid.has_candidate(1, 5, 1));
  EXPECT_TRUE(grid.has_candidate(1, 5, 2));
  EXPECT_TRUE(grid.has_candidate(7, 5, 1));
  EXPECT_TRUE(grid.has_candidate(7, 5, 2));

  EXPECT_FALSE(grid.has_candidate(1, 5, 3));
  EXPECT_FALSE(grid.has_candidate(7, 5, 3));
}

TEST(Unit, HiddenPairNoProgress) {
  auto grid = Grid::of_line(std::string(81, '0')).value();

  EXPECT_FALSE(HiddenPair().apply(grid));
}
