#include "rules/naked_single.hpp"

#include <ranges>

namespace vw = std::views;

auto NakedSingle::apply(Grid& grid) const noexcept -> bool {
  const auto cand = grid.candidates();
  for (const auto [i, row] : vw::enumerate(cand)) {
    for (const auto [j, mask] : vw::enumerate(row)) {
      const auto values = Grid::of_mask(mask);
      if (values.size() == 1) {
        grid.place(i, j, values[0]);
        return true;
      }
    }
  }
  return false;
}
