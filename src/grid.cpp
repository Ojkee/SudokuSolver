
#include "../include/grid.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <print>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

namespace rng = std::ranges;
namespace vw = std::views;

auto Grid::of_line(std::string_view line) noexcept
    -> std::expected<Grid, ParseError> {
  Grid::Grid_t grid_array{};
  if (line.size() != Grid::kSize * Grid::kSize)
    return std::unexpected(ParseError::InvalidLength);
  if (!rng::all_of(line, Grid::is_digit))
    return std::unexpected(ParseError::InvalidChar);

  for (const auto [i, v] : vw::enumerate(line)) {
    const auto x = i / Grid::kSize;
    const auto y = i % Grid::kSize;
    grid_array[x][y] = v - '0';
  }
  return Grid(grid_array);
}

auto Grid::print() const noexcept -> const void {
  std::println();
  for (auto const [i, row] : vw::enumerate(data_)) {
    if (i > 0 && i % 3 == 0) {
      for (auto k{0uz}; k < 11; ++k) {
        const auto delim = (k == 3 || k == 7) ? "+" : "-";
        std::print("{} ", delim);
      }
      std::print("\n");
    }
    for (auto const [j, cell] : vw::enumerate(row)) {
      if (j > 0 && j % 3 == 0) std::print("| ");
      const auto v = (cell == 0) ? " " : std::to_string(cell);
      std::printf("%s ", v.data());
    }
    std::print("\n");
  }
  std::println();
}

auto Grid::solved() noexcept -> const bool {
  for (auto row{0uz}; row < 9; ++row) {
    for (auto col{0uz}; col < 9; ++col) {
      if (data_[row][col] == 0) return false;
    }
  }
  return true;
}

auto Grid::empty(Idx row, Idx col) const noexcept -> const bool {
  return data_[row][col] == 0;
}

auto Grid::place(Idx row, Idx col, const Cell value) noexcept -> void {
  data_[row][col] = value;
  eliminate_candidates_row(row, value);
  eliminate_candidates_col(col, value);
  eliminate_candidates_group(row / 3, col / 3, value);
  cell_candidates_[row][col] = {};
}

auto Grid::fill_cell_candidates() noexcept -> void {
  for (const auto [i, row] : vw::enumerate(data_)) {
    for (const auto [j, cell] : vw::enumerate(row)) {
      if (cell != 0) continue;
      cell_candidates_[i][j] = candidates_for_cell(i, j);
    }
  }
}

auto Grid::in_row(Idx row, const Cell value) const noexcept -> const bool {
  for (auto col{0uz}; col < 9; ++col) {
    if (data_[row][col] == value) return true;
  }
  return false;
}

auto Grid::in_col(Idx col, const Cell value) const noexcept -> const bool {
  for (auto row{0uz}; row < 9; ++row) {
    if (data_[row][col] == value) return true;
  }
  return false;
}

auto Grid::in_group(Idx group_row, Idx group_col,
                    const Cell value) const noexcept -> const bool {
  const auto row = group_row * 3;
  const auto col = group_col * 3;
  for (auto i{0uz}; i < 3; ++i) {
    for (auto j{0uz}; j < 3; ++j) {
      if (data_[row + i][col + j] == value) return true;
    }
  }
  return false;
}

auto Grid::at(Idx row, Idx col) const noexcept -> const Cell {
  return data_[row][col];
}

auto Grid::eliminate_candidate(Idx row, Idx col, const Cell value) noexcept
    -> const bool {
  const auto before = cell_candidates_[row][col];
  cell_candidates_[row][col] &= ~to_mask(value);
  return before != cell_candidates_[row][col];
}

auto Grid::eliminate_candidates_row(Idx row, const Cell value) noexcept
    -> void {
  for (auto col{0uz}; col < 9; ++col) {
    eliminate_candidate(row, col, value);
  }
}

auto Grid::eliminate_candidates_col(Idx col, const Cell value) noexcept
    -> void {
  for (auto row{0uz}; row < 9; ++row) {
    eliminate_candidate(row, col, value);
  }
}

auto Grid::eliminate_candidates_group(Idx group_row, Idx group_col,
                                      const Cell value) noexcept -> void {
  const auto row = group_row * 3;
  const auto col = group_col * 3;
  for (auto i{0uz}; i < 3; ++i) {
    for (auto j{0uz}; j < 3; ++j) {
      eliminate_candidate(row + i, col + j, value);
    }
  }
}

auto Grid::of_mask(const CandidateMask_t mask) noexcept
    -> const std::vector<Cell> {
  auto result = std::vector<Cell>();
  for (auto value{1uz}; value <= 9; ++value) {
    if ((mask & Grid::to_mask(value)) != 0) result.emplace_back(value);
  }
  return result;
}

auto Grid::has_candidate(Idx row, Idx col, const Cell value) const noexcept
    -> const bool {
  return (cell_candidates_[row][col] & Grid::to_mask(value)) != 0;
}

auto Grid::transposed_candidates() const noexcept -> const Candidates_t {
  // TODO: implement
  return {};
}

/*
 * PRIVATE
 */

constexpr auto Grid::is_digit(const char c) noexcept -> bool {
  return '0' <= c && c <= '9';
}

auto Grid::candidates_for_cell(uint8_t row, uint8_t col) -> CandidateMask_t {
  const auto is_valid = [this, col, row](const Cell candidate) {
    return !in_row(row, candidate) && !in_col(col, candidate) &&
           !in_group(row / 3, col / 3, candidate);
  };

  auto masks = CandidateMask_t{};
  for (auto candidate{1uz}; candidate <= 9; ++candidate) {
    if (is_valid(candidate)) {
      masks |= to_mask(candidate);
    }
  }

  return masks;
}

auto Grid::to_mask(const Cell value) noexcept -> const CandidateMask_t {
  return 1 << value;
}
