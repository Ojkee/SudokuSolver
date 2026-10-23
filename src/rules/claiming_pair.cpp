#include "rules/claiming_pair.hpp"

#include "grid.hpp"

auto ClaimingPair::apply(Grid& grid) const noexcept -> bool {
  auto restricted{false};
  for (auto value{1uz}; value <= 9; ++value) {
    for (auto i{0uz}; i < 9; ++i) {
      restricted |= restrict_of_line(grid, i, value);
    }
  }
  return restricted;
}

auto ClaimingPair::restrict_of_line(Grid& grid, Grid::Idx i,
                                    const Grid::Cell value) const noexcept
    -> bool {
  auto first_appeared_group_row{-1};
  auto first_appeared_group_col{-1};
  auto can_restrict_row{true};
  auto can_restrict_col{true};

  for (auto j{0uz}; j < 9; ++j) {
    if (grid.has_candidate(i, j, value)) {
      const auto group_col = static_cast<int>(j / 3);

      if (first_appeared_group_row == -1) {
        first_appeared_group_row = group_col;
      } else if (first_appeared_group_row != group_col) {
        can_restrict_row = false;
      }
    }

    if (grid.has_candidate(j, i, value)) {
      const auto group_row = static_cast<int>(j / 3);

      if (first_appeared_group_col == -1) {
        first_appeared_group_col = group_row;
      } else if (first_appeared_group_col != group_row) {
        can_restrict_col = false;
      }
    }
  }

  auto restricted{false};

  if (can_restrict_row && first_appeared_group_row != -1) {
    restricted |= restrict_row(
        grid, i, static_cast<Grid::Idx>(first_appeared_group_row), value);
  }

  if (can_restrict_col && first_appeared_group_col != -1) {
    restricted |= restrict_col(
        grid, i, static_cast<Grid::Idx>(first_appeared_group_col), value);
  }

  return restricted;
}

auto ClaimingPair::restrict_row(Grid& grid, Grid::Idx row, Grid::Idx group_col,
                                const Grid::Cell value) const noexcept -> bool {
  auto restricted{false};
  for (auto group_row{row / 3 * 3}; group_row < (row / 3 + 1) * 3;
       ++group_row) {
    if (group_row == row) continue;
    for (auto col{group_col * 3}; col < (group_col + 1) * 3; ++col) {
      restricted |= grid.eliminate_candidate(group_row, col, value);
    }
  }
  return restricted;
}

auto ClaimingPair::restrict_col(Grid& grid, Grid::Idx col, Grid::Idx group_row,
                                const Grid::Cell value) const noexcept -> bool {
  auto restricted{false};
  for (auto group_col{col / 3 * 3}; group_col < (col / 3 + 1) * 3;
       ++group_col) {
    if (group_col == col) continue;
    for (auto row{group_row * 3}; row < (group_row + 1) * 3; ++row) {
      restricted |= grid.eliminate_candidate(row, group_col, value);
    }
  }
  return restricted;
}
