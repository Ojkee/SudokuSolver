#include <gtest/gtest.h>

#include <array>

#include "grid.hpp"

#define M(x) (1 << x)

TEST(Unit, FillingCandidates) {
  auto grid = Grid(
      "001957063"
      "000806070"
      "769130805"
      "007261350"
      "312495786"
      "056378000"
      "108609507"
      "090710608"
      "674583000");
  using CandidateRow = std::array<Grid::CandidateMask_t, 9>;
  const auto result = Grid::Candidates_t{
      CandidateRow{M(2) | M(4) | M(8), M(2) | M(4) | M(8), 0, 0, 0, 0,
                   M(2) | M(4), 0, 0},
      CandidateRow{M(2) | M(4) | M(5), M(2) | M(3) | M(4), M(3) | M(5), 0,
                   M(2) | M(4), 0, M(1) | M(2) | M(4) | M(9), 0,
                   M(1) | M(2) | M(4) | M(9)},
      CandidateRow{0, 0, 0, 0, 0, M(2) | M(4), 0, M(2) | M(4), 0},
      CandidateRow{M(4) | M(8) | M(9), M(4) | M(8), 0, 0, 0, 0, 0, 0,
                   M(4) | M(9)},
      CandidateRow{0, 0, 0, 0, 0, 0, 0, 0, 0},
      CandidateRow{M(4) | M(9), 0, 0, 0, 0, 0, M(1) | M(2) | M(4) | M(9),
                   M(1) | M(2) | M(4) | M(9), M(1) | M(2) | M(4) | M(9)},
      CandidateRow{0, M(2) | M(3), 0, 0, M(2) | M(4), 0, 0, M(2) | M(3) | M(4),
                   0},
      CandidateRow{M(2) | M(5), 0, M(3) | M(5), 0, 0, M(2) | M(4), 0,
                   M(2) | M(3) | M(4), 0},
      CandidateRow{0, 0, 0, 0, 0, 0, M(1) | M(2) | M(9), M(1) | M(2) | M(9),
                   M(1) | M(2) | M(9)},
  };
  ASSERT_EQ(grid.candidates(), result);
}
