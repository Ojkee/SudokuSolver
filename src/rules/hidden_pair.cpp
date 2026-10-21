#include "rules/hidden_pair.hpp"

#include <array>

#include "grid.hpp"

auto HiddenPair::apply(Grid& grid) const noexcept -> bool {
  auto restricted{false};
  for (auto group_row{0uz}; group_row < 9; group_row += 3) {
    for (auto group_col{0uz}; group_col < 9; group_col += 3) {
      if (!at_least_n_empty_group(grid, 3, group_row, group_col)) continue;
      const auto positions = values_positions_group(grid, group_row, group_col);
      restricted |= restrict_of_positions(grid, positions);
    }
  }

  for (auto i{0uz}; i < 9; ++i) {
    if (at_least_n_empty_row(grid, 3, i)) {
      const auto positions = values_positions_row(grid, i);
      restricted |= restrict_of_positions(grid, positions);
    }

    if (at_least_n_empty_col(grid, 3, i)) {
      const auto positions = values_positions_col(grid, i);
      restricted |= restrict_of_positions(grid, positions);
    }
  }
  return restricted;
}

auto HiddenPair::at_least_n_empty_group(const Grid& grid, const uint8_t n,
                                        Grid::Idx group_row,
                                        Grid::Idx group_col) const noexcept
    -> bool {
  auto count{0uz};
  for (auto row{group_row}; row < group_row + 3; ++row) {
    for (auto col{group_col}; col < group_col + 3; ++col) {
      if (grid.empty(row, col)) ++count;
    }
  }
  return count >= n;
}

auto HiddenPair::values_positions_group(Grid& grid, Grid::Idx group_row,
                                        Grid::Idx group_col) const noexcept
    -> Positions {
  auto positions = Positions{};
  for (auto value{1uz}; value <= 9; ++value) {
    for (auto row{group_row}; row < group_row + 3; ++row) {
      for (auto col{group_col}; col < group_col + 3; ++col) {
        if (grid.has_candidate(row, col, value)) {
          const Position pos{row, col};
          positions[value].emplace_back(pos);
        }
      }
    }
  }
  return positions;
}

auto HiddenPair::at_least_n_empty_row(const Grid& grid, const uint8_t n,
                                      Grid::Idx row) const noexcept -> bool {
  auto count{0uz};
  for (auto col{0uz}; col < 9; ++col) {
    if (grid.empty(row, col)) ++count;
  }
  return count >= n;
}

auto HiddenPair::values_positions_row(Grid& grid, Grid::Idx row) const noexcept
    -> Positions {
  auto positions = Positions{};
  for (auto value{1uz}; value <= 9; ++value) {
    for (auto col{0uz}; col < 9; ++col) {
      if (grid.has_candidate(row, col, value)) {
        const Position pos{row, col};
        positions[value].emplace_back(pos);
      }
    }
  }
  return positions;
}

auto HiddenPair::at_least_n_empty_col(const Grid& grid, const uint8_t n,
                                      Grid::Idx col) const noexcept -> bool {
  auto count{0uz};
  for (auto row{0uz}; row < 9; ++row) {
    if (grid.empty(row, col)) ++count;
  }
  return count >= n;
}

auto HiddenPair::values_positions_col(Grid& grid, Grid::Idx col) const noexcept
    -> Positions {
  auto positions = Positions{};
  for (auto value{1uz}; value <= 9; ++value) {
    for (auto row{0uz}; row < 9; ++row) {
      if (grid.has_candidate(row, col, value)) {
        const Position pos{row, col};
        positions[value].emplace_back(pos);
      }
    }
  }
  return positions;
}

auto HiddenPair::restrict_of_positions(
    Grid& grid, const Positions& positions) const noexcept -> bool {
  auto restricted{false};
  for (auto i{1uz}; i <= 9; ++i) {
    if (positions[i].size() != 2) continue;
    for (auto j{i + 1}; j <= 9; ++j) {
      if (positions[j].size() != 2) continue;
      if (positions[i][0] != positions[j][0] ||
          positions[i][1] != positions[j][1])
        continue;
      for (auto value{1uz}; value <= 9; ++value) {
        if (value == i || value == j) continue;
        restricted |= eliminate_candidate_of_position(grid, positions[i][0],
                                                      positions[i][1], value);
      }
    }
  }
  return restricted;
}

auto HiddenPair::eliminate_candidate_of_position(
    Grid& grid, const Position& pos1, const Position& pos2,
    Grid::Cell value) const noexcept -> bool {
  const auto eliminated1 =
      grid.eliminate_candidate(pos1.first, pos1.second, value);
  const auto eliminated2 =
      grid.eliminate_candidate(pos2.first, pos2.second, value);
  return eliminated1 || eliminated2;
}
