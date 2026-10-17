#pragma once

#include "../grid.hpp"
#include "rule.hpp"

struct Transposed {
  bool value;
};

class PointingElimination final : public Rule {
 public:
  [[nodiscard]] auto name() const noexcept -> const std::string override {
    return "pointing_elimination";
  }
  [[nodiscard]] auto apply(Grid& grid) const noexcept -> bool override;

 private:
  auto in_row_mask(const Grid& grid, Grid::Idx group_row, Grid::Idx group_col,
                   const Grid::Cell value,
                   const Transposed transposed) const noexcept -> const uint8_t;
  auto eliminate_row_wise_in_group(Grid& grid, Grid::Idx group_row,
                                   Grid::Idx group_col, const Grid::Cell value,
                                   const Transposed transposed) const noexcept
      -> const bool;
};
