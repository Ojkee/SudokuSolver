#include "rules/hidden_single.hpp"

auto HiddenSingle::apply(Grid& grid) const noexcept -> bool {
  for (auto value{1uz}; value <= 9; ++value) {
    if (once_in_row(grid, value)) return true;
    if (once_in_col(grid, value)) return true;
    if (once_in_group(grid, value)) return true;
  }
  return false;
}

auto HiddenSingle::once_in_row(Grid& grid,
                               const Grid::Cell value) const noexcept -> bool {
  for (auto row{0uz}; row < 9; ++row) {
    auto col_idx{-1};
    auto should_place{true};
    for (auto col{0uz}; col < 9; ++col) {
      const auto present = grid.has_candidate(row, col, value);
      if (present && col_idx == -1)
        col_idx = col;
      else if (present) {
        should_place = false;
        break;
      }
    }
    if (should_place && col_idx != -1) {
      grid.place(row, col_idx, value);
      return true;
    }
  }
  return false;
}

auto HiddenSingle::once_in_col(Grid& grid,
                               const Grid::Cell value) const noexcept -> bool {
  for (auto col{0uz}; col < 9; ++col) {
    auto row_idx{-1};
    auto should_place{true};
    for (auto row{0uz}; row < 9; ++row) {
      const auto present = grid.has_candidate(row, col, value);
      if (present && row_idx == -1)
        row_idx = row;
      else if (present) {
        should_place = false;
        break;
      }
    }
    if (should_place && row_idx != -1) {
      grid.place(row_idx, col, value);
      return true;
    }
  }
  return false;
}

auto HiddenSingle::once_in_group(Grid& grid,
                                 const Grid::Cell value) const noexcept
    -> bool {
  for (auto group_row{0uz}; group_row < 9; group_row += 3) {
    for (auto group_col{0uz}; group_col < 9; group_col += 3) {
      auto row_idx{-1};
      auto col_idx{-1};
      auto should_place{true};
      for (auto row{0uz}; row < 3; ++row) {
        for (auto col{0uz}; col < 3; ++col) {
          const auto present =
              grid.has_candidate(group_row + row, group_col + col, value);
          if (present && row_idx == -1) {
            row_idx = group_row + row;
            col_idx = group_col + col;

          } else if (present) {
            should_place = false;
            break;
          }
        }
        if (!should_place) {
          break;
        }
      }
      if (should_place && row_idx != -1) {
        grid.place(row_idx, col_idx, value);
        return true;
      }
    }
  }
  return false;
}
