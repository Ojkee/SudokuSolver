#pragma once

#include "../grid.hpp"
#include "rule.hpp"

class HiddenSingle final : public Rule {
 public:
  [[nodiscard]] auto name() const noexcept -> const std::string override {
    return "hidden_single";
  }
  [[nodiscard]] auto apply(Grid& grid) const noexcept -> bool override;

 private:
  auto once_in_row(Grid& grid, const Grid::Cell value) const noexcept -> bool;
  auto once_in_col(Grid& grid, const Grid::Cell value) const noexcept -> bool;
  auto once_in_group(Grid& grid, const Grid::Cell value) const noexcept -> bool;
};
