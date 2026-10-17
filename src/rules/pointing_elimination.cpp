#include "rules/pointing_elimination.hpp"

#include "grid.hpp"

auto PointingElimination::apply(Grid& grid) const noexcept -> bool {
  auto eliminated{false};
  for (auto value{1uz}; value <= 9; ++value) {
    for (auto group_row{0uz}; group_row < 9; group_row += 3) {
      for (auto group_col{0uz}; group_col < 9; group_col += 3) {
        eliminated |= eliminate_row_wise_in_group(grid, group_row, group_col,
                                                  value, Transposed{false});
        eliminated |= eliminate_row_wise_in_group(grid, group_row, group_col,
                                                  value, Transposed{true});
      }
    }
  }

  return eliminated;
}

auto PointingElimination::eliminate_row_wise_in_group(
    Grid& grid, Grid::Idx group_row, Grid::Idx group_col,
    const Grid::Cell value, const Transposed transposed) const noexcept -> const
    bool {
  const auto eliminate_candidate = [&](auto row, auto col) {
    return transposed.value ? grid.eliminate_candidate(col, row, value)
                            : grid.eliminate_candidate(row, col, value);
  };

  const auto in_row =
      in_row_mask(grid, group_row, group_col, value, transposed);
  const auto exclude_group = [&group_col](const auto col) {
    return group_col <= col && col < group_col + 3;
  };

  auto eliminated{false};
  for (auto row{0uz}; row < 3; ++row) {
    if (in_row != (1uz << row)) {
      continue;
    }

    for (auto col{0uz}; col < 9; ++col) {
      if (exclude_group(col)) continue;
      eliminated |= eliminate_candidate(group_row + row, col);
    }
    return eliminated;
  }
  return false;
}

auto PointingElimination::in_row_mask(
    const Grid& grid, Grid::Idx group_row, Grid::Idx group_col,
    const Grid::Cell value, const Transposed transposed) const noexcept
    -> const uint8_t {
  const auto has_candidate = [&](auto row, auto col) {
    return transposed.value ? grid.has_candidate(col, row, value)
                            : grid.has_candidate(row, col, value);
  };
  auto in_row{0uz};
  for (auto row{0uz}; row < 3; ++row) {
    for (auto col{0uz}; col < 3; ++col) {
      const auto present =
          has_candidate(group_row + row, group_col + col) ? 1 : 0;
      in_row |= (present << row);
    }
  }
  return in_row;
}
