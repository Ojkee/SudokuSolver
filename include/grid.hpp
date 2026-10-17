#ifndef GRID_HPP
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <string_view>
#include <vector>

enum class ParseError { InvalidLength, InvalidChar };

class Grid {
 public:
  inline constexpr static std::size_t kSize{9};
  using Cell = uint8_t;
  using Idx = const uint8_t;
  using Grid_t = std::array<std::array<Cell, kSize>, kSize>;
  using CandidateMask_t = uint16_t;
  using Candidates_t = std::array<std::array<CandidateMask_t, kSize>, kSize>;

  Grid(std::string_view line) : Grid(Grid::of_line(line).value()) {};
  Grid(Grid_t grid_array) : data_(grid_array) { fill_cell_candidates(); };
  static auto of_line(std::string_view line) noexcept
      -> std::expected<Grid, ParseError>;

  auto print() const noexcept -> const void;
  auto solved() noexcept -> const bool;
  auto empty(Idx row, Idx col) const noexcept -> const bool;
  auto place(Idx row, Idx col, const Cell value) noexcept -> void;
  auto in_row(Idx row, const Cell value) const noexcept -> const bool;
  auto in_col(Idx col, const Cell value) const noexcept -> const bool;
  auto in_group(Idx group_row, Idx group_col, const Cell value) const noexcept
      -> const bool;
  auto at(Idx row, Idx col) const noexcept -> const Cell;
  auto candidates() -> Candidates_t { return cell_candidates_; };
  auto eliminate_candidate(Idx row, Idx col, const Cell value) noexcept -> const
      bool;
  auto eliminate_candidates_row(Idx row, const Cell value) noexcept -> void;
  auto eliminate_candidates_col(Idx row, const Cell value) noexcept -> void;
  auto eliminate_candidates_group(Idx group_row, Idx group_col,
                                  const Cell value) noexcept -> void;
  static auto of_mask(const CandidateMask_t mask) noexcept
      -> const std::vector<Cell>;
  auto has_candidate(Idx row, Idx col, const Cell value) const noexcept -> const
      bool;
  auto transposed_candidates() const noexcept -> const Candidates_t;

 private:
  auto fill_cell_candidates() noexcept -> void;
  auto candidates_for_cell(uint8_t row, uint8_t col) -> CandidateMask_t;
  static auto to_mask(const Cell value) noexcept -> const CandidateMask_t;

  constexpr static auto is_digit(const char c) noexcept -> bool;
  Grid_t data_{};
  Candidates_t cell_candidates_{};
};

#endif  // !GRID_HPP
