#pragma once

#include "../grid.hpp"
#include "rule.hpp"

class ClaimingPair final : public Rule {
 public:
  [[nodiscard]] auto name() const noexcept -> const std::string override {
    return "claiming_pair";
  }
  [[nodiscard]] auto apply(Grid& grid) const noexcept -> bool override;

 private:
  auto restrict_of_line(Grid& grid, Grid::Idx i,
                        const Grid::Cell value) const noexcept -> bool;
  auto restrict_row(Grid& grid, Grid::Idx row, Grid::Idx group_col,
                    const Grid::Cell value) const noexcept -> bool;
  auto restrict_col(Grid& grid, Grid::Idx col, Grid::Idx group_row,
                    const Grid::Cell value) const noexcept -> bool;
};
