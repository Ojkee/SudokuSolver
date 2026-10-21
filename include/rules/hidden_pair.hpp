#pragma once

#include <utility>
#include <vector>

#include "../grid.hpp"
#include "rule.hpp"

using Position = std::pair<Grid::Idx, Grid::Idx>;
using Positions = std::array<std::vector<Position>,
                             10>;  // for easier matching with 1-9 values

class HiddenPair final : public Rule {
 public:
  [[nodiscard]] auto name() const noexcept -> const std::string override {
    return "hidden_pair";
  }
  [[nodiscard]] auto apply(Grid& grid) const noexcept -> bool override;

 private:
  auto at_least_n_empty_group(const Grid& grid, const uint8_t n,
                              Grid::Idx group_row,
                              Grid::Idx group_col) const noexcept -> bool;
  [[nodiscard]] auto values_positions_group(Grid& grid, Grid::Idx group_row,
                                            Grid::Idx group_col) const noexcept
      -> Positions;

  auto at_least_n_empty_row(const Grid& grid, const uint8_t n,
                            Grid::Idx row) const noexcept -> bool;
  [[nodiscard]] auto values_positions_row(Grid& grid,
                                          Grid::Idx row) const noexcept
      -> Positions;
  auto at_least_n_empty_col(const Grid& grid, const uint8_t n,
                            Grid::Idx col) const noexcept -> bool;
  [[nodiscard]] auto values_positions_col(Grid& grid,
                                          Grid::Idx col) const noexcept
      -> Positions;

  auto restrict_of_positions(Grid& grid,
                             const Positions& positions) const noexcept -> bool;
  auto eliminate_candidate_of_position(Grid& grid, const Position& pos1,
                                       const Position& pos2,
                                       Grid::Cell value) const noexcept -> bool;
};
